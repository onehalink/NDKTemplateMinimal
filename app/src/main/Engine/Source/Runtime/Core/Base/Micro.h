/**
* Predefined Micros
*/

#pragma once



/**
* Compiler
*
*
* Supported:
* 1.Microsoft C compiler(for Windows)
* 2.GCC(for Linux)
* 3.Clang(for android)
*/
#if defined(_MSC_VER)
#define COMPILER_MSVC
#elif defined(__GNUC__)
#define COMPILER_GCC
#elif defined(__clang__)
#define COMPILER_CLANG
#else
#error "Unknown C compiler"
#endif


/**
* Standard
* 
* 
* Required:
* C11 or later
*/
#if !defined(__cplusplus) & ( __STDC_VERSION__ < 201112L )
#error "C11 required"
#endif


/**
* Platform
*
*
* Supported:
* 1.Windows 64-bit
* 2.Linux
* 3.Android
*/
#if defined(COMPILER_MSVC) & defined(_WIN64)
#define PLATFORM_WINDOWS
#elif defined(COMPILER_GCC) & defined(__linux__)
#define PLATFORM_LINUX
#elif 1
#define PLATFORM_ANDROID
#else
#error "Current platform is not supported"
#endif

//#define PLATFORM_ANDROID


/**
* Export/Import dynamic link library
* 
* 
* Note:
* Used by this:			[Export]
* Used by the other:	[Import]
*/
#if defined(COMPILER_MSVC)
#define DLL_EXPORT	__declspec(dllexport)
#define DLL_IMPORT	__declspec(dllimport)
#elif defined(COMPILER_GCC) | defined(COMPILER_CLANG)
#define DLL_EXPORT	__attribute__((visibility("default")))
#define DLL_IMPORT
#else
#error "DLL_EXPORT and DLL_IMPORT are undefined"
#endif

#if !defined(ENGINE_API_IMPORTS)
#define ENGINE_API	DLL_EXPORT
#else
#define ENGINE_API	DLL_IMPORT
#endif


// Text related
#define __STRINGIFY(param)	#param
#define STRINGIFY(param)	__STRINGIFY(param)	// Convert param to a string literal

#define U8TEXT(text)		u8 ## text			// Used to represent UTF8 encoding string literal
#define U16TEXT(text)		L ## text			// Used to represent UTF16 encoding string literal


// Math related
#define SWAP(Type, a, b)	{ Type temporary = a; a = b; b = temporary; } // Swap the value of a and b


// Type conversion
#define CAST(Type, param)							( (Type)(param) )							// Cast param to the other datatype
#define REINTERPRET_CAST(Type, pointer, offset)		CAST( Type, CAST(char*, pointer) + offset )	// Apply offset(in bytes) to a pointer and reinterpret it to the other pointer datatype