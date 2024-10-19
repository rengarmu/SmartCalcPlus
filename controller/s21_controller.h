#ifndef SMARTCALC_SRC_CONTROLLER_S21_CONTROLLER_H_
#define SMARTCALC_SRC_CONTROLLER_S21_CONTROLLER_H_

#include "../model/s21_model.h"

namespace s21 {

class SmartController {
 public:
  double SmartCalcModel(const std::string &str, double res);
  void GraficValue(double x_min, double x_max);
  std::vector<double> x_value;
  std::vector<double> y_value;

 private:
  s21::SmartModel model;
};

};  // namespace s21

#endif  // SRC_S21_SMARTCONTROLLER_H