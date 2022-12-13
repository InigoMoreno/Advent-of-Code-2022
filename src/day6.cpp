#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

class Today : public Day {
 public:
  Today() : Day(6) {}

 protected:
  string data;

  virtual void parse(istream& in) override { in >> data; }

  virtual void part1(ostream& out) override {
    for (int i = 3; i < data.size(); i++) {
      if (data[i] != data[i - 1] and data[i] != data[i - 2] and data[i] != data[i - 3] and data[i - 1] != data[i - 2] and data[i - 1] != data[i - 3] and
          data[i - 2] != data[i - 3]) {
        out << i + 1;
        break;
      }
    }
  }

  virtual void part2(ostream& out) override {
    uint N = 14;
    for (int i = 0; i < data.size() - N; i++) {
      string substring = data.substr(i, N);
      if (set<char>(substring.begin(), substring.end()).size() == N) {
        out << i + N;
        break;
      }
    }
  }
};

int main() {
  Today day;
  day.run();
}
