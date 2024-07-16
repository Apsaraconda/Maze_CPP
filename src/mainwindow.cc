#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  connect(ui_->pushButton_MazeGen, SIGNAL(clicked()), this,
          SLOT(OnGenerateMazeButtonPush()));
  connect(ui_->color_button, SIGNAL(clicked()), this,
          SLOT(OnColorButtonClicked()));
  connect(ui_->color_background_button, SIGNAL(clicked()), this,
          SLOT(OnColorBackgroundColorClicked()));
  connect(ui_->actionSave_file, SIGNAL(triggered()), this,
          SLOT(OnActionSaveFileTriggered()));
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::OnGenerateMazeButtonPush() {
  srand(time(0));
  ui_->openGLWidget->SetTypeOfStruct() = 0;
  Maze maze;
  maze.GenerateMaze(ui_->spinBox_x->value(), ui_->spinBox_y->value());
  ui_->openGLWidget->SetMaze(maze);
  ui_->openGLWidget->repaint();
}

void MainWindow::OnColorButtonClicked() {
  QColor rgb = QColorDialog::getColor(Qt::black, this, "Line color");
  double r = static_cast<double>(rgb.red()) / 255;
  double b = static_cast<double>(rgb.blue()) / 255;
  double g = static_cast<double>(rgb.green()) / 255;
  ui_->openGLWidget->SetColor(r, g, b);
  ui_->openGLWidget->repaint();
}

void MainWindow::OnColorBackgroundColorClicked() {
  QColor rgb = QColorDialog::getColor(Qt::white, this, "Background color");
  double r = static_cast<double>(rgb.red()) / 255;
  double b = static_cast<double>(rgb.blue()) / 255;
  double g = static_cast<double>(rgb.green()) / 255;
  if (!rgb.isValid()) {
    ui_->openGLWidget->SetBackgroundColor(1, 1, 1);
  } else {
    ui_->openGLWidget->SetBackgroundColor(r, g, b);
  }
  ui_->openGLWidget->repaint();
}

void MainWindow::on_actionOpen_file_triggered() {
  QString file_path =
      QFileDialog::getOpenFileName(this, "Open file", "", "All files (*.*)");
  if (file_path != nullptr) {
    int error = ui_->openGLWidget->OpenFile(file_path);
    if (error == 1) {
      QMessageBox message(this);
      message.setText("Open file error");
      message.exec();
    }
    if (error == 2) {
      QMessageBox message(this);
      message.setText("Incorrect data");
      message.exec();
    }
  }
}

void MainWindow::OnActionSaveFileTriggered() {
  QString file_path =
      QFileDialog::getSaveFileName(this, "Save file", "", "All files (*.*)");
  if (file_path != nullptr) {
    ui_->openGLWidget->SaveFile(file_path);
  }
}
