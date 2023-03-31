#pragma once

#include "../../../Core.h"



struct FAsciiGlyphInfo
{
	const SizeType CodePointOffset;
	const SizeType Count;

	const SizeType Width;
	const SizeType Height;

	const Byte Masks[95][16];
};

extern ENGINE_API struct FAsciiGlyphInfo FAsciiGlyphInfo;