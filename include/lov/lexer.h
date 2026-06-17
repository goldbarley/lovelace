#ifndef LOV_LEXER_H
#define LOV_LEXER_H

#include "attr.h"
#include "common.h"
#include "tokens.h"

#include <stdint.h>

#define lov_tokenize lov_tokenise

#define LOV_IGNORE_CHAR(c) \
	((c) == LOV_ICHAR_CR || (c) == LOV_ICHAR_HTAB || (c) == LOV_ICHAR_LF \
		|| (c) == LOV_ICHAR_SPACE)

#define LOV_TOK_SEP_CHAR(c) \
	((c) == LOV_TSCHAR_COLON || (c) == LOV_TSCHAR_SEMICOLON \
		|| (c) == LOV_TSCHAR_CR || (c) == LOV_TSCHAR_HTAB \
		|| (c) == LOV_TSCHAR_LF || (c) == LOV_TSCHAR_SPACE \
		|| (c) == LOV_TSCHAR_LPAREN || (c) == LOV_TSCHAR_RPAREN)

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
		|| (c) == LOV_TSCHAR_LPAREN || (c) == LOV_TSCHAR_RPAREN);
}

lov_fnret lov_tokenise(uint32_t count, const char **files);

#endif /* LOV_LEXER_H */
