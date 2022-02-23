#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <fstream>

#include "../../prj.parts/doctest/doctest.h"
#include "M3i.h"

TEST_CASE("Simple") {
  M3i matrix = M3i(3, 5);
  matrix.write_to(std::cout);

  matrix.atPosition(0, 0, 0) = 0;
  matrix.atPosition(1, 0, 0) = 10;
  matrix.atPosition(0, 1, 0) = 11;
  matrix.atPosition(0, 0, 1) = 12;
  matrix.write_to(std::cout);

  matrix.resize(4, 3, 4, 7);
  matrix.write_to(std::cout);

  matrix.resize(1, 2, 3, 2);
  matrix.write_to(std::cout);
}