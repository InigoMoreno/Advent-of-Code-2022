#include <utils.hpp>

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
  ArrayXi vec;
  int N;

  virtual void parse(istream& in) override {
    vec = eigenRead<ArrayXi>(in, ' ');
  }
  virtual void part1(ostream& out) override {
    out << countAscending(vec);
  }
  virtual void part2(ostream& out) override {
    out << countAscending(vec(seq(0, last - 2)) + vec(seq(1, last - 1)) + vec(seq(2, last)));
  }
};

int main() {
  Today day;
  day.run();
}
