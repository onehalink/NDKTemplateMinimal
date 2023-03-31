/**
* Used By The Other C Project
* 
* 
* Note:
* Build this project as a dynamic link library
*/

#pragma once



/**
* [Include]
* 
* Path(Visual Studio Micro): $(SolutionDir)C/Engine/Source/Include/
*/


/**
* [Link]
* 
* Path(Visual Studio Micro): $(SolutionDir)Binary/C/$(Configuration)/$(Platform)/
*/
//#pragma comment(lib, "Engine")


/**
* For Visual Studio
* 
* Output:		$(SolutionDir)Binary/C/$(Configuration)/$(Platform)/
* Intermediate:	$(SolutionDir)Binary/C/$(Configuration)/$(Platform)/$(ProjectName)/
*/


/**
* Import engine
* 
* 
* Note:
* As a flag to define ENGINE_API as DLL_IMPORT(default is DLL_EXPORT)
*/
#if !defined(ENGINE_API_IMPORTS)
#define ENGINE_API_IMPORTS
#endif


// APIs
#include "../Runtime/Core.h"

#include "../Runtime/Function/Render/Serface.h"
#include "../Runtime/Function/Render/ImmediateModeUI/Text.h"

#include "../Runtime/Resource/Bitmap.h"
#include "../Runtime/Resource/Wave.h"