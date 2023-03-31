#include "Matrix4Extension.h"



static Matrix4 RotateX(RealType radians)
{
	RealType sine	= FMath.Sine(radians);
	RealType cosine = FMath.Cosine(radians);

	/**    Y   Z
	* [xx][xx][xx]
	* [xx][11][12]
	* [xx][21][22]
	*/
	Matrix4 ret = FMatrix4.Identity;
	ret.m11		= cosine;
	ret.m21		= sine;
	ret.m12		= -sine;
	ret.m22		= cosine;

	return ret;
}

static Matrix4 RotateY(RealType radians)
{
	RealType sine	= FMath.Sine(radians);
	RealType cosine = FMath.Cosine(radians);

	/**X       Z
	* [00][xx][02]
	* [xx][xx][xx]
	* [20][xx][22]
	*/
	Matrix4 ret = FMatrix4.Identity;
	ret.m00		= cosine;
	ret.m20		= -sine;
	ret.m02		= sine;
	ret.m22		= cosine;

	return ret;
}

static Matrix4 RotateZ(RealType radians)
{
	RealType sine	= FMath.Sine(radians);
	RealType cosine = FMath.Cosine(radians);

	/**X   Y
	* [00][01][xx]
	* [10][11][xx]
	* [xx][xx][xx]
	*/
	Matrix4 ret	= FMatrix4.Identity;
	ret.m00		= cosine;
	ret.m10		= sine;
	ret.m01		= -sine;
	ret.m11		= cosine;

	return ret;
}

static Matrix4 Scale(RealType scaleX, RealType scaleY, RealType scaleZ)
{
	Matrix4 ret	= FMatrix4.Identity;
	ret.m00		= scaleX;
	ret.m11		= scaleY;
	ret.m22		= scaleZ;

	return ret;
}

static Matrix4 Translate(RealType translationX, RealType translationY, RealType translationZ)
{
	Matrix4 ret = FMatrix4.Identity;
	ret.m03		= translationX;
	ret.m13		= translationY;
	ret.m23		= translationZ;

	return ret;
}


struct FMatrix4Extension FMatrix4Extension =
{
	RotateX,
	RotateY,
	RotateZ,
	Scale,
	Translate,
};
