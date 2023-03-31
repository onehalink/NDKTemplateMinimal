#pragma once

#include "Matrix4.h"



struct FMatrix4Extension
{
	Matrix4(*RotateX)(RealType radians);
	Matrix4(*RotateY)(RealType radians);
	Matrix4(*RotateZ)(RealType radians);
	Matrix4(*Scale)(RealType scaleX, RealType scaleY, RealType scaleZ);
	Matrix4(*Translate)(RealType translationX, RealType translationY, RealType translationZ);
};

extern ENGINE_API struct FMatrix4Extension FMatrix4Extension;