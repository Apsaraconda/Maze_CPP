#ifndef A1_MAZE_CPP_SRC_MAZE_MAZE_H
#define A1_MAZE_CPP_SRC_MAZE_MAZE_H
#include <QFile>
#include <QTextStream>
#include <ctime>
#include <vector>

class Maze {
 public:
  Maze() : x_(0), y_(0) {}
  Maze(int x, int y) : x_(x), y_(y) {}
  Maze &operator=(const Maze &);
  void GenerateMaze(int x, int y);
  int SolveMaze(int x0, int y0, int x1, int y1);
  std::vector<bool> GetRightWalls() { return right_walls_; }
  std::vector<bool> GetBottomWalls() { return bottom_walls_; }
  std::vector<std::pair<float, float>> GetSolve() { return solve_; }
  void PushRightWall(int value) { right_walls_.push_back(value); }
  void PushBottomWall(int value) { bottom_walls_.push_back(value); }
  void ClearData();
  void ClearSolve() { solve_.clear(); }
  int OpenFile(QString file_path);
  int SaveFile(QString file_path);
  void SetRange(int, int);
  void SetX(int range_x) { x_ = range_x; }
  void SetY(int range_y) { y_ = range_y; }
  int GetX() { return x_; }
  int GetY() { return y_; }
  void SetMaze(Maze &&m);
  std::vector<int> GenerateWave(int x0, int y0, int x1, int y1);

 protected:
  int CheckSetRange(QStringList line_data, int *form_success);
  int PushWall(QStringList line_data, bool bottom_wall, int *matrix_success);
  void EllerAlgorithm();
  std::vector<int> EllerAlgorithmPart1(int x);
  void EllerAlgorithmPart2(std::vector<int> &str);
  void EllerAlgorithmPart3(std::vector<int> &str);
  void EllerAlgorithmPart4(std::vector<int> &str);
  void EllerAlgorithmPart5(std::vector<int> &str, int y, bool finishMaze);
  void MergeSells(std::vector<int> &str, int transform_numb,
                  int numb_to_change);
  bool IsAvailableCellUp(int i);
  bool IsAvailableCellDown(int i);
  bool IsAvailableCellRight(int i);
  bool IsAvailableCellLeft(int i);
  int x_, y_;

 private:
  std::vector<bool> right_walls_;
  std::vector<bool> bottom_walls_;
  std::vector<std::pair<float, float>> solve_;
};

#endif  // A1_MAZE_CPP_1_SRC_MAZE_MAZE_H
