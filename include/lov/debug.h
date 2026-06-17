#ifndef LOV_DEBUG_H
#define LOV_DEBUG_H

#define LOV_PRINT_KW(kw) \
	do \
	{ \
		printf("KEYWORD: %s\n", kw); \
	} while (0)

#define LOV_PRINT_TOK(tok) \
	do \
	{ \
		printf("TOKEN: %s\n", tok); \
	} while(0)

#define LOV_PRINT_TOK_SEP(toksep) \
	do \
	{ \
		printf("TOKEN_SEPARATOR: %c\n", toksep); \
	} while(0)

#define LOV_PRINT_STRTOK(strtok) \
	do \
	{ \
		printf("STRING_TOKEN: %s\n", strtok); \
	} while(0)

#define LOV_PRINT_IDENT(ident) \
	do \
	{ \
		printf("IDENTIFIER: %s\n", ident); \
	} while(0)

#endif /* LOV_DEBUG_H */
