#include <utils.hpp>

using namespace std;
// using namespace Eigen;
// using namespace absl;

class Today : public Day {
 public:
  Today() : Day(25) {}

 protected:
  vector<string> snafus;
  virtual void parse(istream& in) override { snafus = absl::StrSplit(streamToString(in), "\n", absl::SkipEmpty()); }

  map<char, int> table = {
      {'=', -2}, {'-', -1}, {'0', 0}, {'1', 1}, {'2', 2},
  };

  typedef long long int INT;

  INT snafuToDecimal(string snafu) {
    INT decimal = 0;
    for (int i = 0; i < snafu.size(); i++) decimal += table[snafu[snafu.size() - 1 - i]] * pow(5, i);
    return decimal;
  }

  string lookup = "=-012";
  string decimalToSnafu(INT decimal) {
    auto [q, r] = std::div(decimal + 2, (INT)5);
    return (q ? decimalToSnafu(q) : "") + lookup[r];
  }

  virtual void part1(ostream& out) override {
    INT sum = 0;
    for (string snafu : snafus) sum += snafuToDecimal(snafu);
    out << decimalToSnafu(sum);
  }

  virtual void part2(ostream& out) override {}
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
