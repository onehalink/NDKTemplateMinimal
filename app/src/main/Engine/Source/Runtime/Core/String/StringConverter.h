#pragma once

#include "../Base.h"



struct FStringConverter
{
	Bool(*TryParseBool)(Bool* output, const Char8* inAsciiString);
	Bool(*TryParseInt32)(Int32* output, const Char8* inAsciiString);
	Bool(*TryParseFloat32)(Float32* output, const Char8* inAsciiString);

	/**
	* Convert Bool/Int32/Float32's value to a Ascii String representation with 0x00 as terminated character
	* 
	* 
	* Note:
	* Currently is not implementated, and dont to use them
	*/
	Bool(*TryConvertBool)(Char8* inBuffer, SizeType inSize, Bool value);
	Bool(*TryConvertInt32)(Char8* inBuffer, SizeType inSize, Int32 value);
	Bool(*TryConvertFloat32)(Char8* inBuffer, SizeType inSize, Float32 value);
};

extern ENGINE_API struct FStringConverter FStringConverter;