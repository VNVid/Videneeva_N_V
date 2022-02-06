#include <iostream>

int main() {
  const int kStepSize = 5;
  int x = 0;
  std::cin >> x;
  std::cout << (x + kStepSize - 1) / kStepSize;
}