#ifndef LOV_LEXER_H
#define LOV_LEXER_H

#include "attr.h"
#include "common.h"
#include "tokens.h"

#include <stdint.h>

#define lov_lx_tokenize lov_lx_tokenise

enum lov_lx_state_bits
{
	LOV_LXS_STRTOK_BIT,
	LOV_LXS_COMMENT_BIT,
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
lov_bool lov_ignore_char(char c)
{
	return ((c) == LOV_ICHAR_CR || (c) == LOV_ICHAR_HTAB || 
		(c) == LOV_ICHAR_LF || (c) == LOV_ICHAR_SPACE);
}

LOV_INLINE
lov_bool lov_tok_sep_char(char c)
{
	return ((c) == LOV_TSCHAR_COLON || (c) == LOV_TSCHAR_SEMICOLON
		|| (c) == LOV_TSCHAR_CR || (c) == LOV_TSCHAR_HTAB
		|| (c) == LOV_TSCHAR_LF || (c) == LOV_TSCHAR_SPACE
		|| (c) == LOV_TSCHAR_LPAREN || (c) == LOV_TSCHAR_RPAREN
		|| (c) == LOV_TSCHAR_HYPHEN || (c) == LOV_TSCHAR_COMMA
		|| (c) == LOV_TSCHAR_DOT || (c) == LOV_TSCHAR_PLUS
		|| (c) == LOV_TSCHAR_ASTERISK || (c) == LOV_TSCHAR_SLASH
		|| (c) == LOV_TSCHAR_LESSTHAN || (c) == LOV_TSCHAR_GREATERTHAN
		|| (c) == LOV_TSCHAR_AMPERSAND);
}

lov_fnret lov_lx_tokenise(uint32_t count, const char **files);
int32_t lov_lx_comment(void);

#endif /* LOV_LEXER_H */
