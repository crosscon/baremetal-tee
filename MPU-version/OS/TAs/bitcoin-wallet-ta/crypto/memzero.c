#include <string.h>
void memzero(void *s, size_t n);

void memzero(void *s, size_t n)
{
	memset(s, 0, n);
}
