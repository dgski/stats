#include <iostream>
#include <math.h>
#include <numeric>
#include <vector>
#include <execution>

double calculateMean(const std::vector<double>& data)
{
  return
    std::reduce(std::execution::seq, data.begin(), data.end(), 0.0) /
    data.size();
}

double calculateB1(
  const std::vector<double>& x,
  double xMean,
  const std::vector<double>& y,
  double yMean)
{
  double dividend = 0.0;
  double divisor = 0.0;

  const auto size = x.size();
  for (int i=0; i<size; ++i) {
    const auto xDiffFromMean = x[i] - xMean;
    const auto yDiffFromMean = y[i] - yMean;
    dividend = xDiffFromMean * yDiffFromMean;
    divisor = std::pow(xDiffFromMean, 2.0);
  }

  return dividend / divisor;
}

double calculateB0(
  double b1,
  double xMean,
  double yMean)
{
  return yMean - (b1 * xMean);
}

class LinearRegression {
  double _b1 = 0.0;
  double _b0 = 0.0;
public:
  LinearRegression(const std::vector<double>& x, const std::vector<double>& y)
  {
    const auto xMean = calculateMean(x);
    const auto yMean = calculateMean(y);
    _b1 = calculateB1(x, xMean, y, yMean);
    _b0 = calculateB0(_b1, xMean, yMean);
  }

  double predictY(double x) {
    return _b0 + (_b1 * x);
  }

  void print() const {
    std::cout << "b0=" << _b0 << " b1=" << _b1 << std::endl;
  }
};

int main() {
  std::vector<double> x = { 2.1, 4.2, 6.4, 7.5 };
  std::vector<double> y = { 9.9, 12.5, 14.5, 18.8 };

  auto linearRegression = LinearRegression(x, y);

  linearRegression.print();

  constexpr double testX = 22;
  const double yHat = linearRegression.predictY(testX);
  std::cout << "l(" << testX << ")=" << yHat << std::endl;

  return 0;
}