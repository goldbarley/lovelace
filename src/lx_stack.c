#include "lov/lexer.h"

static uint64_t Lov_Fts_Tok_Head = 0;
static uint64_t Lov_Fts_Strtok_Head = 0;

#include "lxI_stack.c"

lov_fnret lov_lx_fts_push(char *tok, enum lov_lx_token_type toktype)
{

	switch(toktype)
	{
		case LOV_LX_TOKTYPE_STD:
			return lov_lxI_fts_push_stdtok(tok);
		case LOV_LX_TOKTYPE_STR:
			return lov_lxI_fts_push_strtok(tok);

		default:
			return FR_ERR_INVALID_ARGUMENT;
	}
}

const char *lov_lx_fts_pop(enum lov_lx_token_type toktype)
{
	switch(toktype)
	{
		case LOV_LX_TOKTYPE_STD:
			return lov_lxI_fts_pop_stdtok();
		case LOV_LX_TOKTYPE_STR:
			return lov_lxI_fts_pop_strtok();

		default:
			return NULL;
	}
}

const char *lov_lx_fts_peek(enum lov_lx_token_type toktype)
{
	switch(toktype)
	{
		case LOV_LX_TOKTYPE_STD:
			return lov_lxI_fts_peek_stdtok();
		case LOV_LX_TOKTYPE_STR:
			return lov_lxI_fts_peek_strtok();

		default:
			return NULL;
	}
}
