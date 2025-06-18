#include <string.h>
#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "flash.h"
#include "cJSON.h"
#include "tee_common.h"

// Maximum number of objects that can be stored in the flash memory (for each TA)
#define FLASH_MAX_OBJECT      32
#define CALC_FREE_SIZE_OFF    80

/**
 * In order to avoid using a file system to manage data in the FLASH memory, 
 * the data are organized in a JSON format (using the cJSON library)
 * The stored data are organized in objects, each object has an ID, a length, and the data
 * 
 * The JSON format used to store the data in the FLASH memory is the following:
{
    "objects": [
        {
            "id": 1,
            "len": 256,
            "data": "xxxxx"
        },
        {
            "id": 2,
            "len": 128,
            "data": "xxxxx"
        }
    ]
}
 * 
 * The actual data stored in the FLASH memory for persistent objects are encoded in base64
 * The motivation behind this choice was to avoid character encoding issues as C can treat 
 * characters diffently based on the type they are declared (e.g. char, unsigned char, int, uint, ecc.)
 * 
 * In this way, the user can store trasparently the data in the FLASH memory without worrying about the
 * character encoding and their type
 * 
 * Basic encoding and decoding functions are provided in this file without the need of external libraries
 */

// Define the constants chars that are part of the BASE64 encoding
static const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "abcdefghijklmnopqrstuvwxyz"
                                "0123456789+/";

// Define the inverse of the BASE64 encoding
static const int b64invs[] = { 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58,
	59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5,
	6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28,
	29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
	43, 44, 45, 46, 47, 48, 49, 50, 51 };

// Returns the size of the encoding
size_t b64_encoded_size(size_t inlen)
{
	size_t ret;

	ret = inlen;
	if (inlen % 3 != 0)
		ret += 3 - (inlen % 3);
	ret /= 3;
	ret *= 4;

	return ret;
}

// Returns the size of the decoding
size_t b64_decoded_size(const char *in)
{
	size_t len;
	size_t ret;
	size_t i;

	if (in == NULL)
		return 0;

	len = strlen(in);
	ret = len / 4 * 3;

	for (i=len; (i--)>0; ) {
		if (in[i] == '=') {
			ret--;
		} else {
			break;
		}
	}

	return ret;
}

// Checks if the character is valid  according to the BASE64 encoding
int b64_isvalidchar(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	if (c >= 'A' && c <= 'Z')
		return 1;
	if (c >= 'a' && c <= 'z')
		return 1;
	if (c == '+' || c == '/' || c == '=')
		return 1;
	return 0;
}

// Encodes the input to the output according to the BASE64 encoding. Output_len contains also the termination character
int base64_encode(const unsigned char *input, size_t input_len, char *output, size_t output_len)
{
    size_t required_size = b64_encoded_size(input_len);

    if(output_len < required_size)
        return -1;

    int i, j;
    size_t v;
	for (i=0, j=0; i<input_len; i+=3, j+=4) 
    {
		v = input[i];
		v = i+1 < input_len ? v << 8 | input[i+1] : v << 8;
		v = i+2 < input_len ? v << 8 | input[i+2] : v << 8;

		output[j]   = b64chars[(v >> 18) & 0x3F];
		output[j+1] = b64chars[(v >> 12) & 0x3F];
		if (i+1 < input_len) {
			output[j+2] = b64chars[(v >> 6) & 0x3F];
		} else {
			output[j+2] = '=';
		}
		if (i+2 < input_len) {
			output[j+3] = b64chars[v & 0x3F];
		} else {
			output[j+3] = '=';
		}
	}

    output[output_len -1] = '\0';

    return required_size;
}

// Decodes the input to the output according to the BASE64 encoding
int base64_decode(const unsigned char *input, size_t input_len, unsigned char *output, size_t output_len) 
{   
    size_t v;
    size_t required_size = b64_decoded_size((const char *)input);

	if (output_len < required_size || input_len % 4 != 0)
    {
        //printf("Burada 116\r\n");
        return 0;
    }
		

	for (int i=0; i<input_len; i++) 
    {
		if (b64_isvalidchar((char)input[i]) == 0) {
			//printf("Burada[%d] 123 %d\r\n", i, input[i]);
            return 0;
		}
	}

	for (int i=0, j=0; i<input_len; i+=4, j+=3) {
		v = b64invs[input[i]-43];
		v = (v << 6) | b64invs[input[i+1]-43];
		v = input[i+2]=='=' ? v << 6 : (v << 6) | b64invs[input[i+2]-43];
		v = input[i+3]=='=' ? v << 6 : (v << 6) | b64invs[input[i+3]-43];

		output[j] = (v >> 16) & 0xFF;
		if (input[i+2] != '=')
			output[j+1] = (v >> 8) & 0xFF;
		if (input[i+3] != '=')
			output[j+2] = v & 0xFF;
	}

    return required_size;
}

/**
 * @brief Searchs desired charcters (x, y) in the given content (arr)
 *        and returns the index of the first occurence of the characters.
*/
static int search(char arr[], int n, int x, int y)
{
    for (int i=0; i<n-1; i++)
        if ((arr[i] == x) && (arr[i+1] == y))
            return i;
    return -1;
}


/**
 * @brief Get flash area starting address and total size using TA id.
 * Each TA has their own secure storage area to store persistent objects.
 * 
 * @param id Trusted App id (1 or 2)
 * @param start_addr Relevant area starting address
 * @param total_size relevant area total flash sizewhich is dedicated for relevant TA
*/
void flash_getConfig(uint32_t id, uint32_t *start_addr, uint32_t *total_size)
{
    if(id == TRUSTED_APP_1){
        *start_addr = TA1_SEC_STR_BASE_ADDR;
        *total_size = TA1_FLASH_SIZE;
    }else{
        *start_addr = TA2_SEC_STR_BASE_ADDR;
        *total_size = TA2_FLASH_SIZE;
    }
}

/**
 * @brief Erase all flash area which is indicated by TA id
 * 
 * @param ta_id TA id
 * 
 * @return if it is success, return 0 else -1
*/
int flash_erase(uint32_t ta_id)
{
    HAL_FLASH_Unlock();

    uint16_t page_count = 0;
    uint16_t page_index = 0;
    if(ta_id == TRUSTED_APP_1){
        page_count = TA1_PAGE_COUNT;
        page_index = TA1_PAGE_INDEX;
    }else{
        page_count = TA2_PAGE_COUNT;
        page_index = TA2_PAGE_INDEX;
    }
    
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_SR_ERRORS); //clear flags

    FLASH_EraseInitTypeDef eraseInitStruct;
    uint32_t sectorError = 0;

    eraseInitStruct.TypeErase = TYPEERASE_PAGES;
    if (page_index < 256) {
        eraseInitStruct.Banks = FLASH_BANK_1;
    } else {
        eraseInitStruct.Banks = FLASH_BANK_2;
    }
    eraseInitStruct.NbPages = page_count;
    eraseInitStruct.Page = page_index;

    if (HAL_FLASHEx_Erase(&eraseInitStruct, &sectorError) != HAL_OK) {
        HAL_FLASH_Lock();
        return -1;
    }

    HAL_FLASH_Lock();
    
    return 0;
}


/**
 * @brief read flash memory area from starting addres to address+len
 * 
 * @param rx_buff Buffer to store the readed data
 * @param len Length of the data
 * @param addr Starting address
*/
void flash_internalRead(uint8_t* rx_buff, size_t len, int addr)
{
    memcpy(rx_buff, (void*)addr, len);
}


/**
 * @brief Write raw data to flash memory area
 * 
 * @param ctx Raw Data to write in flash
 * @param len Raw Data length
 * @param ta_id TA id to find proper place in flash
 * 
 * @warning if this functions returns different than 0 and -1 please chech the HAL FLASH ERR flags
 * 
 * @return if it is success, returns 0, else different from 0. -1 means err for erasing flash
 * 
*/
static int flash_writeInternal(const char* ctx, int len, uint32_t ta_id)
{
    HAL_FLASH_Unlock();
    
    FLASH_EraseInitTypeDef eraseInitStruct = {0};
    uint32_t sectorError = 0;

    uint16_t page_count = 0;
    uint16_t page_index = 0;

    if(ta_id == TRUSTED_APP_1){
        page_count = TA1_PAGE_COUNT;
        page_index = TA1_PAGE_INDEX;
    }else{
        page_count = TA2_PAGE_COUNT;
        page_index = TA2_PAGE_INDEX;
    }

    uint32_t start_addr = 0;
    uint32_t total_size = 0;
    flash_getConfig(ta_id, &start_addr, &total_size);
    

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_SR_ERRORS); //clear flag

    eraseInitStruct.TypeErase = TYPEERASE_PAGES;
    if (page_index < 256) {
        eraseInitStruct.Banks = FLASH_BANK_1;
    } else {
        eraseInitStruct.Banks = FLASH_BANK_2;
    }
    eraseInitStruct.NbPages = page_count;
    eraseInitStruct.Page = page_index;

    if (HAL_FLASHEx_Erase(&eraseInitStruct, &sectorError) != HAL_OK) {
        HAL_FLASH_Lock();
        return -1;
    }

    uint64_t temp = 0;
    int i = 0;
    for (i=0; i<len; i += 8)
    {
        size_t remaining = len - i;
        if (remaining >= 8)
        {
            memcpy(&temp, ctx + i, 8);
        }else{
            // Last partial block: zero-pad
            memset(&temp, 0, sizeof(temp));
            memcpy(&temp, ctx + i, remaining);
        }
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, start_addr + i, temp) != HAL_OK)
        {
            HAL_FLASH_Lock();
            return HAL_FLASH_GetError();
        }
        temp = 0;
    }

    HAL_FLASH_Lock();

    return 0;
}

/**
 * @brief Initialize the memory area identified by the ta_id by 
 * creatig the templates of the json structure
 * 
 * @param ta_id TA id
*/
static int flash_init(uint32_t ta_id)
{
    cJSON *p = cJSON_CreateObject();
    if(!p)
        return -1;

    cJSON *objects = cJSON_CreateArray();
    if(!objects){
        cJSON_Delete(p);
        return -1;
    }
    cJSON_AddItemToObject(p, "objects", objects);

    char *str = cJSON_PrintUnformatted(p);
    if(!str){
        cJSON_Delete(p);
        return -1;
    }

    if(flash_writeInternal(str, strlen(str), ta_id) != 0)
    {
        free(str);
        cJSON_Delete(p);
        return -1;
    }

    cJSON_Delete(p);
    free(str);

    return 0;
}

/**
 * @brief Read the flash memory area, identify the object with the given id and return its data
 * 
 * @param ctx The JSON content
 * @param len Length of the content
 * @param obj_id Object id, it indicates the object number
 * @param out_buff Buffer to store the readed data
 * @param out_len It must be given as a buffer size. If the buffer size and out_len value is same, value of out_len
 *                will not change, otherwise it will set 0
 * 
 * @warning Do not forget free of the returned value
*/
int flash_readObject(const char* ctx, uint32_t len, int obj_id, char* out_buff, size_t out_len)
{
    int ret_val = 0;

    if(!ctx)
        return -1;

    cJSON *p = cJSON_ParseWithLength(ctx, len);
    if(!p)
        return -1;

    cJSON *objects = cJSON_GetObjectItem(p, "objects");
    if(!objects)
        goto end;

    for(int i=0; i<FLASH_MAX_OBJECT; ++i)
    {
        cJSON* item = cJSON_GetArrayItem(objects, i);
        if(!item)
            goto end;

        cJSON *id = cJSON_GetObjectItem(item, "id");
        if(!id)
            goto end;

        if(id->valueint != obj_id)  
            continue;

        // Desired object is found
        // If out_buff is NULL, that means function is using to open the object, not reading
        if(!out_buff){
            cJSON_Delete(p);
            return id->valueint;
        }

        cJSON *data = cJSON_GetObjectItem(item, "data");
        if(!data)
            goto end;

        cJSON *data_len = cJSON_GetObjectItem(item, "len");
        if(!data_len)
            goto end;


        ret_val = base64_decode((const unsigned char*)data->valuestring, strlen(data->valuestring), (unsigned char*)out_buff, out_len);

        break;
    }

end:
    cJSON_Delete(p);
    return ret_val;
}

/**
 * @brief Write new object identified with obj_id to the flash memory area indicated by ta_id
 * 
 * @param ctx The content to store in flash
 * @param len length of content 
 * @param obj_id Object id which identify the content that you want 
 * @param base_addr It indicates to starting flash addres for secure storage which is relevant to id of TA
 * 
 * @return 0 failed, -1 insufficient flash memory, 1 successful
*/
int flash_writeNewObject(const char* ctx, uint32_t len, int obj_id, uint32_t ta_id)
{
    int ret_val = -1;
    uint32_t start_addr = 0;
    uint32_t total_size = 0;
    uint32_t free_size = flash_getFreeSize(ta_id);

    flash_getConfig(ta_id, &start_addr, &total_size);

    if((free_size == total_size) || (free_size == 0))
    {
        if(flash_init(ta_id) != 0) 
            return -1;

        free_size = flash_getFreeSize(ta_id);
    }


    int encoded_len = 4 * ((len + 2) / 3); // base64 encode output length
    if(free_size < encoded_len)
        return -1;

    unsigned char flash_content[total_size - free_size];
    
    
    memset(flash_content, 0, total_size - free_size);

    unsigned char buffer[encoded_len+1];
    if(base64_encode((const unsigned char*)ctx, len, (char*)buffer, encoded_len + 1) <= 0)
        return -1;

    flash_internalRead(flash_content, total_size - free_size, start_addr);

    cJSON *p = cJSON_ParseWithLength((const char*)flash_content, total_size - free_size);
    if(!p)
        return -1;

    cJSON* objects = cJSON_GetObjectItem(p, "objects");
    if(!objects)
        goto end;

    cJSON* item = cJSON_CreateObject();
    if(!item)
        goto end;
    
    ret_val = cJSON_AddItemToArray(objects, item);

    cJSON* id = cJSON_CreateNumber(obj_id);
    if(!id)
        goto end;

    ret_val = cJSON_AddItemToObject(item, "id", id);

    cJSON* ctx_len = cJSON_CreateNumber(encoded_len);
    if(!ctx_len)
        goto end;

    ret_val = cJSON_AddItemToObject(item, "len", ctx_len);

    cJSON *data = cJSON_AddStringToObject(item, "data", buffer);
    if(!data)
        goto end;

    const char *content = cJSON_PrintUnformatted(p);
    if(!content)
        goto end;

    //Check if the size of the jeson content is larger than the flash area
    if(strlen(content) > total_size)
    {
        ret_val = -1;
        goto end;
    }

    int f_err = flash_writeInternal(content, strlen(content), ta_id);
    if(f_err != 0){
        cJSON_Delete(p);
        return -1;
    }

end:
    cJSON_Delete(p);
    return ret_val;
}

/**
 * @brief Gets available size in the flash area indicated by TA id
 * 
 * @param ta_id TA id
 * 
 * @return if it is success, return free size in the flash area else returns -1
*/
uint32_t flash_getFreeSize(uint32_t ta_id)
{
    char buff[CALC_FREE_SIZE_OFF] = {0};
    int free_size = -1;
    int offset = 0;

    uint32_t start_addr = 0;
    uint32_t total_size = 0;
    flash_getConfig(ta_id, &start_addr, &total_size);

    /* If flash is fully empty, the readed all value must be 255 */
    memcpy(buff, (void*)start_addr, CALC_FREE_SIZE_OFF);
    if((buff[0] == 255) && (buff[CALC_FREE_SIZE_OFF - 1] == 255))
        return total_size;

    for(uint32_t i=0; i<total_size; i += CALC_FREE_SIZE_OFF)
    {
        memcpy(buff, (void*)(start_addr + i), CALC_FREE_SIZE_OFF);
        if(buff[CALC_FREE_SIZE_OFF - 1] != 255)
            continue;
        //End of the objects array, that means end of the content is finded
        offset = search(buff, CALC_FREE_SIZE_OFF, ']', '}');
        if(offset != -1){
            free_size = total_size - (offset + i + 2); // +2 for the some extra character end of the content like } or etc.
            break;
        }
    }

    return free_size;
}

/**
 * @brief Delete the object identified with obj_id from flash
 * 
 * @param ta_id TA id
 * @param obj_id object id that will be deleted
 * 
 * @return if it is success, returns 0 else -1
*/
int flash_deleteObject(uint32_t ta_id, int obj_id)
{
    // Get relevant flash area informations
    uint32_t start_addr = 0;
    uint32_t total_size = 0;
    uint32_t free_size = flash_getFreeSize(ta_id);
    flash_getConfig(ta_id, &start_addr, &total_size);
    // Set buffer to read flash area as a raw data
    uint16_t len = total_size -free_size;
    char temp_buff[len]; 
    memset(temp_buff, 0, len);
    flash_internalRead(temp_buff, len, start_addr);
    // Pars RAW data
    cJSON *p = cJSON_ParseWithLength(temp_buff, len);
    if(!p)
        return -1;
    // Get objects array
    cJSON *objects = cJSON_GetObjectItem(p, "objects");
    if(!objects)
        goto end;
    
    int index;
    for(index=0; index<=32; ++index)
    {
        cJSON* item = cJSON_GetArrayItem(objects, index);
        if(!item)
            goto end;

        cJSON *id = cJSON_GetObjectItem(item, "id");
        if(!id)
            goto end;
        //check if the id is the same. If yes, the desired object object is found and break the loop
        if(id->valueint != obj_id)  
            continue;

        break;
    }
    // Delete desired object from content
    cJSON_DeleteItemFromArray(objects, index);
    // We have new conten and obtain it
    char *str = cJSON_PrintUnformatted(p);
    if(!str)
        goto end;
    
    if(flash_writeInternal(str, strlen(str), ta_id) != 0){
        free(str);
        goto end;
    }

    cJSON_Delete(p);
    return 0;
end:
    cJSON_Delete(p);
    return -1;
}
