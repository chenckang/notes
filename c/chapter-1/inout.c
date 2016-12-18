#include <stdio.h>

int
main() {
  printf("%d\n", EOF);
  int c = getchar();
  while(c != EOF) {
    putchar(c);
    c = getchar();
  }
  return 0;
}
