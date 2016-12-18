typedef int ElementType;

#ifndef _BIN_HEAP
#define _BIN_HEAP

struct HeapStruct;

typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue H);
void MakeEmpty(PriorityQueue H);
void Insert(ElementType X, PriorityQueue H);
ElementType DeleteMin(PriorityQueue H);
ElementType FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);

struct HeapStruct
{
  int Capacity;
  int Size;
  ElementType *Elements;
};
#endif
