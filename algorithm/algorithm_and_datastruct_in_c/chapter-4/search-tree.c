#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../h/fatal.h"
#include "./search-tree.h"

SearchTree
MakeEmpty( SearchTree T ) {
  if (T != NULL )
  {
    MakeEmpty( T->Left );
    MakeEmpty( T->Right );
    free( T );
  }
  return NULL;
}

Position
Find( ElementType X, SearchTree T)
{
  if (T == NULL)
  {
    return NULL;
  }

  if (X < T->Element)
  {
    return Find(X, T->Left);
  }
  else
  if (X > T->Element)
  {
    return Find(X, T->Right);
  }
  else
  {
    return T;
  }
}

Position
FindMin( SearchTree T )
{
  if (T == NULL)
  {
    return NULL;
  }
  else
  if (T -> Left == NULL)
  {
    return T;
  }
  else
  {
    return FindMin(T->Left);
  }
}

Position
FindMax( SearchTree T ) {
  if (T != NULL)
  {
    while (T->Right != NULL)
    {
      T = T->Right;
    }
  }

  return T;
}

SearchTree
Insert( ElementType X, SearchTree T )
{
  if (T == NULL)
  {
    T = malloc(sizeof(struct TreeNode));
    if (T == NULL)
    {
      FatalError("Out of space!");
    }
    else {
      T->Element = X;
      T->Left = T->Right = NULL;
    }
  }
  else
  if (X < T->Element)
  {
    T->Left = Insert(X, T->Left);
  }
  else
  if (X > T->Element)
  {
    T->Right = Insert(X, T->Right);
  }

  return T;
}

SearchTree
Delete( ElementType X, SearchTree T )
{
  Position TmpCell;

  if (T == NULL)
  {
    Error("Element not found");
  }
  else
  if (X < T->Element)
  {
    T->Left = Delete(X, T->Left);
  }
  else
  if (X > T->Element)
  {
    T->Right = Delete(X, T->Right);
  }
  else
  if (T->Left && T->Right)
  {
    TmpCell = FindMin(T->Right);
    T->Element = TmpCell->Element;
    T->Right = Delete(T->Element, T->Right);
  }
  else
  {
    TmpCell = T;
    if (T->Left == NULL)
    {
      T = T->Right;
    }
    else
    if (T->Right == NULL)
    {
      T = T->Left;
    }
    free(TmpCell);
  }
  return T;
}

void
tprint(SearchTree T, int D) {
  if (T != NULL)
  {
    tprint(T->Left, D + 1);
    char s[D];
    strcpy(s, "");
    for (int i = 0; i < D; i++)
    {
      strcat(s, "\t");
    }
    // puts(s);
    fprintf(stdout, "%s%d\n", s, T->Element);
    tprint(T->Right, D + 1);
  }
}

int
main(void) {
  SearchTree T = NULL;
  MakeEmpty(T);
  // Insert(50, T);
  // for (int i = 50; i > 0; i--)
  // {
  //   T = Insert(i, T);
  // }
  // for (int i = 51; i < 100; i++)
  // {
  //   T = Insert(i, T);
  // }
  srand(time(NULL));
  for (int i = 0; i < 100; i++) {
    T = Insert( rand() % 100, T);
  }

  tprint(T, 0);

  // for (int i = 0; i < 100; i++)
  // {
  //   T = Delete(rand() % 100, T);
  // }
  // tprint(T, 0);
  return 0;
}
