#ifndef LOV_DICT_H
#define LOV_DICT_H

#include <stdint.h>

struct lov_kw
{
	const char *kw;
	int32_t kwcode;
};

struct lov_kw *lov_in_kw_set(
	register const char *str, register unsigned int len);

#endif /* LOV_DICT_H */
