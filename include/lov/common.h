#ifndef LOV_COMMON_H
#define LOV_COMMON_H

#include <stdint.h>

typedef enum lov_fnret
{
	FR_SUCCESS = 0,
	FR_ERR_FAILURE = -10,
	FR_ERR_BUFFER_OVERFLOW,
	FR_ERR_STACK_OVERFLOW,
	FR_ERR_STACK_UNDERFLOW,
	FR_ERR_INVALID_ARGUMENT,
} lov_fnret;

#define LOV_FALSE (0)
#define LOV_TRUE (1)

typedef uint8_t lov_bool;

#define LOV_U8A_SETBIT(m, n, i) ((m)[((n) - 1) - ((i) / 8)] |= (1 << ((i) % 8)))

#define LOV_U8A_CLRBIT(m, n, i) ((m)[((n) - 1) - ((i) / 8)] &= ~(1 << ((i) % 8)))

#define LOV_U8A_CHKBIT(m, n, i) (((m)[((n) - 1) - ((i) / 8)] >> ((i) % 8)) & 1)

#endif /* LOV_COMMON_H */
