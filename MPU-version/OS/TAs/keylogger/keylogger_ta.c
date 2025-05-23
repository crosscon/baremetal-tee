/*
 * Copyright (c) 2016, Linaro Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

//#include <tee_internal_api.h>
#include "tee_core_api.h"
//#include <tee_internal_api_extensions.h>
//#include <trace.h>
#include <keylogger_ta.h>
//#include <kernel/pseudo_ta.h>

int init = 0;
int pin_idx = 0;
uint16_t key_state = 0;
char pin[TA_KEYLOGGER_PIN_LEN];
const char keymap[TA_KEYLOGGER_KYPD_NB_KEYS] =
{
    '1', '4', '7', '*',
    '2', '5', '8', '0',
    '3', '6', '9', '#',
    'A', 'B', 'C', 'D',
};
char secure_pin[TA_KEYLOGGER_PIN_LEN] = {'7','7','7','7'};

int dummy_pin_idx = 0;
char dummy_pin[TA_KEYLOGGER_PIN_LEN];

/*
 * Called when the instance of the TA is created. This is the first call in
 * the TA.
 */
TEE_Result /*Keylogger_*/TA_CreateEntryPoint(void)
{
    //DMSG("has been called");

    return TEE_SUCCESS;
}

/*
 * Called when the instance of the TA is destroyed if the TA has not
 * crashed or panicked. This is the last call in the TA.
 */
void /*Keylogger_*/TA_DestroyEntryPoint(void)
{
    //DMSG("has been called");
    return;
}

/*
 * Called when a new session is opened to the TA. *sess_ctx can be updated
 * with a value to be able to identify this session in subsequent calls to the
 * TA. In this function you will normally do the global initialization for the
 * TA.
 */
TEE_Result /*Keylogger_*/TA_OpenSessionEntryPoint(uint32_t param_types,
        TEE_Param __maybe_unused params[4],
        void __maybe_unused **sess_ctx)
{
    uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_NONE,
                           TEE_PARAM_TYPE_NONE,
                           TEE_PARAM_TYPE_NONE,
                           TEE_PARAM_TYPE_NONE);

    //DMSG("has been called");

    if (param_types != exp_param_types)
        return TEE_ERROR_BAD_PARAMETERS;

    /* Unused parameters */
    (void)&params;
    (void)&sess_ctx;

    /*
     * The DMSG() macro is non-standard, TEE Internal API doesn't
     * specify any means to logging from a TA.
     */
    //IMSG("Keylogger has successfully been created!\n");

    /* If return value != TEE_SUCCESS the session will not be created. */
    return TEE_SUCCESS;
}

/*
 * Called when a session is closed, sess_ctx hold the value that was
 * assigned by TA_OpenSessionEntryPoint().
 */
void /*Keylogger_*/TA_CloseSessionEntryPoint(void __maybe_unused *sess_ctx)
{
    (void)&sess_ctx; /* Unused parameter */
    //IMSG("Goodbye!\n");
}

int read_key_simul(void)
{
    int is_pressed, mask = 0x1;

    /* Simulate fetch key state from GPIO driver */
    uint16_t new_key_state = (1<<2);

    /* Store down keys in private PIN array */
    for (int key = 0; key < TA_KEYLOGGER_KYPD_NB_KEYS; key++)
    {
        is_pressed = (new_key_state & mask) & ~(key_state & mask);

        if(is_pressed && (pin_idx < TA_KEYLOGGER_KYPD_NB_KEYS))
        {
            pin[pin_idx++] = keymap[key];
        }
        else
            dummy_pin[dummy_pin_idx++] = keymap[key];

        dummy_pin_idx = 0;
        mask = mask << 1;
    }

    /* Return the number of characters still to be entered by the user */
    return (TA_KEYLOGGER_PIN_LEN - pin_idx);
}

static TEE_Result poll_keypad(uint32_t param_types,
    TEE_Param params[4])
{
    uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_VALUE_INOUT,
                           TEE_PARAM_TYPE_NONE,
                           TEE_PARAM_TYPE_NONE,
                           TEE_PARAM_TYPE_NONE);
    int pin_len = 1;

    //DMSG("has been called");

    if (param_types != exp_param_types)
        return TEE_ERROR_BAD_PARAMETERS;

    while(pin_len)
    {
        pin_len = read_key_simul();
    }

    pin_idx = 0;

    if(pin[0] == secure_pin [0] && pin[1] == secure_pin [1] && \
       pin[2] == secure_pin [2] && pin[3] == secure_pin [3])
    {
        //MSG("Secure pin is correct. Passed device key to untrusted domain...");
        params[0].value.a = 0xDEADDEAD;
    }

    return TEE_SUCCESS;
}

/*
 * Called when a TA is invoked. sess_ctx hold that value that was
 * assigned by TA_OpenSessionEntryPoint(). The rest of the paramters
 * comes from normal world.
 */
TEE_Result /*Keylogger_*/TA_InvokeCommandEntryPoint(void __maybe_unused *sess_ctx,
            uint32_t cmd_id,
            uint32_t param_types, TEE_Param params[4])
{
    (void)&sess_ctx; /* Unused parameter */

    switch (cmd_id) {
    case TA_KEYLOGGER_CMD_READ_KEY:
        return poll_keypad(param_types, params);
    default:
        return TEE_ERROR_BAD_PARAMETERS;
    }
}

//pseudo_ta_register(.uuid = TA_KEYLOGGER_UUID, .name = "Keylogger",
//       .flags = PTA_DEFAULT_FLAGS | TA_FLAG_CONCURRENT,
//       .open_session_entry_point = Keylogger_TA_OpenSessionEntryPoint,
//       .close_session_entry_point = Keylogger_TA_CloseSessionEntryPoint,
//       .invoke_command_entry_point = Keylogger_TA_InvokeCommandEntryPoint);