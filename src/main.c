#include "lov/lexer.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
		return -1;

	lov_fnret ret = 0;

	ret = lov_lx_tokenise(argc - 1, (const char **)(&argv[1]));
	if (ret != FR_SUCCESS)
		return -1;

	return 0;
}
