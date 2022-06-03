#include "maze.h"

#include <cmath>
#include <set>

bool Cell::operator==(const Cell& other) const {
  return x == other.x && y == other.y;
}

void Maze2D::MarkAsUsed(const Cell& cell) { used[cell.x][cell.y] = true; }

bool Maze2D::IsUsed(const Cell& cell) { return used[cell.x][cell.y]; }

void Maze2D::SetEmpty(const Cell& cell) { arr[cell.x][cell.y] = ' '; }
void Maze2D::SetWall(const Cell& cell) { arr[cell.x][cell.y] = '#'; }
void Maze2D::SetConnection(const Cell& cell) { arr[cell.x][cell.y] = '*'; }

std::vector<Cell> Maze2D::FindNeighbours(const Cell& cell) const {
  std::vector<Cell> neighbours;
  if (cell.y + 2 < y_size && !used[cell.x][cell.y + 2]) {
    neighbours.push_back(Cell(cell.x, cell.y + 2));
  }
  if (cell.y - 2 >= 0 && !used[cell.x][cell.y - 2]) {
    neighbours.push_back(Cell(cell.x, cell.y - 2));
  }
  if (cell.x + 2 < x_size && !used[cell.x + 2][cell.y]) {
    neighbours.push_back(Cell(cell.x + 2, cell.y));
  }
  if (cell.x - 2 >= 0 && !used[cell.x - 2][cell.y]) {
    neighbours.push_back(Cell(cell.x - 2, cell.y));
  }

  return neighbours;
}

void Maze2D::Output(std::ofstream& fout) {
  for (size_t i = 0; i < x_size; i++) {
    for (size_t j = 0; j < y_size; j++) {
      fout << arr[i][j];
    }
    fout << "#\n";
  }
  for (size_t j = 0; j < y_size + 1; j++) {
    fout << '#';
  }
}

void Maze2D::Generate() {
  used[1][1] = true;

  std::vector<Wall> wall_list = {Wall(2, 1, Cell(1, 1), Cell(3, 1)),
                                 Wall(1, 2, Cell(1, 1), Cell(1, 3))};
  while (wall_list.size() > 0) {
    int ind = rand() % wall_list.size();
    Wall wall = wall_list[ind];

    if (!(IsUsed(wall.firstCell) && IsUsed(wall.secondCell))) {
      arr[wall.x][wall.y] = ' ';

      Cell curr_cell =
          IsUsed(wall.firstCell) ? wall.secondCell : wall.firstCell;
      MarkAsUsed(curr_cell);
      std::vector<Cell> neighbours = FindNeighbours(curr_cell);
      for (auto next_cell : neighbours) {
        wall_list.push_back(Wall(curr_cell.x + (next_cell.x - curr_cell.x) / 2,
                                 curr_cell.y + (next_cell.y - curr_cell.y) / 2,
                                 curr_cell, next_cell));
      }
    }

    wall_list.erase(wall_list.begin() + ind);
  }
}
void Maze2D::FixDensity(double density) {
  int walls_num = CountWalls();
  int wanted_walls_num = round(density * x_size * y_size);

  char new_type = (walls_num < wanted_walls_num) ? '#' : ' ';
  char old_type = (walls_num < wanted_walls_num) ? ' ' : '#';
  std::vector<Cell> cells;
  for (size_t i = 0; i < x_size; i++) {
    for (size_t j = 0; j < y_size; j++) {
      if (arr[i][j] == old_type) {
        cells.push_back(Cell(i, j));
      }
    }
  }

  int cnt = std::abs(walls_num - wanted_walls_num);
  while (cnt > 0) {
    int ind = rand() % cells.size();
    arr[cells[ind].x][cells[ind].y] = new_type;
    cells.erase(cells.begin() + ind);
    --cnt;
  }
}

int Maze2D::CountWalls() {
  int cnt = 0;
  for (size_t i = 0; i < x_size; i++) {
    for (size_t j = 0; j < y_size; j++) {
      if (arr[i][j] == '#') {
        ++cnt;
      }
    }
  }

  return cnt;
}

bool Maze2D::IsEmpty(int x, int y) { return arr[x][y] == ' '; }

Maze3D::Maze3D(int num, size_t size_x, size_t size_y, int max_connections)
    : levels_num(num),
      x_size(size_x),
      y_size(size_y),
      max_num_connections(max_connections / 2) {
  for (size_t i = 0; i < levels_num; i++) {
    maze3d.push_back(Maze2D(size_x, size_y));
    maze3d[i].Generate();
  }
}
void Maze3D::FixDensity(double density) {
  for (size_t i = 0; i < levels_num; i++) {
    maze3d[i].FixDensity(density);
  }

  BuildConnections();
}
void Maze3D::Output() {
  for (size_t i = 0; i < levels_num; i++) {
    std::ofstream fout("level" + std::to_string(i) + ".txt");
    maze3d[i].Output(fout);
  }
}

void Maze3D::BuildConnections() {
  for (size_t lev = 0; lev < levels_num - 1; lev++) {
    std::vector<Cell> common;
    for (size_t i = 0; i < x_size; i++) {
      for (size_t j = 0; j < y_size; j++) {
        if (maze3d[lev].IsEmpty(i, j) && maze3d[lev + 1].IsEmpty(i, j)) {
          common.push_back(Cell(i, j));
        }
      }
    }

    int cnt = 0;
    while (cnt < max_num_connections && common.size() > 0) {
      int ind = rand() % common.size();
      maze3d[lev].SetConnection(common[ind]);
      maze3d[lev + 1].SetConnection(common[ind]);
      common.erase(common.begin() + ind);
      ++cnt;
    }
  }
}