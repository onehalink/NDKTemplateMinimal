#include "Matrix4.h"



static Void SetRow(Matrix4* instance, SizeType index, const Vector4* vector4)
{
	instance->rows[index] = *vector4;
}

static Void SetColumn(Matrix4* instance, SizeType index, const Vector4* vector4)
{
	for (SizeType iteration = 0; iteration < 4; iteration++)
		instance->components[4 * iteration + index] = vector4->components[iteration];
}

static Vector4 GetRow(const Matrix4* instance, SizeType index)
{
	return instance->rows[index];
}

static Vector4 GetColumn(const Matrix4* instance, SizeType index)
{
	Vector4 ret;
	for (SizeType iteration = 0; iteration < 4; iteration++)
		ret.components[iteration] = instance->components[4 * iteration + index];

	return ret;
}

static Matrix4 Transpose(const Matrix4* instance)
{
	Matrix4 ret;
	for (SizeType y = 0; y < 4; y++)
		for (SizeType x = 0; x < 4; x++)
			ret.components[4 * x + y] = instance->components[4 * y + x];

	return ret;
}

static Matrix4 Multiply(const Matrix4* leftHandSide, const Matrix4* rightHandSide)
{
	Matrix4 ret;
	for (SizeType y = 0; y < 4; y++)
	{
		Vector4 column = FMatrix4.GetColumn(rightHandSide, y);

		for (SizeType x = 0; x < 4; x++)
			ret.components[4 * x + y] = FVector4.Dot( leftHandSide->rows + x, &column );
	}

	return ret;
}

static Vector4 MultiplyMV(const Matrix4* instance, const Vector4* vector4)
{
	Vector4 ret;
	for (SizeType index = 0; index < 4; index++)
		ret.components[index] = FVector4.Dot( instance->rows + index, vector4 );

	return ret;
}


struct FMatrix4 FMatrix4 =
{
	{ 
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	},

	SetRow,
	SetColumn,
	GetRow,
	GetColumn,
	Transpose,
	Multiply,
	MultiplyMV,
};
