#ifndef LOV_LXI_STACK_C_
#define LOV_LXI_STACK_C_

#include "lov/lexer.h"

extern uint64_t Lov_Fts_Tok_Head;
extern uint64_t Lov_Fts_Strtok_Head;

LOV_INLINE
lov_fnret lov_lxI_fts_push_stdtok(char *tok)
{
	if (Lov_Fts_Tok_Head >= LOV_MAX_TOKEN_COUNT - 1)
		return FR_ERR_STACK_OVERFLOW;
	Lov_Final_Token_Stack.ftokstk[Lov_Fts_Tok_Head++] = tok;

	return FR_SUCCESS;
}

LOV_INLINE
lov_fnret lov_lxI_fts_push_strtok(char *tok)
{
	if (Lov_Fts_Strtok_Head >= LOV_MAX_STRTOK_COUNT - 1)
		return FR_ERR_STACK_OVERFLOW;
	Lov_Final_Token_Stack.fstrtokstk[Lov_Fts_Strtok_Head++] = tok;

	return FR_SUCCESS;
}

LOV_INLINE
const char *lov_lxI_fts_pop_stdtok(void)
{
	if (Lov_Fts_Tok_Head == 0)
		return NULL;

	return Lov_Final_Token_Stack.ftokstk[Lov_Fts_Tok_Head--];
}

LOV_INLINE
const char *lov_lxI_fts_pop_strtok(void)
{
	if (Lov_Fts_Strtok_Head == 0)
		return NULL;

	return Lov_Final_Token_Stack.fstrtokstk[Lov_Fts_Strtok_Head--];
}

LOV_INLINE
const char *lov_lxI_fts_peek_stdtok(void)
{
	if (Lov_Fts_Tok_Head == 0)
		return NULL;

	return Lov_Final_Token_Stack.ftokstk[Lov_Fts_Tok_Head];
}

LOV_INLINE
const char *lov_lxI_fts_peek_strtok(void)
{
	if (Lov_Fts_Strtok_Head == 0)
		return NULL;

	return Lov_Final_Token_Stack.fstrtokstk[Lov_Fts_Strtok_Head];
}

#endif /* LOV_LXI_STACK_C_ */
