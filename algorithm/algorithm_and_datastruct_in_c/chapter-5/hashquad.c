#include "./hashquad.h"
#include "../h/fatal.h"

#include <time.h>
#include <stdio.h>

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
Hash(ElementType Key, int TableSize) {
  return Key % TableSize;
}

HashTable
InitializeTable(int TableSize)
{
  HashTable H;
  int i;

  H = malloc(sizeof(struct HashTbl));

  if (H == NULL) {
    FatalError("No memory space!");
  }

  H->TableSize = NextPrime(TableSize);
  H->TheCells = malloc(sizeof(Cell) * H->TableSize);

  if (H->TheCells == NULL) {
    FatalError("No memory space!");
  }

  for (i = 0; i < H->TableSize; i++) {
    H->TheCells[i].Info = Empty;
    H->TheCells[i].Element = 0;
  }

  return H;
}

Position
Find(ElementType Key, HashTable H) {
  Position currentPos;
  int CollisionNum;

  CollisionNum = 0;
  currentPos = Hash(Key, H->TableSize);

  while (
    H->TheCells[currentPos].Info != Empty &&
    H->TheCells[currentPos].Element != Key
  ) {
    currentPos += 2 * ++CollisionNum - 1;
    if (currentPos >= H->TableSize)
    {
      currentPos -= H->TableSize;
    }
  }
  return currentPos;
}

void
Insert(ElementType Key, HashTable H)
{
  Position pos;

  pos = Find(Key, H);

  if (H->TheCells[pos].Info != Legitimate) {
    H->TheCells[pos].Info = Legitimate;
    H->TheCells[pos].Element = Key;
  }
}

void
DestroyTable(HashTable H)
{
  free(H->TheCells);
  free(H);
}

ElementType
Retrieve(Position P, HashTable H)
{
  return H->TheCells[P].Element;
}

HashTable
Rehash(HashTable H)
{
  int OldSize = H->TableSize;
  Cell *OldCells = H->TheCells;

  H = InitializeTable(2 * OldSize);

  for(int i = 0; i < OldSize; i++)
  {
    if (OldCells[i].Info == Legitimate)
    {
      Insert(OldCells[i].Element, H);
    }
  }

  free(OldCells);

  return H;
}

void
hprint(HashTable H) {
  printf("%d ---- \n", H->TableSize);
  for (int i = 0; i < H->TableSize; i++)
  {
    Cell c = H->TheCells[i];
    printf("| -> %d, %d\n", c.Element, c.Info);
  }
}

int
main(void)
{
  HashTable H = InitializeTable(17);
  srand(time(NULL));
  for (int i = 0; i < 8; i++)
  {
    int ins = rand() % 100;
    printf("%d ---->\n", ins);
    Insert(ins, H);
  }
  printf("<----------------->\n");
  hprint(H);
  printf("<----------------->\n");
  H = Rehash(H);
  hprint(H);
  return 0;
}
