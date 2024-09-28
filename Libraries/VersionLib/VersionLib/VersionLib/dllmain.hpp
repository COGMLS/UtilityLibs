#pragma once

// add headers that you want to pre-compile here
#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
	// Windows Header Files
	#include <windows.h>
#endif // !WIN32