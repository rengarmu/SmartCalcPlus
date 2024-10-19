#include "s21_model.h"

void s21::SmartModel::MakeList(const std::string &str) {
  if (str.size() > 255) {
    throw std::invalid_argument("Input is too long");
  }
  ParsLeks(str);
  SqncValid();
  leksem_list_ = PolishSort();
}

void s21::SmartModel::ParsLeks(const std::string &str) {
  const char *charStr = str.c_str();
  if (!leksem_list_.empty()) leksem_list_.clear();
  while (*charStr) {
    size_t idx = 0;
    std::string ident;
    if (isdigit(*charStr)) {
      s21::SmartModel::leksem numLeksem = s21::SmartModel::leksem();
      numLeksem.value = std::stod(charStr, &idx);
      numLeksem.priority = FDIGIT;
      leksem_list_.push_back(numLeksem);
      charStr += idx;
    } else if (isalpha(*charStr) && *charStr != 'x') {
      idx = findIdent(charStr, ident);
      parsOpts(&ident);
      charStr += idx;
    } else if (*charStr == ' ') {
      ++charStr;
    } else {
      ident.push_back(*charStr);
      parsOpts(&ident);
      ++charStr;
    }
  }
}

void s21::SmartModel::SqncValid() {
  int ValMatrix[][ALL] = {
      {0, 1, 1, 0, 0, 0, 0, 0, 1},  // end
      {1, 0, 0, 1, 1, 1, 1, 0, 0},  // digit
      {1, 0, 0, 1, 1, 1, 1, 0, 0},  // val
      {1, 0, 0, 1, 1, 1, 1, 1, 0},  // opn
      {1, 1, 1, 1, 0, 0, 0, 0, 1},  // add
      {0, 1, 1, 0, 0, 0, 0, 0, 1},  // mull
      {0, 1, 1, 0, 0, 0, 0, 0, 1},  // pow
      {1, 0, 0, 1, 1, 1, 1, 0, 0},  // func
      {0, 1, 1, 0, 0, 0, 0, 0, 1}   // cls
  };
  int BracketsCheck = 0;
  for (size_t i = 0; i < leksem_list_.size(); ++i) {
    if (leksem_list_.at(i).priority == FOPN) ++BracketsCheck;
    if (leksem_list_.at(i).priority == FCLS) --BracketsCheck;
    if (BracketsCheck < 0)
      throw std::runtime_error("Brackets are not balanced");
  }
  if (BracketsCheck != 0) throw std::runtime_error("Brackets are not balanced");
  if (ValMatrix[leksem_list_.at(0).priority][0] == 0 ||
      ValMatrix[0][leksem_list_.back().priority] == 0)
    throw std::runtime_error("Invalid syntax");
  for (size_t i = 1; i < leksem_list_.size(); ++i) {
    if (ValMatrix[leksem_list_.at(i).priority]
                 [leksem_list_.at(i - 1).priority] == 0) {
      throw std::runtime_error("Invalid syntax");
    }
  }
}

std::vector<s21::SmartModel::leksem> s21::SmartModel::PolishSort() {
  std::vector<leksem> Buff;
  std::vector<leksem> PolishNat;
  size_t i = 0;
  while (i < leksem_list_.size()) {
    if (leksem_list_.at(i).priority == FDIGIT ||
        leksem_list_.at(i).priority == FVAL) {
      PolishNat.push_back(leksem_list_.at(i));
    } else if (leksem_list_.at(i).priority == FOPN) {
      Buff.push_back(leksem_list_.at(i));
    } else if (leksem_list_.at(i).priority > FOPN &&
               leksem_list_.at(i).priority < FCLS) {
      if ((leksem_list_.at(i).priority == FADD && i == 0) ||
          (leksem_list_.at(i).priority == FADD && i != 0 &&
           leksem_list_.at(i - 1).priority == FOPN)) {
        leksem tmp = {0.0, FDIGIT};
        PolishNat.push_back(tmp);
      }
      while ((!Buff.empty()) &&
             (Buff.back().priority >= leksem_list_.at(i).priority) &&
             !(Buff.back().priority == FPOW &&
               leksem_list_.at(i).priority == FPOW)) {
        PolishNat.push_back(Buff.back());
        Buff.pop_back();
      }
      Buff.push_back(leksem_list_.at(i));
    } else if (leksem_list_.at(i).priority == FCLS) {
      while (Buff.back().priority != FOPN) {
        PolishNat.push_back(Buff.back());
        Buff.pop_back();
      }
      Buff.pop_back();
    }
    ++i;
  }
  while (!Buff.empty()) {
    PolishNat.push_back(Buff.back());
    Buff.pop_back();
  }
  return PolishNat;
}

int s21::SmartModel::findIdent(const char *charStr, std::string &ident) {
  int shift = 0;
  while (isalpha(*charStr)) {
    ident.push_back(*charStr);
    ++shift;
    ++charStr;
  }
  return shift;
}

void s21::SmartModel::parsOpts(const std::string *ident) {
  std::map<std::string, s21::SmartModel::leksem> LeksemsMap{
      {"+", {kSum, FADD}},     {"-", {kSub, FADD}},     {"*", {kMul, FMULL}},
      {"/", {kDiv, FMULL}},    {"(", {kOpen, FOPN}},    {")", {kCls, FCLS}},
      {"^", {kPow, FPOW}},     {"mod", {kMod, FMULL}},  {"cos", {kCos, FUNC}},
      {"sin", {kSin, FUNC}},   {"tan", {kTan, FUNC}},   {"asin", {kAsin, FUNC}},
      {"acos", {kAcos, FUNC}}, {"atan", {kAtan, FUNC}}, {"sqrt", {kSqrt, FUNC}},
      {"ln", {kLn, FUNC}},     {"log", {kLog, FUNC}},   {"x", {0.0, FVAL}}};
  auto leks = LeksemsMap.find(*ident);
  if (leks != LeksemsMap.end()) {
    s21::SmartModel::leksem optLeksem;
    optLeksem = LeksemsMap.find(*ident)->second;
    leksem_list_.push_back(optLeksem);
  } else {
    throw std::invalid_argument("Incorrect input");
  }
}

double s21::SmartModel::findResult(double &res) {
  std::vector<double> d_digit;
  for (size_t i = 0; i < leksem_list_.size(); ++i) {
    if (leksem_list_.at(i).priority == FDIGIT) {
      d_digit.push_back(leksem_list_.at(i).value);
    } else if (leksem_list_.at(i).priority == FVAL) {
      d_digit.push_back(res);
    } else {
      digitOperation(d_digit, leksem_list_.at(i).value);
    }
  }
  if (d_digit.size() > 2) {
    throw std::invalid_argument("Incorrect input");
  }
  res = d_digit.back();
  return res;
}

void s21::SmartModel::digitOperation(std::vector<double> &d_digit,
                                     double type) {
  double a = d_digit.back();
  d_digit.pop_back();
  double b = 0;
  if (type == kSum) {
    b = d_digit.back();
    d_digit.pop_back();
    b = b + a;
  } else if (type == kSub) {
    b = d_digit.back();
    d_digit.pop_back();
    b = b - a;
  } else if (type == kMul) {
    b = d_digit.back();
    d_digit.pop_back();
    b = b * a;
  } else if (type == kDiv) {
    b = d_digit.back();
    d_digit.pop_back();
    b = b / a;
  } else if (type == kMod) {
    b = d_digit.back();
    d_digit.pop_back();
    b = fmod(b, a);
  } else if (type == kPow) {
    b = d_digit.back();
    d_digit.pop_back();
    b = pow(b, a);
  } else if (type == kSin) {
    b = sin(a);
  } else if (type == kCos) {
    b = cos(a);
  } else if (type == kTan) {
    b = tan(a);
  } else if (type == kAsin) {
    b = asin(a);
  } else if (type == kAcos) {
    b = acos(a);
  } else if (type == kAtan) {
    b = atan(a);
  } else if (type == kSqrt) {
    b = sqrt(a);
  } else if (type == kLog) {
    b = log10(a);
  } else if (type == kLn) {
    b = log(a);
  }
  d_digit.push_back(b);
}
