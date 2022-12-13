#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

class Today : public Day {
 public:
  Today() : Day(4) {}

 protected:
  typedef pair<uint, uint> range;
  vector<pair<range, range>> assignments;
  virtual void parse(istream& in) override {
    int a, b, c, d;
    char dash, comma;
    while (in >> a >> dash >> b >> comma >> c >> dash >> d) {
      assignments.push_back(pair<range, range>(range(a, b), range(c, d)));
    }
  }

  // True if range a fully contains range b
  bool fully_contains(range a, range b) { return a.first <= b.first and b.second <= a.second; }

  virtual void part1(ostream& out) override {
    uint count = 0;
    for (auto assignment : assignments) {
      if (fully_contains(assignment.first, assignment.second) or fully_contains(assignment.second, assignment.first)) count += 1;
    }
    out << count;
  }

  // True if range a overlaps range b (with a starting before than b)
  bool overlaps(range a, range b) { return a.first <= b.first and b.first <= a.second; }

  virtual void part2(ostream& out) override {
    uint count = 0;
    for (auto assignment : assignments) {
      if (overlaps(assignment.first, assignment.second) or overlaps(assignment.second, assignment.first)) count += 1;
    }
    out << count;
  }
};

int main() {
  Today day;
  day.run();
}
