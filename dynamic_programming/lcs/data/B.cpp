#include <iostream>

int compute(int a, int b) {
  return a - b;
}

int main(int argc, char** argv) {
  int c;
  int a = 3;
  int b = 4;
  c = compute(a, b);
  std::cout << c << std::endl;
  return 0;
}