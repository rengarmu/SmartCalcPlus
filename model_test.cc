// #include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "model/s21_model.h"

TEST(SmartModel, test_01) {
  s21::SmartModel test;
  std::string str = "-(-1)";
  double res = 0.;
  test.MakeList(str);
  EXPECT_EQ(test.findResult(res), 1.);
}

TEST(SmartModel, test_2) {
  s21::SmartModel test;
  std::string str = "35+cos(0)";
  double res = 0.;
  test.MakeList(str);
  EXPECT_EQ(test.findResult(res), 36);
}

TEST(SmartModel, test_3) {
  s21::SmartModel test;
  std::string str = "cos(4-2+sqrt(4))";
  double res = 0.;
  test.MakeList(str);
  EXPECT_NEAR(test.findResult(res), -0.6536436, 6);
}

TEST(SmartModel, test_4) {
  s21::SmartModel test;
  std::string str = "sin(cos((4)-(8)-2))";
  double res = 0.;
  test.MakeList(str);
  EXPECT_NEAR(test.findResult(res), 0.819289, 6);
}

TEST(SmartModel, test_5) {
  s21::SmartModel test;
  std::string str = "1-sin(cos(4-2+sqrt(4)-(6/3)-2))";
  double res = 0.;
  test.MakeList(str);
  EXPECT_NEAR(test.findResult(res), 0.1585290, 6);
}

TEST(SmartModel, test_6) {
  s21::SmartModel test;
  std::string str = "4 * (- 1)";
  double res = 0.;
  test.MakeList(str);
  EXPECT_EQ(test.findResult(res), -4.);
}

TEST(SmartModel, test_7) {
  s21::SmartModel test;
  std::string str = "(14mod3^sin(1))";
  double res = 0.;
  test.MakeList(str);
  EXPECT_NEAR(test.findResult(res), 1.397587, 6);
}

TEST(SmartModel, test_8) {
  s21::SmartModel test;
  std::string str = "cos(1)";
  double res = 0.;
  test.MakeList(str);
  EXPECT_NEAR(test.findResult(res), 0.540302, 6);
}

TEST(SmartModel, test_9) {
  s21::SmartModel test;
  std::string str = "sqrt(cos( sin(2+9*6^1.2-tan(0))) ) mod0.1";
  double res = 0.;
  test.MakeList(str);
  EXPECT_NEAR(test.findResult(res), 0.0857781, 6);
}

TEST(SmartModel, test_10) {
  s21::SmartModel test;
  std::string str = "-5.0mod(-3.0)";
  double res = 0.;
  test.MakeList(str);
  EXPECT_EQ(test.findResult(res), -2.);
}

TEST(SmartModel, test_11) {
  s21::SmartModel test;
  std::string str = "1+2+(3*4)+(5.1+6.8)";
  double res = 0.;
  test.MakeList(str);
  EXPECT_EQ(test.findResult(res), 26.9);
}

TEST(SmartModel, test_12) {
  s21::SmartModel test;
  std::string str = "3+4*2/(1-5)^2^3";
  double res = 0.;
  test.MakeList(str);
  EXPECT_NEAR(test.findResult(res), 3.0001220, 6);
}

TEST(SmartModel, test_13) {
  s21::SmartModel test;
  std::string str = "ln(2)+log(5)";
  double res = 0.;
  test.MakeList(str);
  EXPECT_NEAR(test.findResult(res), 1.3921171849, 6);
}

TEST(SmartModel, test_14) {
  s21::SmartModel test;
  std::string str = "2^3^2";
  double res = 0.;
  test.MakeList(str);
  EXPECT_EQ(test.findResult(res), 512);
}

TEST(SmartModel, test_15) {
  s21::SmartModel test;
  std::string str = "2^3*2";
  double res = 0.;
  test.MakeList(str);
  EXPECT_EQ(test.findResult(res), 16);
}

TEST(SmartModel, test_16) {
  s21::SmartModel test;
  double res = 0.;
  test.MakeList("cos(3)^2");
  EXPECT_NEAR(test.findResult(res), 0.9800851, 6);
}

TEST(SmartModel, test_17) {
  s21::SmartModel test;
  double res = 0.;
  test.MakeList("1.77215424758523+0.201357920790331*0.785398163397448");
  EXPECT_NEAR(test.findResult(res), 1.9303003, 6);
}

TEST(SmartModel, test_18) {
  s21::SmartModel test;
  double res = 0.;
  test.MakeList("atan(1)");
  EXPECT_NEAR(test.findResult(res), 0.785398, 6);
}

TEST(SmartModel, test_19) {
  s21::SmartModel test;
  double res = 0.;
  test.MakeList("acos(-0.2)+asin(0.2)");
  EXPECT_NEAR(test.findResult(res), 1.973512, 6);
}

TEST(SmartModel, test_20) {
  s21::SmartModel test;
  double res = 0.;
  test.MakeList("atan(1)^2");
  EXPECT_NEAR(test.findResult(res), 0.616850, 6);
}

TEST(SmartModelValue, test_1) {
  s21::SmartModel test;
  std::string str = "-x^x";
  double res = 2.;
  test.MakeList(str);
  EXPECT_EQ(test.findResult(res), -4.);
}

TEST(SmartModelValue, test_2) {
  s21::SmartModel test;
  std::string str = "3+tan(x)";
  double res = 1.;
  test.MakeList(str);
  EXPECT_NEAR(test.findResult(res), 4.55740772, 6);
}

TEST(SmartModelThrow, test_1) {
  s21::SmartModel test;
  EXPECT_THROW(test.MakeList("-()*7"), std::runtime_error);
}

TEST(SmartModelThrow, test_2) {
  s21::SmartModel test;
  EXPECT_THROW(test.MakeList("tan(2))"), std::runtime_error);
}

TEST(SmartModelThrow, test_3) {
  s21::SmartModel test;
  EXPECT_THROW(test.MakeList("*sin(3)+tan(x)"), std::runtime_error);
}

TEST(SmartModelThrow, test_4) {
  s21::SmartModel test;
  EXPECT_THROW(test.MakeList("func3+tan(x)"), std::invalid_argument);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}