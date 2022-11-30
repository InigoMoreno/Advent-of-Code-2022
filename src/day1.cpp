#include <utils.hpp>

using namespace std;
using namespace Eigen;

int countAscending(ArrayXi vec) {
  auto ascending = vec.tail(vec.size() - 1) > vec.head(vec.size() - 1);
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
    out << countAscending(vec.segment(0, vec.size() - 2) + vec.segment(1, vec.size() - 2) + vec.segment(2, vec.size() - 2));
  }
};

int main() {
  Today day;
  day.run();
}
