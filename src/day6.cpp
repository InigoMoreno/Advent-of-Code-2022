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
      if (data[i] != data[i - 1] and data[i] != data[i - 2] and
          data[i] != data[i - 3] and data[i - 1] != data[i - 2] and
          data[i - 1] != data[i - 3] and data[i - 2] != data[i - 3]) {
        out << i + 1;
        break;
      }
    }
  }

  virtual void part2(ostream& out) override {}
};

int main() {
  Today day;
  day.run();
}
