#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif /* _MSC_VER */

#include "lov/debug.h"
#include "lov/dict.h"
#include "lov/lexer.h"

#include <stdio.h>

lov_fnret lov_I_tokenise(FILE *file)
{
	register uint64_t tc = 0;
	register int32_t ch;
	register uint32_t tbi = 0;
	uint64_t toklen = 0;
	char tokbuf[LOV_MAX_TOKEN_SIZE] = {0};
	uint32_t stbi = 0;
	char strtokbuf[LOV_MAX_STRTOK_SIZE] = {0};
	lov_bool instr = LOV_FALSE;
	struct lov_kw *kw = NULL;


	while ((ch = fgetc(file)) != EOF)
	{
		++tc;

		instr = ch == '"' ? !instr : instr;
		if (instr)
		{
			if (stbi >= LOV_MAX_STRTOK_SIZE - 1)
				return FR_ERR_BUFFER_OVERFLOW;
			strtokbuf[stbi++] = ch;

			continue;
		}
		else if (!instr && stbi)
		{
			strtokbuf[stbi++] = ch;
			if (stbi >= LOV_MAX_STRTOK_SIZE - 1)
				return FR_ERR_BUFFER_OVERFLOW;

			strtokbuf[stbi] = 0;
			printf("%s\n", strtokbuf);
			stbi = 0;

			continue;
		}

		if (LOV_TOK_SEP_CHAR(ch))
		{
			if (tbi == LOV_MAX_TOKEN_SIZE)
				return FR_ERR_BUFFER_OVERFLOW;

			tokbuf[tbi] = 0;
			toklen = strlen(tokbuf);
			kw = lov_in_kw_set(tokbuf, toklen);
			if (!kw)
				LOV_TOK_PRINTF(tokbuf);
			else
				LOV_KW_PRINTF(tokbuf);
			tbi = 0;
			if (!LOV_IGNORE_CHAR(ch))
				LOV_TOK_SEP_PRINTF(ch);

			continue;
		}

		if (tbi >= LOV_MAX_TOKEN_SIZE - 1)
			return FR_ERR_BUFFER_OVERFLOW;
		tokbuf[tbi++] = ch;
	}

	return FR_SUCCESS;
}

lov_fnret lov_tokenise(uint32_t count, const char **files)
{
	FILE *file;

	for (uint32_t i = 0; i < count; ++i)
	{
		file = fopen(files[i], "r");
		if (!file)
			return FR_ERR_FAILURE;
		lov_I_tokenise(file);
		fclose(file);
	}

	return FR_SUCCESS;
}
