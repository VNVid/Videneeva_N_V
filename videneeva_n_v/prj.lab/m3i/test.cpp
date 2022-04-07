#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <fstream>

#include "m3i.h"

TEST_CASE("Simple")
{
    M3i matrix = M3i(3, 5);
    matrix.write_to(std::cout);

    matrix.at(0, 0, 0) = 0;
    matrix.at(1, 0, 0) = 10;
    matrix.at(0, 1, 0) = 11;
    matrix.at(0, 0, 1) = 12;
    matrix.write_to(std::cout);

    matrix.resize(4, 3, 4, 7);
    matrix.write_to(std::cout);

    CHECK(matrix.size(0) == 4);
    CHECK(matrix.size(1) == 3);
    CHECK(matrix.size(2) == 4);

    matrix.resize(1, 2, 3, 2);
    matrix.write_to(std::cout);
}

TEST_CASE("Copies and clones")
{
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

    M3i cloned = matrix.clone();
    CHECK(matrix.getCopiesNumber() == 2);
    CHECK(copy1.getCopiesNumber() == 2);
    CHECK(cloned.getCopiesNumber() == 1);
}

TEST_CASE("initializer_list")
{

    M3i matrix = {{{1, 1, 1}, {2, 2, 2}}};

    CHECK(matrix.size(0) == 1);
    CHECK(matrix.size(1) == 2);
    CHECK(matrix.size(2) == 3);

    for (size_t i = 0; i < 3; i++)
    {
        CHECK(matrix.at(0, 0, i) == 1);
        CHECK(matrix.at(0, 1, i) == 2);
    }
}