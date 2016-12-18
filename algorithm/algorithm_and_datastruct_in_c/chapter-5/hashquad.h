#ifndef _HASHQUAD_H
typedef int ElementType;

#define _HASHQUAD_H
typedef unsigned int Index;
typedef Index Position;

struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P, HashTable H);
HashTable Rehash(HashTable H);

enum KindOfEntry {Legitimate, Empty, Deleted};

struct HashEntry {
  ElementType Element;
  enum KindOfEntry Info;
};

typedef struct HashEntry Cell;

struct HashTbl {
  int TableSize;
  Cell *TheCells;
};
#endif
