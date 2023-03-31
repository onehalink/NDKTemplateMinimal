#pragma once

#include "Vector4.h"



typedef union
{
	struct
	{
		RealType
			m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33;
	};
	RealType components[4 * 4];
	Vector4 rows[4];
}
Matrix4;


struct FMatrix4
{
	const Matrix4 Identity;


	Void(*SetRow)(Matrix4* instance, SizeType index, const Vector4* vector4);
	Void(*SetColumn)(Matrix4* instance, SizeType index, const Vector4* vector4);
	Vector4(*GetRow)(const Matrix4* instance, SizeType index);
	Vector4(*GetColumn)(const Matrix4* instance, SizeType index);

	Matrix4(*Transpose)(const Matrix4* instance);


	Matrix4(*Multiply)(const Matrix4* leftHandSide, const Matrix4* rightHandSide);
	Vector4(*MultiplyMV)(const Matrix4* instance, const Vector4* vector4);
};

extern ENGINE_API struct FMatrix4 FMatrix4;