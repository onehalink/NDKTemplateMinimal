/**
* Unicode Helper APIs
*/

#pragma once

#include "../Base.h"



struct FUnicode
{
	SizeType(*GetUTF8ElementCount)(const Char8* inUTF8, Char8 terminatedCharacter);
	SizeType(*GetUTF16ElementCount)(const Char8* inUTF16, Char16 terminatedCharacter);

	SizeType(*GetCodePointCountFromUTF8Elements)(const Char8* inUTF8, SizeType count);
	SizeType(*GetCodePointCountFromUTF16Elements)(const Char16* inUTF16, SizeType count);
	SizeType(*GetUTF8ElementCountFromCodePoints)(const CodePoint* in, SizeType count);
	SizeType(*GetUTF16ElementCountFromCodePoints)(const CodePoint* in, SizeType count);

	/**
	* Convert UTF encoding sequence to codepoint
	* 
	* 
	* @param output		As a output param, and calculated codepoint will be store in
	* 
	* @return Indicate how many UTF elements had been used
	*/
	SizeType(*ConvertFromUTF8)(CodePoint* output, const Char8* inUTF8Sequence);
	SizeType(*ConvertFromUTF16)(CodePoint* output, const Char16* inUTF16Sequence);
	/**
	* Convert codepoint to UTF encoding sequence
	* 
	* 
	* @param output		As a ouput param, and calculated UTF sequnece will be store in
	* 
	* @return Indicate a codepoint will be converted to how many UTF elements
	*/
	SizeType(*ConvertToUTF8)(Char8* output, CodePoint codepoint);
	SizeType(*ConvertToUTF16)(Char16* output, CodePoint codepoint);
};

extern ENGINE_API struct FUnicode FUnicode;