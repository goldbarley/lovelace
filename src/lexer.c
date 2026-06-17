#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif /* _MSC_VER */

#include "lov/debug.h"
#include "lov/dict.h"
#include "lov/lexer.h"

#include <stdio.h>
#include <string.h>

lov_fnret lov_I_tokenise(FILE *file)
{
	register uint64_t tc = 0;
	register int32_t ch;
	int32_t nextch;
	register uint32_t tbi = 0;
	uint64_t toklen = 0;
	register uint64_t ntok = 0;
	char tokbuf[LOV_MAX_TOKEN_SIZE] = {0};
	uint32_t stbi = 0;
	uint64_t nstrtok = 0;
	char strtokbuf[LOV_MAX_STRTOK_SIZE] = {0};
	lov_bool instr = LOV_FALSE;
	struct lov_kw *kw = NULL;
	lov_bool iscmnt = LOV_FALSE;
	char dump[512] = {0};


	while ((ch = fgetc(file)) != EOF)
	{
		if (ch == LOV_CHAR_HYPHEN)
		{
			nextch = fgetc(file);
			if (nextch == LOV_CHAR_HYPHEN)
				iscmnt = LOV_TRUE;
			else if (nextch != EOF)
				fseek(file, -1, SEEK_CUR);
		}
		if (iscmnt)
		{
			fgets(dump, 512 * sizeof(char), file);
			iscmnt = LOV_FALSE;
			continue;
		}

		++tc;

		instr = ch == LOV_CHAR_DBLQUOTE ? !instr : instr;
		if (instr)
		{
			if (ch == LOV_CHAR_DBLQUOTE)
				continue;

			strtokbuf[stbi++] = ch;
			if (stbi >= LOV_MAX_STRTOK_SIZE - 1)
				return FR_ERR_BUFFER_OVERFLOW;

			continue;
		}
		else if (!instr && stbi)
		{
			++nstrtok;
			strtokbuf[stbi] = 0;
			LOV_PRINT_STRTOK(strtokbuf);
			stbi = 0;

			continue;
		}

		if (lov_tok_sep_char(ch))
		{
			++ntok;
			if (tbi == LOV_MAX_TOKEN_SIZE)
				return FR_ERR_BUFFER_OVERFLOW;
			
			if (tbi)
			{
				tokbuf[tbi] = 0;
				toklen = strlen(tokbuf);
				kw = lov_in_kw_set(tokbuf, toklen);
				if (!kw)
					LOV_PRINT_IDENT(tokbuf);
				else
					LOV_PRINT_KW(tokbuf);
				tbi = 0;
				if (!lov_ignore_char(ch))
					LOV_PRINT_TOK_SEP(ch);

				continue;
			}
		}

		if (lov_ignore_char(ch))
			continue;

		if (tbi >= LOV_MAX_TOKEN_SIZE - 1)
			return FR_ERR_BUFFER_OVERFLOW;
		tokbuf[tbi++] = ch;
	}

	puts("");
	printf("TOTAL_CHARACTERS: %lli\n", tc);
	printf("TOTAL_TOKENS: %lli\n", ntok);
	printf("TOTAL_STRING_TOKENS: %lli\n", nstrtok);
	puts("");

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
