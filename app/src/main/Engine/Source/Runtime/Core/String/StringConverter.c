#include "StringConverter.h"



static const Char8* SkipWhiteSpace(const Char8* inCStyleString)
{
	const Char8* p = inCStyleString;

	while (
		*p == '\r' ||
		*p == '\n' ||
		*p == '\t' ||
		*p == ' '
		)
		p++;

	return p;
}

static Bool IsNumber(Char8 code)
{
	if ( code >= '0' && code <= '9' )
		return True;

	return False;
}

static Int32 FindDot(const Char8* inCStyleString)
{
	const Char8* p = inCStyleString;

	for (SizeType index = 0; p[index] != 0x00; index++)
	{
		if ( *p == '.' )
			return index;

		p++;
	}

	return -1;
}


static Bool TryParseBool(Bool* output, const Char8* inAsciiString)
{
	const Char8* p = SkipWhiteSpace(inAsciiString);

	if ( *p == 'f' || *p == 'F' )
	{
		if (output)
			*output = False;

		return True;
	}

	if ( *p == 't' || *p == 'T' )
	{
		if (output)
			*output = True;

		return True;
	}

	return False;
}

static Bool TryParseInt32(Int32* output, const Char8* inAsciiString)
{
	const Char8* p = SkipWhiteSpace(inAsciiString);

	Int32 sign = 1;
	{
		if ( *p == '+' )
			p++;

		if ( *p == '-' )
		{
			sign = -1;

			p++;
		}
	}

	if ( !IsNumber(*p) )
		return False;

	Int32 number = 0;
	while ( IsNumber(*p) )
	{
		number *= 10;
		number += *p - '0';

		p++;
	}

	if (output)
		*output = number * sign;

	return True;
}

static Bool TryParseFloat32(Float32* output, const Char8* inAsciiString)
{
	const Char8* p = SkipWhiteSpace(inAsciiString);

	Int32 integerPart;
	if ( !FStringConverter.TryParseInt32(&integerPart, inAsciiString) )
		return False;

	Int32 dot = FindDot(inAsciiString);
	if( dot == -1 )
	{
		if (output)
			*output = integerPart;

		return True;
	}

	Float32 fractionPart;
	{
		const Char8* p = inAsciiString + (dot + 1);

		Int32 number	= 0;
		Int32 N			= 1;

		while ( IsNumber(*p) )
		{
			number *= 10;
			number += *p - '0';

			N *= 10;

			p++;
		}

		fractionPart = CAST(Float32, number) / N;
	}


	if (output)
		*output = integerPart + fractionPart * ( integerPart < 0 ? -1 : 1 );

	return True;
}

static Bool TryConvertBool(Char8* inBuffer, SizeType inSize, Bool value)
{
	return False;
}

static Bool TryConvertInt32(Char8* inBuffer, SizeType inSize, Int32 value)
{
	return False;
}

static Bool TryConvertFloat32(Char8* inBuffer, SizeType inSize, Float32 value)
{
	return False;
}


struct FStringConverter FStringConverter =
{
	TryParseBool,
	TryParseInt32,
	TryParseFloat32,
	TryConvertBool,
	TryConvertInt32,
	TryConvertFloat32,
};
