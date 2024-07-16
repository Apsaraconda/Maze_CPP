#include "maze.h"

Maze &Maze::operator=(const Maze &m) {
  this->bottom_walls_ = m.bottom_walls_;
  this->right_walls_ = m.right_walls_;
  this->x_ = m.x_;
  this->y_ = m.y_;
  this->solve_ = m.solve_;
  return *this;
}

void Maze::SetRange(int range_x, int range_y) {
  SetX(range_x);
  SetY(range_y);
}

void Maze::ClearData() {
  x_ = 0;
  y_ = 0;
  bottom_walls_.clear();
  right_walls_.clear();
  ClearSolve();
}

void Maze::GenerateMaze(int x, int y) {
  ClearData();
  SetRange(x, y);
  EllerAlgorithm();
}

void Maze::EllerAlgorithm() {
  std::vector<int> str = EllerAlgorithmPart1(x_);
  for (int i = 0; i < y_; i++) {
    EllerAlgorithmPart2(str);
    if (i != y_ - 1) {
      EllerAlgorithmPart3(str);
      EllerAlgorithmPart4(str);
      EllerAlgorithmPart5(str, i, 0);
    } else {
      EllerAlgorithmPart5(str, i, 1);
    }
  }
}
std::vector<int> Maze::EllerAlgorithmPart1(int x) {
  std::vector<int> res(x, 0);
  return res;
}
void Maze::EllerAlgorithmPart2(std::vector<int> &str) {
  static unsigned count = 1;
  for (int i = 0; i < x_; i++) {
    if (!str[i]) str[i] = count++;
  }
}
void Maze::EllerAlgorithmPart3(std::vector<int> &str) {
  int random;
  for (int i = 0; i < x_ - 1; i++) {
    random = std::rand() % 2;
    if (random || str[i] == str[i + 1]) {
      right_walls_.push_back(1);
    } else {
      MergeSells(str, str[i + 1], str[i]);
      right_walls_.push_back(0);
    }
  }
  right_walls_.push_back(1);
}
void Maze::EllerAlgorithmPart4(std::vector<int> &str) {
  bool border, newSet;
  bool emptySpace = false;
  for (int i = 0; i < x_; i++) {
    newSet = (i == 0 || str[i] != str[i - 1]);
    if (newSet) emptySpace = false;
    border = std::rand() % 2;
    if (border && (emptySpace || (i + 1 != x_ && str[i + 1] == str[i]))) {
      bottom_walls_.push_back(true);
    } else {
      emptySpace = true;
      bottom_walls_.push_back(false);
    }
  }
}
void Maze::EllerAlgorithmPart5(std::vector<int> &str, int y_temp,
                               bool finishMaze) {
  if (!finishMaze) {
    for (int i = 0; i < x_; i++) {
      if (bottom_walls_[y_temp * x_ + i]) str[i] = 0;
    }
  } else {
    for (int i = 0; i < x_ - 1; i++) {
      if (str[i] == str[i + 1]) {
        right_walls_.push_back(1);
      } else {
        MergeSells(str, str[i + 1], str[i]);
        right_walls_.push_back(0);
      }
      bottom_walls_.push_back(1);
    }
    right_walls_.push_back(1);
    bottom_walls_.push_back(1);
  }
}

void Maze::MergeSells(std::vector<int> &str, int transform_numb,
                      int numb_to_change) {
  for (int i = 0; i < x_; i++) {
    if (str[i] == transform_numb) {
      str[i] = numb_to_change;
    }
  }
}

int Maze::OpenFile(QString file_path) {
  int error = 0;
  QFile file(file_path);
  if (!file.open(QIODevice::ReadOnly)) {
    error = 1;
  } else {
    ClearData();
    int current_line = 0;
    int second_matrix = 0;
    int form_success = 0;
    int first_matrix_success = 0;
    int second_matrix_success = 0;
    while (!file.atEnd()) {
      current_line++;
      char buf[1024];
      file.readLine(buf, sizeof(buf));
      QStringList line_data = QString(buf).trimmed().split(" ");
      if (current_line == 1) {
        error = CheckSetRange(line_data, &form_success);
      } else {
        if (current_line >= GetY() + 1) second_matrix = 1;
        if (line_data.length() == GetX() && current_line <= GetY() + 1) {
          error = PushWall(line_data, 0, &first_matrix_success);
        } else if (line_data.length() == GetX() && second_matrix &&
                   second_matrix <= GetY() + 1) {
          second_matrix++;
          error = PushWall(line_data, 1, &second_matrix_success);
        } else if (line_data.length() != GetX() && second_matrix == 1) {
        } else {
          error = 2;
        }
      }
      if (error) break;
    }
    file.close();
    if (!form_success || first_matrix_success != GetY() ||
        second_matrix_success != GetY())
      error = 2;
    if (second_matrix == 1 && first_matrix_success && !second_matrix_success)
      error = 3;
  }
  return error;
}

int Maze::SaveFile(QString file_path) {
  int error = 0;
  QFile file(file_path);
  if (!file.open(QIODevice::WriteOnly)) {
    error = 1;
  } else {
    QTextStream steam(&file);
    steam << y_ << ' ' << x_ << '\n';
    for (long unsigned int i = 0; i < right_walls_.size(); i++) {
      steam << right_walls_[i] << ' ';
      if (!((i + 1) % x_)) steam << '\n';
    }
    steam << '\n';
    for (long unsigned int i = 0; i < bottom_walls_.size(); i++) {
      steam << bottom_walls_[i] << ' ';
      if (!((i + 1) % x_)) steam << '\n';
    }
    file.close();
  }
  return error;
}

int Maze::PushWall(QStringList line_data, bool bottom_wall,
                   int *matrix_success) {
  int error = 0;
  bool int_ok = 0;
  for (int i = 0; i < line_data.length(); ++i) {
    int value = line_data[i].toInt(&int_ok);
    if (!int_ok || (value != 0 && value != 1)) {
      error = 2;
      break;
    }
    if (!bottom_wall) {
      PushRightWall(value);
    } else {
      PushBottomWall(value);
    }
  }
  if (!error) *matrix_success = *matrix_success + 1;
  return error;
}

int Maze::CheckSetRange(QStringList line_data, int *form_success) {
  int error = 0;
  if (line_data.length() == 2) {
    bool int_x_ok = 0;
    bool int_y_ok = 0;
    *form_success = *form_success + 1;
    int x = line_data[0].toInt(&int_x_ok);
    int y = line_data[1].toInt(&int_y_ok);
    if (int_x_ok && int_y_ok && x > 0 && x <= 50 && y > 0 && y <= 50) {
      SetX(x);
      SetY(y);
    } else {
      error = 2;
    }
  } else {
    error = 2;
  }
  return error;
}
