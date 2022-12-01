#include <utils.hpp>
#include <algorithm>
#include <fmt/ranges.h>

using namespace std;
using namespace Eigen;

int countAscending(ArrayXi vec) {
  auto ascending = vec(seq(1, last)) > vec(seq(0, last - 1));
  return ascending.count();
}

class Today : public Day {
public:
  Today() : Day(1) {
  }

protected:
  vector<int> sums;

  virtual void parse(istream& in) override {
    while (in) sums.push_back(eigenRead<ArrayXi>(in, ' ').sum());
  }
  virtual void part1(ostream& out) override {
    out << *max_element(sums.begin(), sums.end());
  }

  virtual void part2(ostream& out) override {
    nth_element(sums.begin(), sums.begin()+2, sums.end(), std::greater<int>{});
    out << sums[0] + sums[1] + sums[2];
  }
};

int main() {
  Today day;
  day.run();
}
