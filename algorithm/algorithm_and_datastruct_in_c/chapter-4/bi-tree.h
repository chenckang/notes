#include "../h/type.h"

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

struct TreeNode
{
  ElementType Element;
  SearchTree Left;
  SearchTree Right;
};
