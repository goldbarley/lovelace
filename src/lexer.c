#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif /* _MSC_VER */

#include "lov/debug.h"
#include "lov/dict.h"
#include "lov/lexer.h"

#include <stdio.h>
#include <string.h>

#define LOV_LX_TOG_STATEBIT(bit) (Lov_Lexer_Info.state ^= 1 << (bit))
#define LOV_LX_SET_STATEBIT(bit) (Lov_Lexer_Info.state |= 1 << (bit))
#define LOV_LX_CLR_STATEBIT(bit) (Lov_Lexer_Info.state &= ~(1 << (bit)))
#define LOV_LX_CHK_STATEBIT(bit) (Lov_Lexer_Info.state & (1 << (bit)))

static struct
{
	FILE *file;
	uint64_t state;
} Lov_Lexer_Info = {0};

int32_t lov_lx_comment()
{
	char fch = LOV_CHAR_HYPHEN;
	register char nch = fgetc(Lov_Lexer_Info.file);
	if (nch == EOF)
	{
		LOV_LX_CLR_STATEBIT(LOV_LXS_COMMENT_BIT);
		return nch;
	}

	char dump[512] = {0};

	if (fch == nch)
	{
		fgets(dump, 512 * sizeof(char), Lov_Lexer_Info.file);
		LOV_LX_SET_STATEBIT(LOV_LXS_COMMENT_BIT);
		return nch;
	}

	LOV_LX_CLR_STATEBIT(LOV_LXS_COMMENT_BIT);
	ungetc(nch, Lov_Lexer_Info.file);
	return nch;
}

lov_fnret lov_lxI_tokenise(void)
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
	struct lov_kw *kw = NULL;
	char dump[512] = {0};


	while ((ch = fgetc(Lov_Lexer_Info.file)) != EOF)
	{
		if (ch == LOV_CHAR_HYPHEN)
		{
			nextch = lov_lx_comment();
			if (nextch == LOV_CHAR_HYPHEN)
			{
				LOV_LX_CLR_STATEBIT(LOV_LXS_COMMENT_BIT);
				continue;
			}
			else if (nextch == EOF)
				break;
		}

		++tc;

		if (ch == LOV_CHAR_DBLQUOTE)
			LOV_LX_TOG_STATEBIT(LOV_LXS_STRTOK_BIT);
		if (LOV_LX_CHK_STATEBIT(LOV_LXS_STRTOK_BIT))
		{
			if (ch == LOV_CHAR_DBLQUOTE)
				continue;

			strtokbuf[stbi++] = ch;
			if (stbi >= LOV_MAX_STRTOK_SIZE - 1)
				return FR_ERR_BUFFER_OVERFLOW;

			continue;
		}
		else if (!LOV_LX_CHK_STATEBIT(LOV_LXS_STRTOK_BIT) && stbi)
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

lov_fnret lov_lx_tokenise(uint32_t count, const char **files)
{
	lov_fnret ret = FR_SUCCESS;
	for (uint32_t i = 0; i < count && ret == FR_SUCCESS; ++i)
	{
		memset(&Lov_Lexer_Info, 0, sizeof(Lov_Lexer_Info));
		Lov_Lexer_Info.file = fopen(files[i], "r");
		if (!Lov_Lexer_Info.file)
			return FR_ERR_FAILURE;
		ret = lov_lxI_tokenise();
		fclose(Lov_Lexer_Info.file);
	}

	return ret;
}
