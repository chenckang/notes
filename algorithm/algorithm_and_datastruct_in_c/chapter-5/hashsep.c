#include "./hashsep.h"
#include "../h/fatal.h"

#include <stdio.h>
#include <time.h>

static int
NextPrime( int N )
{
    int i;

    if( N % 2 == 0 )
        N++;
    for( ; ; N += 2 )
    {
        for( i = 3; i * i <= N; i += 2 )
            if( N % i == 0 )
                goto ContOuter;  /* Sorry about this! */
        return N;
      ContOuter: ;
    }
}

int
Hash(ElementType Key, int TableSize)
{
  return Key % TableSize;
}

HashTable
InitializeTable(int TableSize)
{
  HashTable H;
  int i;

  H = malloc(sizeof(struct HashTbl));

  if (H == NULL)
  {
    FatalError("Out of memory!");
  }

  H->TableSize = NextPrime(TableSize);

  H->TheLists = malloc(sizeof(List) * H->TableSize);

  if (H->TheLists == NULL)
  {
    FatalError("Out of memory!");
  }

  for (i = 0; i < H->TableSize; i++)
  {
    H->TheLists[i] = malloc(sizeof(struct ListNode));
    if (H->TheLists[i] == NULL)
    {
      FatalError("Out of memory");
    }
    else
    {
      H->TheLists[i]->Next = NULL;
    }
  }

  return H;
}

Position
Find(ElementType Key, HashTable H)
{
  Position P;
  List L;

  L = H->TheLists[Hash(Key, H->TableSize)];

  P = L->Next;
  while (P != NULL && P->Element != Key)
  {
    P = P->Next;
  }

  return P;
}

void
Insert(ElementType Key, HashTable H)
{
  Position Pos, NewCell;
  List L;

  Pos = Find(Key, H);

  if (Pos == NULL)
  {
    NewCell = malloc(sizeof(struct ListNode));
    if (NewCell == NULL) {
      FatalError("Out of Memory!");
    }
    else
    {
      L = H->TheLists[Hash(Key, H->TableSize)];
      NewCell->Next = L->Next;
      NewCell->Element = Key;
      L->Next = NewCell;
    }
  }
}

void
hprint(HashTable H) {
  printf("%d ----- \n", H->TableSize);

  for (int i = 0; i < H->TableSize; i++)
  {
    Position it = H->TheLists[i]->Next;
    printf("| -> ");
    while (it != NULL)
    {
      printf(" %d -> ", it->Element);
      it = it->Next;
    }
    printf("\n");
  }
}

void
DestroyTable(HashTable H)
{
  for (int i = 0; i < H->TableSize; i++)
  {
    Position pos = H->TheLists[i];
    Position tmp;

    while (pos != NULL) {
      tmp = pos->Next;
      free(pos);
      pos = tmp;
    }
  }

  free(H->TheLists);
  free(H);
}

ElementType
Retrieve(Position p)
{
  return p->Element;
}

int
main(void) {
  HashTable H = InitializeTable(10);
  srand(time(NULL));
  for(int i = 0; i < 50; i++)
  {
    int ins = rand() % 110;
    Insert(ins, H);
  }
  hprint(H);
  return 0;
}
