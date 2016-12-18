#include <stdlib.h>
#include <stdio.h>

template <class T>
T minimum(const T& lhs, const T& rhs)
{
  return lhs < rhs ? lhs : rhs;
}

int
main(void) {
  int a = minimum<size_t>(100, 10);
  printf("%d\n", a);
  return 0;
}
