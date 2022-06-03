#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <maze.h>

#include <fstream>
#include <iostream>

TEST_CASE("Density 1") {
  Maze3D maze = Maze3D(3, 10, 10, 0);
  maze.FixDensity(1);
  maze.Output();

  for (size_t i = 0; i < 3; i++) {
    std::ifstream fin("level" + std::to_string(i) + ".txt");

    for (size_t j = 0; j < 10; j++) {
      std::string str;
      fin >> str;
      for (size_t k = 0; k < str.size(); k++) {
        CHECK(str[k] == '#');
      }
    }
  }
}

TEST_CASE("Density 0") {
  Maze3D maze = Maze3D(3, 10, 10, 0);
  maze.FixDensity(0);
  maze.Output();

  for (size_t i = 0; i < 3; i++) {
    std::ifstream fin("level" + std::to_string(i) + ".txt");

    for (size_t j = 0; j < 10; j++) {
      std::string str;
      fin >> str;
      for (size_t k = 0; k < str.size() - 1; k++) {
        CHECK(str[k] == ' ');
      }
    }
  }
}

TEST_CASE("Density 0.5") {
  Maze3D maze = Maze3D(3, 10, 10, 0);
  maze.FixDensity(0.5);
  maze.Output();

  for (size_t i = 0; i < 3; i++) {
    std::ifstream fin("level" + std::to_string(i) + ".txt");

    int empty = 0;

    for (size_t j = 0; j < 10; j++) {
      std::string str;
      getline(fin, str);
      for (size_t k = 0; k < str.size(); k++) {
        if (str[k] == ' ') {
          ++empty;
        }
      }
    }

    double dens = (100 - (double)empty) / 100;
    CHECK(std::abs(dens - 0.5) < 0.05);
  }
}

TEST_CASE("Max connections") {
  for (size_t conn = 0; conn < 10; conn++) {
    Maze3D maze = Maze3D(3, 10, 10, conn);
    maze.Output();

    for (size_t i = 0; i < 3; i++) {
      std::ifstream fin("level" + std::to_string(i) + ".txt");

      int connections = 0;

      for (size_t j = 0; j < 10; j++) {
        std::string str;
        getline(fin, str);
        for (size_t k = 0; k < str.size(); k++) {
          if (str[k] == '*') {
            ++connections;
          }
        }
      }

      CHECK(connections <= conn);
    }
  }
}