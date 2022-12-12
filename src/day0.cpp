#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

class Today : public Day {
 public:
  Today() : Day(0) {}

 protected:
  virtual void parse(istream& in) override {
  }

  virtual void part1(ostream& out) override {
  }

  virtual void part2(ostream& out) override {
  }
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
