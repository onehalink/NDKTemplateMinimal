/**
* Windows OS Special APIs
* 
* 
* Note:
* Dont include this header file directly
*/

#pragma once



#if !defined(PLATFORM_WINDOWS)
#error "This is not a Windows app"
#endif


#define WIN32_LEAN_AND_MAIN
#define NOMINMAX
#include <Windows.h>


// Audio related
#include <dsound.h>
#pragma comment(lib, "dsound")