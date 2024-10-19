#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "../controller/s21_controller.h"
#include "qcustomplot.h"

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

 private slots:
  void BasicFunc();
  void PushButton_func(QAbstractButton *clickedButton);
  void ClearLine();
  void GraphFrame();

 private:
  s21::SmartController controller;
  Ui::MainWindow *ui;
  void PrintGrafic(double x_min, double x_max, char *str);
};
#endif  // MAINWINDOW_H
