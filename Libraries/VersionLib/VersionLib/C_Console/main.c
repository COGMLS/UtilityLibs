#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if __STDC_VERSION__ < 202311L
#include <stdbool.h>
#endif // Test C23

int main(int argc, const char* argv[])
{
	bool testVersionStrFormats = false;
	bool testVersionOperators = false;
	bool testVersionExceptions = false;
	bool testVersionStrComp = false;
	bool testVersionStructComp = false;
	bool test_toVersionStruct3 = false;

	for (int i = 0; i < argc; i++)
	{
		#ifdef DEBUG
		printf("%s", argv[i]);
		#endif // !DEBUG
	}

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-test-formats") == 0)
		{
			testVersionStrFormats = true;
		}

		if (strcmp(argv[i], "-test-operators") == 0)
		{
			testVersionOperators = true;
		}

		if (strcmp(argv[i], "-test-exceptions") == 0)
		{
			testVersionExceptions = true;
		}

		if (strcmp(argv[i], "-test-string-comparison") == 0)
		{
			testVersionStrComp = true;
		}

		if (strcmp(argv[i], "-test-struct-comparison") == 0)
		{
			testVersionStructComp = true;
		}

		if (strcmp(argv[i], "-test2versionstruct3") == 0)
		{
			test_toVersionStruct3 = true;
		}
	}

	return 0;
}