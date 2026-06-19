#ifndef LOV_LEXER_H
#define LOV_LEXER_H

#include "attr.h"
#include "common.h"
#include "tokens.h"

#include <stdint.h>

extern struct lov_lx_ftokstack
{
	char *ftokstk[LOV_MAX_TOKEN_COUNT];
	char *fstrtokstk[LOV_MAX_STRTOK_COUNT];
} Lov_Final_Token_Stack;

#define lov_lx_tokenize lov_lx_tokenise

enum lov_lx_state_bits
{
	LOV_LXS_STRTOK_BIT,
	LOV_LXS_COMMENT_BIT,
};

enum lov_lx_token_type
{
	LOV_LX_TOKTYPE_STD,
	LOV_LX_TOKTYPE_STR
};

#define LOV_IGNORE_CHAR(c) \
	((c) == LOV_ICHAR_CR || (c) == LOV_ICHAR_HTAB || (c) == LOV_ICHAR_LF \
		|| (c) == LOV_ICHAR_SPACE)

#define LOV_TOK_SEP_CHAR(c) \
	((c) == LOV_TSCHAR_COLON || (c) == LOV_TSCHAR_SEMICOLON \
		|| (c) == LOV_TSCHAR_CR || (c) == LOV_TSCHAR_HTAB \
		|| (c) == LOV_TSCHAR_LF || (c) == LOV_TSCHAR_SPACE \
		|| (c) == LOV_TSCHAR_LPAREN || (c) == LOV_TSCHAR_RPAREN \
		|| (c) == LOV_TSCHAR_HYPHEN || (c) == LOV_TSCHAR_COMMA \
		|| (c) == LOV_TSCHAR_DOT || (c) == LOV_TSCHAR_PLUS \
		|| (c) == LOV_TSCHAR_ASTERISK || (c) == LOV_TSCHAR_SLASH \
		|| (c) == LOV_TSCHAR_LESSTHAN || (c) == LOV_TSCHAR_GREATERTHAN \
		|| (c) == LOV_TSCHAR_AMPERSAND)

LOV_INLINE
lov_bool lov_ignore_char(int32_t c)
{
	return ((c) == LOV_ICHAR_CR || (c) == LOV_ICHAR_HTAB || 
		(c) == LOV_ICHAR_LF || (c) == LOV_ICHAR_SPACE);
}

LOV_INLINE
lov_bool lov_tok_sep_char(int32_t c)
{
	return ((c) == LOV_TSCHAR_COLON || (c) == LOV_TSCHAR_SEMICOLON
		|| (c) == LOV_TSCHAR_CR || (c) == LOV_TSCHAR_HTAB
		|| (c) == LOV_TSCHAR_LF || (c) == LOV_TSCHAR_SPACE
		|| (c) == LOV_TSCHAR_LPAREN || (c) == LOV_TSCHAR_RPAREN
		|| (c) == LOV_TSCHAR_HYPHEN || (c) == LOV_TSCHAR_COMMA
		|| (c) == LOV_TSCHAR_DOT || (c) == LOV_TSCHAR_PLUS
		|| (c) == LOV_TSCHAR_ASTERISK || (c) == LOV_TSCHAR_SLASH
		|| (c) == LOV_TSCHAR_LT || (c) == LOV_CHAR_GT
		|| (c) == LOV_TSCHAR_AMPERSAND);
}

/* Stack functions */
lov_fnret lov_lx_fts_push(char *tok, enum lov_lx_token_type toktype);
const char *lov_lx_fts_pop(enum lov_lx_token_type toktype);
const char *lov_lx_fts_peek(enum lov_lx_token_type toktype);

lov_fnret lov_lx_tokenise(uint32_t count, const char **files);
int32_t lov_lx_comment(void);
uint64_t lov_lx_strtok(void);

#endif /* LOV_LEXER_H */
