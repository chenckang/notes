#include "./binheap.h"
#include "../h/fatal.h"

#define MinData (-32767)

PriorityQueue
Initialize(int MaxElements)
{
  PriorityQueue H;

  H = malloc(sizeof(struct HeapStruct));

  if (H == NULL)
  {
    FatalError("Out of Memory!");
  }

  H->Elements = malloc(sizeof(struct ElementType) * MaxElements);

  if (H->Elements == NULL)
  {
    FatalError("Out of Memory!");
  }

  H->Capacity = MaxElements;
  H->Size = 0;
  H->Elements[0] = MinData;

  return H;
}

void
Insert(ElementType key, PriorityQueue H)
{
  int i;

  if (IsFull(H))
  {
    Error("Priority queue is Full!");
    return;
  }

  for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
  {
    H->Elements[i] = H->Elements[i / 2];
  }

  H->Element[i] = X:
}

ElementType
DeleteMin(PriorityQueue H)
{
  if (IsEmpty(H)) {
    Error("Priority queue is Empty!");
    return H->Elements[0];
  }

  ElementType MinElement, LastElement;
  MinElement = H->Elements[1];
  LastElement = H->Elements[H->Size--];

  for (int i = 1; i * 2 <= H->Size; i++)
  {
    int child = i * 2;

    if (child < H->Size && H->Elements[child + 1] < H->Elements[child])
    {
      child++;
    }

    if (LastElement > H->Elements[child])
    {
      H->Elements[i] = H->Elements[child];
    }
    else
    {
      break;
    }

  }
  H->Elements[i] = LastElement;

  return MinElement;
}

int
IsFull(PriorityQueue H)
{
  return H->Capacity == H->Size;
}

int IsEmpty(PriorityQueue H)
{
  return H->Size == 0;
}

void
Destroy(PriorityQueue H)
{
  free(H->Elements);
  free(H);
}

ElementType
FindMin(PriorityQueue H)
{
  if (IsEmpty(H))
  {
    return H->Elements[1];
  }
  Error('Queue is Empty!');
  return H->Elements[0];
}

void
MakeEmpty(PriorityQueue H) {
  H->Size = 0;
}

int
main(void)
{
  
}
