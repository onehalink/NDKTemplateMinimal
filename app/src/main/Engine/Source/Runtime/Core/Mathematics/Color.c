#include "Color.h"



static Color Blend(const Color* source, const Color* destination)
{
	RealType alpha			= source->a;
	RealType oneMinusAlpha	= 1 - alpha;

	Color ret;
	ret.r = source->r * alpha + destination->r * oneMinusAlpha;
	ret.g = source->g * alpha + destination->g * oneMinusAlpha;
	ret.b = source->b * alpha + destination->b * oneMinusAlpha;

	return ret;
}

static RealType Luminance(const Color* instance)
{
	//const RealType weight[3] = { 0.2126, 0.7152, 0.0722 };

	return 
		instance->r * 0.2126 +
		instance->g * 0.7152 +
		instance->b * 0.0722;
}

static Color Darkened(const Color* instance, RealType amount)
{
	RealType percent = 1 - amount;

	Color ret;
	ret.r = instance->r * percent;
	ret.g = instance->g * percent;
	ret.b = instance->b * percent;
	ret.a = instance->a;

	return ret;
}

static Color Lightened(const Color* instance, RealType amount)
{
	Color ret;
	ret.r = instance->r + ( 1 - instance->r ) * amount;
	ret.g = instance->g + ( 1 - instance->g ) * amount;
	ret.b = instance->b + ( 1 - instance->b ) * amount;
	ret.a = instance->a;

	return ret;
}

static Color ToLinear(const Color* instance)
{
	const RealType exponent = 2.2;

	Color ret;
	ret.r = FMath.Power(instance->r, exponent);
	ret.g = FMath.Power(instance->g, exponent);
	ret.b = FMath.Power(instance->b, exponent);
	ret.a = instance->a;

	return ret;
}

static Color ToSrgb(const Color* instance)
{
	const RealType exponent = 1 / 2.2;

	Color ret;
	ret.r = FMath.Power(instance->r, exponent);
	ret.g = FMath.Power(instance->g, exponent);
	ret.b = FMath.Power(instance->b, exponent);
	ret.a = instance->a;

	return ret;
}

static Color Add(const Color* leftHandSide, const Color* rightHandSide)
{
	Color ret;
	ret.r = leftHandSide->r + rightHandSide->r;
	ret.g = leftHandSide->g + rightHandSide->g;
	ret.b = leftHandSide->b + rightHandSide->b;
	ret.a = leftHandSide->a + rightHandSide->a;

	return ret;
}

static Color Subtract(const Color* leftHandSide, const Color* rightHandSide)
{
	Color ret;
	ret.r = leftHandSide->r - rightHandSide->r;
	ret.g = leftHandSide->g - rightHandSide->g;
	ret.b = leftHandSide->b - rightHandSide->b;
	ret.a = leftHandSide->a - rightHandSide->a;

	return ret;
}

static Color Multiply(const Color* leftHandSide, const Color* rightHandSide)
{
	Color ret;
	ret.r = leftHandSide->r * rightHandSide->r;
	ret.g = leftHandSide->g * rightHandSide->g;
	ret.b = leftHandSide->b * rightHandSide->b;
	ret.a = leftHandSide->a * rightHandSide->a;

	return ret;
}

static Color MultiplyCS(const Color* instance, RealType scalar)
{
	Color ret;
	ret.r = instance->r * scalar;
	ret.g = instance->g * scalar;
	ret.b = instance->b * scalar;
	ret.a = instance->a * scalar;

	return ret;
}

static Color Divide(const Color* instance, RealType scalar)
{
	Color ret;
	ret.r = instance->r / scalar;
	ret.g = instance->g / scalar;
	ret.b = instance->b / scalar;
	ret.a = instance->a / scalar;

	return ret;
}


struct FColor FColor =
{
	{ 0, 0, 0, 1},
	{ 1, 1, 1, 1},
	{ 1, 0, 0, 1},
	{ 0, 1, 0, 1},
	{ 0, 0, 1, 1},
	{ 1, 1, 0, 1},
	{ 0, 1, 1, 1},
	{ 1, 0, 1, 1},

	Blend,
	Luminance,
	Darkened,
	Lightened,
	ToLinear,
	ToSrgb,
	Add,
	Subtract,
	Multiply,
	MultiplyCS,
	Divide,
};
