#ifndef MAZE_H
#define MAZE_H
#include <fstream>
#include <string>
#include <vector>

struct Cell {
  Cell() = default;
  Cell(int _x, int _y) : x(_x), y(_y) {}
  bool operator==(const Cell& other) const;

  int x = 0;
  int y = 0;
};

struct Wall {
  Wall(int _x, int _y, Cell f, Cell s)
      : x(_x), y(_y), firstCell(f), secondCell(s) {}

  int x = 0;
  int y = 0;
  Cell firstCell;
  Cell secondCell;
};

class Maze2D {
 public:
  Maze2D(size_t size_x, size_t size_y) : x_size(size_x), y_size(size_y) {
    used.resize(x_size);
    arr.resize(x_size);
    for (size_t i = 0; i < x_size; i++) {
      used[i].resize(y_size, false);

      arr[i].resize(y_size, '#');
      if (i % 2 != 0) {
        for (size_t j = 1; j < y_size; j += 2) {
          arr[i][j] = ' ';
        }
      }
    }
  }

  void Generate();
  void FixDensity(double density);

  void Output(std::ofstream& fout);

  bool IsEmpty(int x, int y);
  void SetConnection(const Cell& cell);

 private:
  size_t x_size = 0;
  size_t y_size = 0;
  std::vector<std::vector<char>> arr;
  std::vector<std::vector<bool>> used;

  void MarkAsUsed(const Cell& cell);
  bool IsUsed(const Cell& cell);

  void SetEmpty(const Cell& cell);
  void SetWall(const Cell& cell);

  std::vector<Cell> FindNeighbours(const Cell& cell) const;

  int CountWalls();
};

class Maze3D {
 public:
  Maze3D(int num, size_t size_x, size_t size_y, int max_connections);

  void FixDensity(double density);
  void Output();

 private:
  int max_num_connections = 0;
  int levels_num = 0;
  size_t x_size = 0;
  size_t y_size = 0;
  std::vector<Maze2D> maze3d;

  void BuildConnections();
};

#endif