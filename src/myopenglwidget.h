#ifndef A1_MAZE_CPP_SRC_MYOPENGLWIDGET_H
#define A1_MAZE_CPP_SRC_MYOPENGLWIDGET_H
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QtOpenGL>
#include <vector>

#include "maze/maze.h"

class MyOpenGLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  MyOpenGLWidget(QWidget *parent);
  int &SetTypeOfStruct() { return type_of_struct_; };
  void SetColor(const std::vector<double> &);
  void SetColor(double, double, double);
  void SetBackgroundColor(double, double, double);
  void SetBackgroundColor(const std::vector<double> &);
  void SetMaze(const Maze &m);
  int OpenFile(QString file_path);
  int SaveFile(QString file_path);
  void ResetData();

 protected:
  void paintGL() override;
  void mousePressEvent(QMouseEvent *event) override;

 private:
  QMessageBox *message;
  void DisplayOutput();
  void GenerateBorder();
  void PrintMaze();
  void PrintCave();
  void PrintRightWalls();
  void PrintBottomWalls();
  void PrintDots();
  void PrintSolution(std::vector<std::pair<float, float>> solve);
  void MouseHandle(int, int);
  std::pair<int, int> CalculateDotsPlace(QMouseEvent *event);
  int mouse_x0_, mouse_y0_;
  int mouse_x1_, mouse_y1_;
  int mouse_handle_flag;
  std::vector<double> color_, background_color_;
  Maze *maze_;
  int type_of_struct_;
};

#endif  // A1_MAZE_CPP_SRC_MYOPENGLWIDGET_H
