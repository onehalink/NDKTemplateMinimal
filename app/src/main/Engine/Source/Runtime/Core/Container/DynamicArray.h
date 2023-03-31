#pragma once

#include "../Base.h"

#include "../System/Allocator.h"
#include "../System/Memory.h"



typedef struct
{
	Void* buffer;

	SizeType count;
	SizeType capacity;
	SizeType datatypeSize;
}
DynamicArray;


struct FDynamicArray
{
	DynamicArray(*Construct)(SizeType capacity, SizeType datatypeSize);
	Void(*Destruct)(DynamicArray* instance);


	Void(*Add)(DynamicArray* instance, const Void* element);
	Void(*InsertAt)(DynamicArray* instance, SizeType index, const Void* element);
	Void(*RemoveAt)(DynamicArray* instance, SizeType index);

	Void(*Clear)(DynamicArray* instance);


	Void*(*IndexAt)(DynamicArray* instance, SizeType index);
};

extern ENGINE_API struct FDynamicArray FDynamicArray;