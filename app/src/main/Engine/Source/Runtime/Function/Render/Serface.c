#include "Serface.h"



static Serface Construct(SizeType width, SizeType height)
{
	SizeType elements = width * height;

	Serface ret;
	FMemory.Clear( &ret, sizeof(Serface) );
	ret.width			= width;
	ret.height			= height;
	ret.elementCount	= elements;

	if ( width == 0 || height == 0 )
		return ret;

	ret.aspect = CAST(RealType, width) / height;

	ret.colorBuffer		= FAllocator.Allocate( sizeof(Color) * elements );
	ret.depthBuffer		= FAllocator.Allocate( sizeof(RealType) * elements );
	ret.stencilBuffer	= FAllocator.Allocate( sizeof(Byte) * elements );

	return ret;
}

static Void Destruct(Serface* instance)
{
	if ( !instance )
		return;

	FAllocator.Release( instance->colorBuffer );
	FAllocator.Release( instance->depthBuffer );
	FAllocator.Release( instance->stencilBuffer );
}

static Void Clear(Serface* instance, SerfaceClearFlag flag, const Color* clearColor, RealType clearDepth, Byte clearStencil)
{
	if ( flag & SerfaceClearFlag_Color )
		FSerface.ClearColor(instance, clearColor);

	if ( flag & SerfaceClearFlag_Depth )
		FSerface.ClearDepth(instance, clearDepth);

	if ( flag & SerfaceClearFlag_Stencil )
		FSerface.ClearStencil(instance, clearStencil);
}

static Void ClearColor(Serface* instance, const Color* color)
{
	for (SizeType index = 0; index < instance->elementCount; index++)
		instance->colorBuffer[index] = *color;
}

static Void ClearDepth(Serface* instance, RealType depth)
{
	for (SizeType index = 0; index < instance->elementCount; index++)
		instance->depthBuffer[index] = depth;
}

static Void ClearStencil(Serface* instance, Byte stencil)
{
	for (SizeType index = 0; index < instance->elementCount; index++)
		instance->stencilBuffer[index] = stencil;
}

static Void FlipHorizontal(Serface* instance)
{
	SizeType width	= instance->width;
	SizeType height = instance->height;

	SizeType halfWidth = width / 2;

	for(SizeType y = 0; y < height; y++)
		for(SizeType x = 0; x < halfWidth; x++)
		SWAP(
				Color,
				instance->colorBuffer[width * y + x],
				instance->colorBuffer[width * y + (width - 1 - x)]
		);
}

static Void FlipVertical(Serface* instance)
{
	SizeType width	= instance->width;
	SizeType height = instance->height;

	SizeType halfHeight = height / 2;

	for(SizeType y = 0; y < halfHeight; y++)
		for(SizeType x = 0; x < width; x++)
		SWAP(
				Color,
				instance->colorBuffer[width * y + x],
				instance->colorBuffer[width * (height - 1 - y) + x]
		);
}

static Void CopyTo(const Serface* instance, Void* RenderTarget)
{
#if defined(PLATFORM_WINDOWS)
	typedef struct { Byte b, g, r, a; } B8G8R8A8;

	for (SizeType index = 0; index < instance->elementCount; index++)
	{
		Color* from		= instance->colorBuffer + index;
		B8G8R8A8* to	= CAST(B8G8R8A8*, RenderTarget) + index;

		to->b = FMath.Clamp01( from->b ) * 255;
		to->g = FMath.Clamp01( from->g ) * 255;
		to->r = FMath.Clamp01( from->r ) * 255;
		to->a = FMath.Clamp01( from->a ) * 255;
	}
#elif defined(PLATFORM_LINUX) | defined(PLATFORM_ANDROID)
	typedef struct { Byte r, g, b, a; } R8G8B8A8;

	for (SizeType index = 0; index < instance->elementCount; index++)
	{
		Color* from		= instance->colorBuffer + index;
		R8G8B8A8* to	= CAST(R8G8B8A8*, RenderTarget) + index;

		to->r = FMath.Clamp01( from->r ) * 255;
		to->g = FMath.Clamp01( from->g ) * 255;
		to->b = FMath.Clamp01( from->b ) * 255;
		to->a = FMath.Clamp01( from->a ) * 255;
	}
#endif
}

static Void SetPixel(Serface* instance, SizeType x, SizeType y, const Color* color)
{
	instance->colorBuffer[instance->width * y + x] = *color;
}

static Color GetPixel(const Serface* instance, SizeType x, SizeType y)
{
	return instance->colorBuffer[instance->width * y + x];
}

static Void SetDepth(Serface* instance, SizeType x, SizeType y, RealType depth)
{
	instance->depthBuffer[instance->width * y + x] = depth;
}

static RealType GetDepth(const Serface* instance, SizeType x, SizeType y)
{
	return instance->depthBuffer[instance->width * y + x];
}

static Void SetStencil(Serface* instance, SizeType x, SizeType y, Byte stencil)
{
	instance->stencilBuffer[instance->width * y + x] = stencil;
}

static Byte GetStencil(const Serface* instance, SizeType x, SizeType y)
{
	return instance->stencilBuffer[instance->width * y + x];
}


struct FSerface FSerface =
{
	Construct,
	Destruct,
	Clear,
	ClearColor,
	ClearDepth,
	ClearStencil,
	FlipHorizontal,
	FlipVertical,
	CopyTo,
	SetPixel,
	GetPixel,
	SetDepth,
	GetDepth,
	SetStencil,
	GetStencil,
};
