#include <absl/algorithm/container.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

class Today : public Day {
 public:
  Today() : Day(1) {}

 protected:
  vector<int> sums;

  virtual void parse(istream& in) override {
    while (in) sums.push_back(eigenRead<ArrayXi>(in, ' ').sum());
  }
  virtual void part1(ostream& out) override { out << *c_max_element(sums); }

  virtual void part2(ostream& out) override {
    c_nth_element(sums, sums.begin() + 2, greater<int>{});
    out << sums[0] + sums[1] + sums[2];
  }
};

int main() {
  Today day;
  day.run();
}
