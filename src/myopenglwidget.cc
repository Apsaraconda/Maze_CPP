#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  message = new QMessageBox(this);
  message->setText("Can't solve");
  ResetData();
  for (int i = 0; i < 3; i++) {
    color_.push_back(0);
    background_color_.push_back(1);
  }
  type_of_struct_ = 0;
  maze_ = new Maze;
}

void MyOpenGLWidget::SetColor(const std::vector<double> &col) { color_ = col; }

void MyOpenGLWidget::SetColor(double r, double g, double b) {
  color_[0] = r, color_[1] = g, color_[2] = b;
}

void MyOpenGLWidget::SetBackgroundColor(const std::vector<double> &col) {
  background_color_ = col;
}

void MyOpenGLWidget::SetMaze(const Maze &m) {
  ResetData();
  *maze_ = m;
}

void MyOpenGLWidget::MouseHandle(int x, int y) {
  if (mouse_handle_flag == 2) {
    ResetData();
    maze_->ClearSolve();
  }
  if (!mouse_handle_flag) {
    mouse_x0_ = x, mouse_y0_ = y;
    mouse_handle_flag = 1;
  } else {
    mouse_x1_ = x, mouse_y1_ = y;
    mouse_handle_flag = 2;
    if (!maze_->SolveMaze(mouse_x0_, mouse_y0_, mouse_x1_, mouse_y1_))
      message->exec();
  }
}

std::pair<int, int> MyOpenGLWidget::CalculateDotsPlace(QMouseEvent *event) {
  float var_x = event->pos().x(), var_y = event->pos().y();
  float w = width(), h = height();
  var_x = var_x / w;
  var_y = var_y / h;
  var_x *= maze_->GetX();
  var_y *= maze_->GetY();
  return {var_x, var_y};
}

void MyOpenGLWidget::SetBackgroundColor(double r, double g, double b) {
  background_color_[0] = r, background_color_[1] = g, background_color_[2] = b;
}

void MyOpenGLWidget::paintGL() {
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, maze_->GetX(), maze_->GetY(), 0, 0, 1);
  glClearColor(background_color_[0], background_color_[1], background_color_[2],
               1);
  glClear(GL_COLOR_BUFFER_BIT);
  DisplayOutput();
  glPopMatrix();
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event) {
  if (!type_of_struct_) {
    std::pair<int, int> dot = CalculateDotsPlace(event);
    MouseHandle(dot.first, dot.second);
    update();
  }
}

void MyOpenGLWidget::DisplayOutput() {
  if (maze_->GetX() && maze_->GetY()) {
    GenerateBorder();
    if (!type_of_struct_) {
      PrintMaze();
      PrintSolution(maze_->GetSolve());
      PrintDots();
    } else {
      PrintCave();
    }
  }
}

void MyOpenGLWidget::PrintMaze() {
  PrintBottomWalls();
  PrintRightWalls();
}

void MyOpenGLWidget::PrintCave() {
  for (int i = 0; i < maze_->GetRightWalls().size(); i++) {
    if (maze_->GetRightWalls()[i]) {
      glPointSize(20);
      glBegin(GL_QUADS);
      glVertex2f(i % maze_->GetX(), i / maze_->GetX());
      glVertex2f(i % maze_->GetX(), i / maze_->GetX() + 1);
      glVertex2f(i % maze_->GetX() + 1, i / maze_->GetX() + 1);
      glVertex2f(i % maze_->GetX() + 1, i / maze_->GetX());
      glEnd();
    }
  }
}

void MyOpenGLWidget::GenerateBorder() {
  glLineWidth(2);
  glColor3f(color_[0], color_[1], color_[2]);
  glBegin(GL_LINE_LOOP);
  glVertex2f(0, 0);
  glVertex2f(0, maze_->GetY());
  glVertex2f(maze_->GetX(), maze_->GetY());
  glVertex2f(maze_->GetX(), 0);
  glEnd();
}

void MyOpenGLWidget::PrintRightWalls() {
  for (int i = 0; i < maze_->GetRightWalls().size(); i++) {
    if (maze_->GetRightWalls()[i]) {
      glBegin(GL_LINES);
      glVertex2f(i % maze_->GetX() + 1, i / maze_->GetX());
      glVertex2f(i % maze_->GetX() + 1, i / maze_->GetX() + 1);
      glEnd();
      glPointSize(2);
      glEnable(GL_POINT_SMOOTH);
      glBegin(GL_POINTS);
      glVertex2f(i % maze_->GetX() + 1, i / maze_->GetX());
      glVertex2f(i % maze_->GetX() + 1, i / maze_->GetX() + 1);
      glEnd();
      glDisable(GL_POINT_SMOOTH);
    }
  }
}

void MyOpenGLWidget::PrintBottomWalls() {
  for (int i = 0; i < maze_->GetBottomWalls().size(); i++) {
    if (maze_->GetBottomWalls()[i]) {
      glBegin(GL_LINES);
      glVertex2f(i % maze_->GetX(), i / maze_->GetX() + 1);
      glVertex2f(i % maze_->GetX() + 1, i / maze_->GetX() + 1);
      glEnd();
      glPointSize(2);
      glEnable(GL_POINT_SMOOTH);
      glBegin(GL_POINTS);
      glVertex2f(i % maze_->GetX() + 1, i / maze_->GetX());
      glVertex2f(i % maze_->GetX() + 1, i / maze_->GetX() + 1);
      glEnd();
      glDisable(GL_POINT_SMOOTH);
    }
  }
}

void MyOpenGLWidget::PrintDots() {
  glPointSize(4);
  glColor3f(0, 0, 1);
  glBegin(GL_POINTS);
  glVertex2f(mouse_x0_ + 0.5, mouse_y0_ + 0.5);
  glVertex2f(mouse_x1_ + 0.5, mouse_y1_ + 0.5);
  glEnd();
}

void MyOpenGLWidget::ResetData() {
  mouse_x0_ = -2;
  mouse_y0_ = -2;
  mouse_x1_ = -2;
  mouse_y1_ = -2;
  mouse_handle_flag = 0;
}

int MyOpenGLWidget::OpenFile(QString file_path) {
  ResetData();
  type_of_struct_ = 0;
  int error = maze_->OpenFile(file_path);
  if (!error) {
    repaint();
  } else if (error == 3) {
    type_of_struct_ = 1;
    repaint();
  }
  return error;
}

int MyOpenGLWidget::SaveFile(QString file_path) {
  int error = maze_->SaveFile(file_path);
  return error;
}

void MyOpenGLWidget::PrintSolution(std::vector<std::pair<float, float>> solve) {
  glLineWidth(2);
  glColor3f(1, 0, 1);
  glBegin(GL_LINES);
  for (auto it = solve.cbegin(); it != solve.cend(); it++) {
    const auto &crd = *it;
    glVertex2f(crd.first, crd.second);
  }
  glEnd();
  glPointSize(2);
  glEnable(GL_POINT_SMOOTH);
  glBegin(GL_POINTS);
  for (auto it = solve.cbegin(); it != solve.cend(); it++) {
    const auto &crd = *it;
    glVertex2f(crd.first, crd.second);
  }
  glEnd();
  glDisable(GL_POINT_SMOOTH);
}
