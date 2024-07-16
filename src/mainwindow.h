#ifndef A1_MAZE_CPP_SRC_MAINWINDOW_H
#define A1_MAZE_CPP_SRC_MAINWINDOW_H

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui_;
 public slots:
  void OnGenerateMazeButtonPush();
  void OnColorButtonClicked();
  void OnColorBackgroundColorClicked();
 private slots:
  void on_actionOpen_file_triggered();
  void OnActionSaveFileTriggered();
};
#endif  // A1_MAZE_CPP_SRC_MAINWINDOW_H
