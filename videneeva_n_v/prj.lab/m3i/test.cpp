#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <m3i/m3i.h>

#include <fstream>

TEST_CASE("Simple") {
  M3i matrix = M3i(3, 5);
  matrix.WriteTo(std::cout);

  matrix.At(0, 0, 0) = 0;
  matrix.At(1, 0, 0) = 10;
  matrix.At(0, 1, 0) = 11;
  matrix.At(0, 0, 1) = 12;
  matrix.WriteTo(std::cout);

  matrix.Resize(4, 3, 4, 7);
  matrix.WriteTo(std::cout);

  CHECK(matrix.Size(0) == 4);
  CHECK(matrix.Size(1) == 3);
  CHECK(matrix.Size(2) == 4);

  matrix.Resize(1, 2, 3, 2);
  matrix.WriteTo(std::cout);
}

TEST_CASE("Copies and clones") {
  M3i matrix = M3i(3, 5);
  CHECK(matrix.getCopiesNumber() == 1);

  M3i copy1(matrix);
  CHECK(matrix.getCopiesNumber() == 2);
  CHECK(copy1.getCopiesNumber() == 2);

  {
    M3i copy2 = copy1;
    CHECK(matrix.getCopiesNumber() == 3);
    CHECK(copy1.getCopiesNumber() == 3);
    CHECK(copy2.getCopiesNumber() == 3);

    M3i copy3 = matrix;
    CHECK(matrix.getCopiesNumber() == 4);
    CHECK(copy1.getCopiesNumber() == 4);
    CHECK(copy2.getCopiesNumber() == 4);
    CHECK(copy3.getCopiesNumber() == 4);
  }
  CHECK(matrix.getCopiesNumber() == 2);
  CHECK(copy1.getCopiesNumber() == 2);

  M3i cloned = matrix.Clone();
  CHECK(matrix.getCopiesNumber() == 2);
  CHECK(copy1.getCopiesNumber() == 2);
  CHECK(cloned.getCopiesNumber() == 1);
}

TEST_CASE("initializer_list") {
  M3i matrix = {{{1, 1, 1}, {2, 2, 2}}};

  CHECK(matrix.Size(0) == 1);
  CHECK(matrix.Size(1) == 2);
  CHECK(matrix.Size(2) == 3);

  for (size_t i = 0; i < 3; i++) {
    CHECK(matrix.At(0, 0, i) == 1);
    CHECK(matrix.At(0, 1, i) == 2);
  }
}