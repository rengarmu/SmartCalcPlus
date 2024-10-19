#include "s21_controller.h"

double s21::SmartController::SmartCalcModel(const std::string &str,
                                            double res) {
  model.MakeList(str);
  return model.findResult(res);
}

void s21::SmartController::GraficValue(double x_min, double x_max) {
  x_value.clear();
  y_value.clear();
  double y_count = 0;
  double step = (x_max - x_min) / 1000;
  int i = 0;
  double tmp_val = x_min;
  while (1000 - i) {
    x_value.push_back(tmp_val);
    y_count = tmp_val;
    model.findResult(y_count);
    y_value.push_back(y_count);
    tmp_val += step;
    ++i;
  }
}
