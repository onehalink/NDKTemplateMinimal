#pragma once

#include "Matrix3.h"



struct FMatrix3Extension
{
	Matrix3(*Rotate)(RealType radians);
	Matrix3(*Scale)(RealType scaleX, RealType scaleY);
	Matrix3(*Translate)(RealType translationX, RealType translationY);
};

extern ENGINE_API struct FMatrix3Extension FMatrix3Extension;