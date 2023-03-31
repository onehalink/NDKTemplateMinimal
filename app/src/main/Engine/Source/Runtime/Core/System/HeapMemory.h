#pragma once

#include "Allocator.h"

#include "../Base.h"



typedef struct
{
	Void*		buffer;
	SizeType	byteCount;
}
HeapMemory;


struct FHeapMemory
{
	HeapMemory(*Construct)(SizeType byteCount);
	Void(*Destruct)(HeapMemory* instance);
};

extern ENGINE_API struct FHeapMemory FHeapMemory;