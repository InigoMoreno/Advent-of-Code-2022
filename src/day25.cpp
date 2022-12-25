#include <concepts>
#include <utils.hpp>

using namespace std;
// using namespace Eigen;
// using namespace absl;

map<char, int> table = {
    {'=', -2}, {'-', -1}, {'0', 0}, {'1', 1}, {'2', 2},
};

template <integral INT>
INT snafuToDecimal(string snafu) {
  INT decimal = 0;
  for (int i = 0; i < snafu.size(); i++) decimal += table[snafu[snafu.size() - 1 - i]] * pow(5, i);
  return decimal;
}

template <integral INT>
string decimalToSnafu(INT decimal) {
  auto [q, r] = std::div(decimal + 2, (INT)5);
  return (q ? decimalToSnafu(q) : "") + "=-012"[r];
}

template <integral INT>
class Snafu {
 public:
  mutable INT _decimal;

 public:
  Snafu(INT decimal) : _decimal(decimal){};
  Snafu(string snafu) : _decimal(snafuToDecimal<INT>(snafu)){};
  const Snafu& operator+=(const Snafu& other) const {
    this->_decimal += other._decimal;
    return *this;
  }
  friend std::ostream& operator<<(std::ostream& os, const Snafu& d) { return os << decimalToSnafu(d._decimal); }
};

class Today : public Day {
 public:
  Today() : Day(25) {}

 protected:
  vector<string> snafus;
  virtual void parse(istream& in) override { snafus = absl::StrSplit(streamToString(in), "\n", absl::SkipEmpty()); }

  virtual void part1(ostream& out) override {
    Snafu<long long int> sum = 0;
    for (string snafu : snafus) sum += snafu;
    out << sum;
  }

  virtual void part2(ostream& out) override {}
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
