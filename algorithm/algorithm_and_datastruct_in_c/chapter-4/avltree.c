#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./avltree.h"

struct AvlNode
{
  ElementType Element;
  AvlTree Left;
  AvlTree Right;
  int Height;
};

AvlTree
MakeEmpty(AvlTree T)
{
  if (T != NULL)
  {
    MakeEmpty(T->Left);
    MakeEmpty(T->Right);
    free(T);
  }
  return NULL;
}

Position
Find(ElementType X, AvlTree T)
{
  if (T == NULL)
  {
    return NULL;
  }
  else
  if (X > T->Element)
  {
    return Find(X, T->Right);
  }
  else
  if (X < T->Element)
  {
    return Find(X, T->Left);
  }
  else
  {
    return T;
  }
}

Position
FindMin(AvlTree T)
{
  if (T != NULL)
  {
    while(T->Left)
    {
      T = T->Left;
    }
  }

  return T;
}

Position
FindMax(AvlTree T)
{
  if (T != NULL)
  {
    while(T->Right != NULL)
    {
      T = T->Right;
    }
  }

  return T;
}

int
Height(Position P)
{
  if (P == NULL)
  {
    return -1;
  }
  return P->Height;
}

int
Max(int Lhs, int Rhs)
{
  return Lhs > Rhs ? Lhs : Rhs;
}

Position
SingleRotateWithLeft(Position K2)
{
  Position K1;
  K1 = K2->Left;

  K2->Left = K1->Right;
  K1->Right = K2;

  K2->Height = Max(Height(K2->Right), Height(K2->Left)) + 1;
  K1->Height = Max(Height(K1->Left), K2->Height) + 1;
  return K1;
}

Position
SingleRotateWithRight(Position K2)
{

  Position K1;
  K1 = K2->Right;

  K2->Right = K1->Left;
  K1->Left = K2;

  K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
  K1->Height = Max(Height(K1->Right), K1->Height) + 1;

  return K1;
}

Position
DoubleRotateWithLeft(Position K3)
{
  SingleRotateWithRight(K3->Left);
  return SingleRotateWithLeft(K3);
}

Position
DoubleRotateWithRight(Position K3)
{
  SingleRotateWithLeft(K3->Right);
  return SingleRotateWithRight(K3);
}

AvlTree
Insert(ElementType X, AvlTree T)
{
  if (T == NULL)
  {
    T = malloc(sizeof(struct AvlNode));
    if (T == NULL)
    {
      Error("No additional memory!!");
      exit(1);
    }
    else {
      T->Element = X;
      T->Height = 0;
      T->Left = T->Right = NULL;
    }
  }
  else
  if (X < T->Element){
    T->Left = Insert(X, T->Left);
    if (Height(T->Left) - Height(T->Right) == 2)
    {
      if(X < T->Left->Element)
      {
        T = SingleRotateWithLeft(T);
      }
      else
      {
        T = DoubleRotateWithLeft(T);
      }
    }
  }
  else
  if (X > T->Element)
  {
    T->Right = Insert(X, T->Right);
      // printf("%d%s%d\n", Height(T->Right) - Height(T->Left), "Right", X);
    if (Height(T->Right) - Height(T->Left) == 2)
    {
      // printf("%d|%d\n", X, T->Right->Element);
      if (X > T->Right->Element)
      {
        T = SingleRotateWithRight(T);
      }
      else
      {
        T = DoubleRotateWithRight(T);
      }
    }
  }

  T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
  return T;
}

void
tprint(AvlTree T, int D) {
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
    fprintf(stdout, "%s%d|%d\n", s, T->Element, T->Height);
    tprint(T->Right, D + 1);
  }
}

int
main(void)
{
  AvlTree T = NULL;
  MakeEmpty(T);

  T = Insert(1, T);
  // T = Insert(2, T);
  // T = Insert(3, T);


  for (int i = 0; i < 100; i++)
  {
    T = Insert(i, T);
  }

  tprint(T, 0);

  return 0;
}
