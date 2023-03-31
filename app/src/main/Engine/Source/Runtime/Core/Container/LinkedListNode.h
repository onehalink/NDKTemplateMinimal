#pragma once

#include "../Base.h"

#include "../System/Allocator.h"
#include "../System/Memory.h"



typedef struct LinkedListNode LinkedListNode;

struct LinkedListNode
{
	LinkedListNode*	next;
	Void*			dataArea;
};


struct FLinkedListNode
{
	LinkedListNode*(*Construct)(const Void* element, SizeType datatypeSize);
	Void(*Destruct)(LinkedListNode* instance);
};

extern ENGINE_API struct FLinkedListNode FLinkedListNode;