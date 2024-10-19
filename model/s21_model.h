#ifndef SMARTCALC_SRC_MODEL_S21_MODEL_H_
#define SMARTCALC_SRC_MODEL_S21_MODEL_H_

#include <cctype>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

enum priority { FDIGIT = 1, FVAL, FOPN, FADD, FMULL, FPOW, FUNC, FCLS, ALL };

enum operation {
  kSum = 1,
  kSub,
  kMul,
  kDiv,
  kMod,
  kPow,
  kSin,
  kCos,
  kTan,
  kAsin,
  kAcos,
  kAtan,
  kLn,
  kLog,
  kSqrt,
  kOpen,
  kCls
};

namespace s21 {
class SmartModel {
 public:
  void MakeList(const std::string &str);
  double findResult(double &res);

 private:
  struct leksem {
    double value;
    int priority;
  };
  std::vector<leksem> leksem_list_;
  int findIdent(const char *charStr, std::string &ident);
  void parsOpts(const std::string *ident);
  void ParsLeks(const std::string &str);
  void SqncValid();
  std::vector<leksem> PolishSort();
  void digitOperation(std::vector<double> &d_digit, double type);
};

}  // namespace s21

#endif  // SRC_S21_SMARTMODEL_H