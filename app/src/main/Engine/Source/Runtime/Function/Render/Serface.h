#pragma once

#include "../../Core.h"



typedef enum
{
	SerfaceClearFlag_Color		= 1 << 0,
	SerfaceClearFlag_Depth		= 1 << 1,
	SerfaceClearFlag_Stencil	= 1 << 2,

	SerfaceClearFlag_All		= SerfaceClearFlag_Color | SerfaceClearFlag_Depth | SerfaceClearFlag_Stencil,
}
SerfaceClearFlag;


typedef struct
{
	SizeType width;
	SizeType height;
	SizeType elementCount;
	RealType aspect;

	Color*		colorBuffer;
	RealType*	depthBuffer;
	Byte*		stencilBuffer;
}
Serface;


struct FSerface
{
	Serface(*Construct)(SizeType width, SizeType height);
	Void(*Destruct)(Serface* instance);


	Void(*Clear)(Serface* instance, SerfaceClearFlag flag, const Color* clearColor, RealType clearDepth, Byte clearStencil);
	Void(*ClearColor)(Serface* instance, const Color* color);
	Void(*ClearDepth)(Serface* instance, RealType depth);
	Void(*ClearStencil)(Serface* instance, Byte stencil);

	Void(*FlipHorizontal)(Serface* instance);
	Void(*FlipVertical)(Serface* instance);

	Void(*CopyTo)(const Serface* instance, Void* RenderTarget);

	Void(*SetPixel)(Serface* instance, SizeType x, SizeType y, const Color* color);
	Color(*GetPixel)(const Serface* instance, SizeType x, SizeType y);
	Void(*SetDepth)(Serface* instance, SizeType x, SizeType y, RealType depth);
	RealType(*GetDepth)(const Serface* instance, SizeType x, SizeType y);
	Void(*SetStencil)(Serface* instance, SizeType x, SizeType y, Byte stencil);
	Byte(*GetStencil)(const Serface* instance, SizeType x, SizeType y);
};

extern ENGINE_API struct FSerface FSerface;