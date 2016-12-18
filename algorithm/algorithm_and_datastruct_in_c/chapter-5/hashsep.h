#ifndef _HASHSEP_H
#define _HASHSEP_H

typedef int ElementType;

struct ListNode;

typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P);

struct ListNode
{
  ElementType Element;
  Position Next;
};

typedef Position List;

struct HashTbl
{
  int TableSize;
  List *TheLists;
};
#endif
