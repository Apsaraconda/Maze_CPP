
#include "maze.h"
int Maze::SolveMaze(int x0, int y0, int x1, int y1) {
  std::vector<int> mass = GenerateWave(x0, y0, x1, y1);
  int res = 1;
  if (x_ && y_ && x0 >= 0 && x1 >= 0 && y0 >= 0 && y1 >= 0 && !mass.empty()) {
    int numb = mass[y1 * x_ + x1];
    int up = 0, down = 0, left = 0, right = 0;
    while (numb != 1) {
      if ((y1 - 1) * x_ + x1 < x_ * y_) up = 1;
      if ((y1 + 1) * x_ + x1 >= 0) down = 1;
      if (((y1 * x_ + x1) % x_) - 1 >= 0) left = 1;
      if (((y1 * x_ + x1) % x_) + 1 < x_) right = 1;
      if (up && ((y1 - 1) * x_ + x1) >= 0 &&
          mass[(y1 - 1) * x_ + x1] == numb - 1 &&
          IsAvailableCellUp(y1 * x_ + x1)) {
        solve_.push_back(std::make_pair(x1 + 0.5, y1 - 0.5));
        solve_.push_back(std::make_pair(x1 + 0.5, y1 + 0.5));
        y1--;
      } else if (down && y1 + 1 != y_ && mass[(y1 + 1) * x_ + x1] == numb - 1 &&
                 IsAvailableCellDown(y1 * x_ + x1)) {
        solve_.push_back(std::make_pair(x1 + 0.5, y1 + 0.5));
        solve_.push_back(std::make_pair(x1 + 0.5, y1 + 1.5));
        y1++;
      } else if (left && y1 * x_ + x1 - 1 >= 0 &&
                 mass[y1 * x_ + x1 - 1] == numb - 1 &&
                 IsAvailableCellLeft(y1 * x_ + x1)) {
        solve_.push_back(std::make_pair(x1 + 0.5, y1 + 0.5));
        solve_.push_back(std::make_pair(x1 - 0.5, y1 + 0.5));
        x1--;
      } else if (right && y1 * x_ + x1 + 1 < x_ * y_ &&
                 mass[y1 * x_ + x1 + 1] == numb - 1 &&
                 IsAvailableCellRight(y1 * x_ + x1)) {
        solve_.push_back(std::make_pair(x1 + 0.5, y1 + 0.5));
        solve_.push_back(std::make_pair(x1 + 1.5, y1 + 0.5));
        x1++;
      }
      numb--;
      up = right = left = down = 0;
    }
  } else {
    res = 0;
  }
  return res;
}
std::vector<int> Maze::GenerateWave(int x0, int y0, int x1, int y1) {
  std::vector<int> maze_mass(x_ * y_, 0);
  int new_numb = 1;
  int no_way = 0;
  if (x_ != 0 && y_ != 0 && x1 >= 0 && y1 >= 0) {
    maze_mass[y0 * x_ + x0] = new_numb;
    while (!maze_mass[y1 * x_ + x1] && !no_way) {
      new_numb++;
      if ((int)maze_mass.size() < new_numb - 1) {
        no_way = 1;
      } else {
        for (long unsigned int i = 0; i < maze_mass.size(); i++) {
          if (maze_mass[i] == new_numb - 1) {
            if (IsAvailableCellUp(i)) {
              if (!maze_mass[i - x_]) maze_mass[i - x_] = new_numb;
            }
            if (IsAvailableCellDown(i)) {
              if (!maze_mass[i + x_]) maze_mass[i + x_] = new_numb;
            }
            if (IsAvailableCellRight(i)) {
              if (!maze_mass[i + 1]) maze_mass[i + 1] = new_numb;
            }
            if (IsAvailableCellLeft(i)) {
              if (!maze_mass[i - 1]) maze_mass[i - 1] = new_numb;
            }
          }
        }
      }
    }
  }
  if (no_way) return std::vector<int>();
  return maze_mass;
}
bool Maze::IsAvailableCellUp(int i) {
  if (i - x_ < 0) return false;
  if (bottom_walls_[i - x_]) return false;
  return true;
}

bool Maze::IsAvailableCellDown(int i) {
  if (i + x_ > x_ * y_) return false;
  if (bottom_walls_[i]) return false;
  return true;
}

bool Maze::IsAvailableCellRight(int i) {
  if ((i % x_) + 1 >= x_) return false;
  if (right_walls_[i]) return false;
  return true;
}

bool Maze::IsAvailableCellLeft(int i) {
  if ((i % x_) - 1 < 0) return false;
  if (right_walls_[i - 1]) return false;
  return true;
}
