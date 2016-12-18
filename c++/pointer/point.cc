#include <stdio.h>

int i = 1;
int* a = &i;

int
fun(int*& arg)
{
  int c = 2;
  arg = &c;
  return 0;
}

int main(int argc, char const *argv[]) {
  fun(a);
  printf("%d\n", *a);
  return 0;
}
