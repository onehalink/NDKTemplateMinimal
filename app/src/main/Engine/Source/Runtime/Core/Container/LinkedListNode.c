#include "LinkedListNode.h"


static LinkedListNode* Construct(const Void* element, SizeType datatypeSize)
{
	LinkedListNode* ret	= FAllocator.Allocate( sizeof(LinkedListNode) );
	ret->next			= NullPointer;
	ret->dataArea		= FAllocator.Allocate(datatypeSize);

	FMemory.Copy(
		element,
		ret->dataArea,
		datatypeSize
	);

	return ret;
}

static Void Destruct(LinkedListNode* instance)
{
	if ( !instance )
		return;

	FAllocator.Release( instance->dataArea );
	FAllocator.Release(instance);
}


struct FLinkedListNode FLinkedListNode =
{
	Construct,
	Destruct,
};
