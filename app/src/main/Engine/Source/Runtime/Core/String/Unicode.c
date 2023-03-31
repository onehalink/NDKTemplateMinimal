#include "Unicode.h"



static SizeType GetUTF8ElementCount(const Char8* inUTF8, Char8 terminatedCharacter)
{
	SizeType ret = 0;

	while ( inUTF8[ret] != terminatedCharacter )
		ret++;

	return ret;
}

static SizeType GetUTF16ElementCount(const Char8* inUTF16, Char16 terminatedCharacter)
{
	SizeType ret = 0;

	while ( inUTF16[ret] != terminatedCharacter )
		ret++;

	return ret;
}

static SizeType GetCodePointCountFromUTF8Elements(const Char8* inUTF8, SizeType count)
{
	SizeType ret = 0;

	for (SizeType offset = 0; offset < count;)
	{
		Char8 code = inUTF8[offset];

		if ( (code & 0x80) == 0 )
			offset += 1;
		else if ( (code & 0xE0) == 0xC0 )
			offset += 2;
		else if ( (code & 0xF0) == 0xE0 )
			offset += 3;
		else if ( (code & 0xF8) == 0xF0 )
			offset += 4;
		else // invalid condition
			break;

		ret++;
	}

	return ret;
}

static SizeType GetCodePointCountFromUTF16Elements(const Char16* inUTF16, SizeType count)
{
	SizeType ret = 0;

	for (SizeType offset = 0; offset < count;)
	{
		Char16 code = inUTF16[offset];

		if ( (code & 0xFC00) == 0xD800 )
			offset += 2;
		else
			offset += 1;

		ret++;
	}

	return ret;
}

static SizeType GetUTF8ElementCountFromCodePoints(const CodePoint* in, SizeType count)
{
	SizeType ret = 0;

	for (SizeType index = 0; index < count; index++)
	{
		CodePoint code = in[index];

		if ( code <= 0x7F )
			ret += 1;
		else if ( code <= 0x7FF )
			ret += 2;
		else if ( code <= 0xFFFF )
			ret += 3;
		else if ( code <= 0x10FFFF )
			ret += 4;
		else // invalid condition
			break;
	}

	return ret;
}

static SizeType GetUTF16ElementCountFromCodePoints(const CodePoint* in, SizeType count)
{
	SizeType ret = 0;

	for (SizeType index = 0; index < count; index++)
	{
		CodePoint code = in[index];

		if ( code <= 0xFFFF )
			ret += 1;
		else if ( code <= 0x10FFFF )
			ret += 2;
		else // invalid contidion
			break;
	}

	return ret;
}

static SizeType ConvertFromUTF8(CodePoint* output, const Char8* inUTF8Sequence)
{
	SizeType ret = 0;

	CodePoint codepoint = 0;

	const Char8* c0 = inUTF8Sequence + 0;
	const Char8* c1 = inUTF8Sequence + 1;
	const Char8* c2 = inUTF8Sequence + 2;
	const Char8* c3 = inUTF8Sequence + 3;

	if ( (*c0 & 0x80) == 0 )
	{
		codepoint = *c0;

		ret = 1;
	}
	else if ( (*c0 & 0xE0) == 0xC0 )
	{
		codepoint |= (*c0 & 0x1F) << 6;
		codepoint |= (*c1 & 0x3F) << 0;

		ret = 2;
	}
	else if ( (*c0 & 0xF0) == 0xE0 )
	{
		codepoint |= (*c0 & 0x0F) << 12;
		codepoint |= (*c1 & 0x3F) <<  6;
		codepoint |= (*c2 & 0x3F) <<  0;

		ret = 3;
	}
	else if ( (*c0 & 0xF8) == 0xF0 )
	{
		codepoint |= (*c0 & 0x07) << 18;
		codepoint |= (*c1 & 0x3F) << 12;
		codepoint |= (*c2 & 0x3F) <<  6;
		codepoint |= (*c3 & 0x3F) <<  0;

		ret = 4;
	}

	if (output)
		*output = codepoint;

	return ret;
}

static SizeType ConvertFromUTF16(CodePoint* output, const Char16* inUTF16Sequence)
{
	SizeType ret = 0;

	CodePoint codepoint = 0;

	const Char16* c0 = inUTF16Sequence + 0;
	const Char16* c1 = inUTF16Sequence + 1;

	if ( (*c0 & 0xFC) == 0xD800 )
	{
		codepoint |= (*c0 & 0x3FF) << 10;
		codepoint |= (*c1 & 0x3FF) <<  0;
		codepoint += 0x10000;

		ret = 2;
	}
	else
	{
		codepoint = *c0;

		ret = 1;
	}

	if (output)
		*output = codepoint;

	return ret;
}

static SizeType ConvertToUTF8(Char8* output, CodePoint codepoint)
{
	SizeType ret = 0;

	Char8* c0 = output + 0;
	Char8* c1 = output + 1;
	Char8* c2 = output + 2;
	Char8* c3 = output + 3;

	if ( codepoint <= 0x7F ) // 7-bit mask
	{
		*c0 = codepoint;

		ret = 1;
	}
	else if ( codepoint <= 0x7FF ) // 11-bit(5 + 6) mask
	{
		*c0 = ( (codepoint >> 6) & 0x1F ) | 0xC0;
		*c1 = ( (codepoint >> 0) & 0x3F ) | 0x80;

		ret = 2;
	}
	else if ( codepoint <= 0xFFFF ) // 16-bit(4 + 6 + 6) mask
	{
		*c0 = ( (codepoint >> 12) & 0x0F ) | 0xE0;
		*c1 = ( (codepoint >>  6) & 0x3F ) | 0x80;
		*c2 = ( (codepoint >>  0) & 0x3F ) | 0x80;

		ret = 3;
	}
	else if ( codepoint <= 0x10FFFF ) // 21-bit(3 + 6 + 6 + 6) mask
	{
		*c0 = ( (codepoint >> 18) & 0x07 ) | 0xF0;
		*c1 = ( (codepoint >> 12) & 0x3F ) | 0x80;
		*c2 = ( (codepoint >>  6) & 0x3F ) | 0x80;
		*c3 = ( (codepoint >>  0) & 0x3F ) | 0x80;

		ret = 4;
	}

	return ret;
}

static SizeType ConvertToUTF16(Char16* output, CodePoint codepoint)
{
	SizeType ret = 0;

	Char16* c0 = output + 0;
	Char16* c1 = output + 1;

	if ( codepoint <= 0xFFFF )
	{
		*c0 = codepoint;

		ret = 1;
	}
	else if ( codepoint <= 0x10FFFF )
	{
		codepoint -= 0x10000;

		*c0 = ( (codepoint >> 10) & 0x3FF ) | 0xD800;
		*c1 = ( (codepoint >>  0) & 0x3FF ) | 0xDC00;

		ret = 2;
	}

	return ret;
}


struct FUnicode FUnicode =
{
	GetUTF8ElementCount,
	GetUTF16ElementCount,
	GetCodePointCountFromUTF8Elements,
	GetCodePointCountFromUTF16Elements,
	GetUTF8ElementCountFromCodePoints,
	GetUTF16ElementCountFromCodePoints,
	ConvertFromUTF8,
	ConvertFromUTF16,
	ConvertToUTF8,
	ConvertToUTF16,
};
