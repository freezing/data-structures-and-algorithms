#include <cstdio>

int compute(int a, int b) {
  return a + b;
}

int main(int argc, char** argv) {
  int a = 3;
  int b = 4;
  int c;
  c = compute(a, b);
  printf("%d\n", c);
  return 0;
}