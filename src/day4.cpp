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
      assignments.push_back({{a,b},{c,d}});
    }
  }

  // True if range a fully contains range b
  bool fully_contains(range a, range b) { return a.first <= b.first and b.second <= a.second; }

  virtual void part1(ostream& out) override {
    uint count = 0;
    for (const auto& [a, b] : assignments) {
      if (fully_contains(a, b) or fully_contains(b, a)) count += 1;
    }
    out << count;
  }

  // True if range a overlaps range b (with a starting before than b)
  bool overlaps(range a, range b) { return a.first <= b.first and b.first <= a.second; }

  virtual void part2(ostream& out) override {
    uint count = 0;
    for (const auto& [a, b] : assignments) {
      if (overlaps(a, b) or overlaps(b, a)) count += 1;
    }
    out << count;
  }
};

int main() {
  Today day;
  day.run();
}
