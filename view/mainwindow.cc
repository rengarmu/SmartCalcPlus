#include "mainwindow.h"

#include <QAbstractButton>
#include <QMessageBox>
#include <QString>
#include <iomanip>
#include <iostream>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->showResult, SIGNAL(clicked()), this, SLOT(BasicFunc()));
  connect(ui->buttonGroup_text, &QButtonGroup::buttonClicked, this,
          &MainWindow::PushButton_func);
  connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(ClearLine()));
  connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(GraphFrame()));
  ui->frame_graph->hide();
  ui->label_2->hide();
  ui->label->setText("");
  ui->doubleSpinBox_xmin->setValue(-10.0);
  ui->doubleSpinBox_xmax->setValue(10.0);
  setFixedSize(ui->frame->width() + 2, ui->frame->height() + 50);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::BasicFunc() {
  try {
    QMessageBox MyB;
    double result{};
    result = ui->doubleSpinBox_x->value();
    double x_min = ui->doubleSpinBox_xmin->value();
    double x_max = ui->doubleSpinBox_xmax->value();
    QString str = ui->lineEdit->text();
    QByteArray ba;
    ba = str.toLatin1();
    double res = controller.SmartCalcModel(ba.data(), result);
    ui->label->setText(QString::number(res));
    if (ui->frame_graph->isVisible()) {
      PrintGrafic(x_min, x_max, ba.data());
    }
  } catch (std::exception& e) {
    ui->label->setText(QString::fromStdString(e.what()));
  }
}

void MainWindow::PushButton_func(QAbstractButton* clickedButton) {
  ui->lineEdit->insert(clickedButton->text());
}

void MainWindow::ClearLine() {
  ui->lineEdit->clear();
  ui->doubleSpinBox_x->clear();
}

void MainWindow::PrintGrafic(double x_min, double x_max, char* str) {
  ui->widget->xAxis->setRangeLower(x_min);
  ui->widget->xAxis->setRangeUpper(x_max);
  ui->widget->yAxis->setRangeLower(x_min);
  ui->widget->yAxis->setRangeUpper(x_max);
  controller.GraficValue(x_min, x_max);
  QVector<double> x(controller.x_value.begin(), controller.x_value.end());
  QVector<double> y(controller.y_value.begin(), controller.y_value.end());
  ui->widget->removeGraph(0);
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

void MainWindow::GraphFrame() {
  if (ui->frame_graph->isVisible()) {
    ui->frame_graph->hide();
    setFixedSize(ui->frame->width() + 2, ui->frame->height() + 50);
  } else {
    ui->frame_graph->show();
    setFixedSize(ui->frame->width() + 25 + ui->frame_plus->width(),
                 ui->frame->height() + 50);
  }
}
