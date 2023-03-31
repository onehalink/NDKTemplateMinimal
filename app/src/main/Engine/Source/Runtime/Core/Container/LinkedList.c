#include "LinkedList.h"



static LinkedList Construct(SizeType datatypeSize)
{
	LinkedList ret;
	ret.header			= NullPointer;
	ret.count			= 0;
	ret.datatypeSize	= datatypeSize;

	return ret;
}

static Void Destruct(LinkedList* instance)
{
	if ( !instance )
		return;

	LinkedListNode* node = instance->header;
	while (node)
	{
		LinkedListNode* next = node->next;

		FLinkedListNode.Destruct(node);

		node = next;
	}
}

static Void Add(LinkedList* instance, LinkedListNode* node)
{
	if ( !instance->header )
		instance->header = node;
	else
		FLinkedList.IndexAt(instance, instance->count - 1)->next = node;

	instance->count++;
}

static Void InsertAt(LinkedList* instance, SizeType index, LinkedListNode* node)
{
	if ( index >= instance->count )
		return;

	if ( index == 0 )
	{
		node->next			= instance->header;
		instance->header	= node;
	}
	else
	{
		LinkedListNode* previous = FLinkedList.IndexAt(instance, index - 1);

		node->next		= previous->next;
		previous->next	= node;
	}

	instance->count++;
}

static Void RemoveAt(LinkedList* instance, SizeType index)
{
	if ( index >= instance->count )
		return;

	if ( index == 0 )
	{
		LinkedListNode* next = instance->header->next;

		FLinkedListNode.Destruct( instance->header );

		instance->header = next;
	}
	else
	{
		LinkedListNode* previous	= FLinkedList.IndexAt(instance, index - 1);
		LinkedListNode* current		= previous->next;
		previous->next				= current->next;

		FLinkedListNode.Destruct(current);
	}

	instance->count--;
}

static LinkedListNode* IndexAt(LinkedList* instance, SizeType index)
{
	LinkedListNode* node = instance->header;

	for (SizeType iteration = 1; iteration <= index; iteration++)
		if ( !node )
			return NullPointer;
		else
			node = node->next;

	return node;
}


struct FLinkedList FLinkedList =
{
	Construct,
	Destruct,
	Add,
	InsertAt,
	RemoveAt,
	IndexAt,
};
