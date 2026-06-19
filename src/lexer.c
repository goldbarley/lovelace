#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif /* _MSC_VER */

#include "lov/dict.h"
#include "lov/lexer.h"

#include <stdio.h>
#include <string.h>

#define LOV_LX_TOG_STATEBIT(bit) (Lov_Lexer_Info.state ^= 1 << (bit))
#define LOV_LX_SET_STATEBIT(bit) (Lov_Lexer_Info.state |= 1 << (bit))
#define LOV_LX_CLR_STATEBIT(bit) (Lov_Lexer_Info.state &= ~(1 << (bit)))
#define LOV_LX_CHK_STATEBIT(bit) (Lov_Lexer_Info.state & (1 << (bit)))

struct lov_lx_ftokstack Lov_Final_Token_Stack = {0};

static struct lov_lx_info
{
	FILE *file;
	uint64_t state;
	char tokbuf[LOV_MAX_TOKEN_SIZE];
	char strtokbuf[LOV_MAX_STRTOK_SIZE];
} Lov_Lexer_Info = {0};

int32_t lov_lx_comment(void)
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

uint64_t lov_lx_strtok(void)
{
	/* This function is only triggered if char = LOV_CHAR_DBLQUOTE. */

	uint32_t stbi = 0;
	int32_t ch = 0;

	while ((ch = fgetc(Lov_Lexer_Info.file)) != EOF)
	{
		if (ch == LOV_CHAR_DBLQUOTE)
			break;
		Lov_Lexer_Info.strtokbuf[stbi++] = ch;
	}

	LOV_LX_CLR_STATEBIT(LOV_LXS_STRTOK_BIT);

	return stbi;
}

static lov_fnret lov_lxI_tokenise(void)
{
	register uint64_t tc = 0;
	register int32_t ch;
	int32_t nextch;

	register uint32_t tbi = 0;
	uint64_t toklen = 0;
	register uint64_t ntok = 0;

	uint32_t stbi = 0;
	uint64_t strtoklen = 0;
	uint64_t nstrtok = 0;

	struct lov_kw *kw = NULL;

	char dump[512] = {0};

	while ((ch = fgetc(Lov_Lexer_Info.file)) != EOF)
	{
		/* Comment */
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

		/* Strings */
		if (ch == LOV_CHAR_DBLQUOTE)
		{
			LOV_LX_SET_STATEBIT(LOV_LXS_STRTOK_BIT);
			strtoklen = lov_lx_strtok();
			// LOV_PRINT_STRTOK(Lov_Lexer_Info.tokbuf);
			lov_lx_fts_push(Lov_Lexer_Info.strtokbuf,
				LOV_LX_TOKTYPE_STR);
			continue;
		}

		if (lov_tok_sep_char(ch))
		{
			++ntok;
			if (tbi == LOV_MAX_TOKEN_SIZE)
				return FR_ERR_BUFFER_OVERFLOW;
			
			if (tbi)
			{
				Lov_Lexer_Info.tokbuf[tbi] = 0;
				toklen = strlen(Lov_Lexer_Info.tokbuf);
				kw = lov_in_kw_set(Lov_Lexer_Info.tokbuf,
					toklen);
				// if (!kw)
				// 	LOV_PRINT_IDENT(Lov_Lexer_Info.tokbuf);
				// else
				// 	LOV_PRINT_KW(Lov_Lexer_Info.tokbuf);

				lov_lx_fts_push(Lov_Lexer_Info.tokbuf,
					LOV_LX_TOKTYPE_STD);
				tbi = 0;
				if (!lov_ignore_char(ch))
				{
					// LOV_PRINT_TOK_SEP_CHAR(ch);
					lov_lx_fts_push(
						(char []){ch, 0},
						LOV_LX_TOKTYPE_STD
					);
				}

				continue;
			}
		}

		if (lov_ignore_char(ch))
			continue;

		if (tbi >= LOV_MAX_TOKEN_SIZE - 1)
			return FR_ERR_BUFFER_OVERFLOW;
		Lov_Lexer_Info.tokbuf[tbi++] = ch;
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
