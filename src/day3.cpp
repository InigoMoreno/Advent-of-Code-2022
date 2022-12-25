#include <utils.hpp>

using namespace std;
// using namespace Eigen;
// using namespace absl;

class Today : public Day {
 public:
  Today() : Day(3) {}

 protected:
  vector<string> sacks;

  virtual void parse(istream& in) override {
    string line;
    while (in >> line) {
      sacks.push_back(line);
    }
  }

  string find_intersection(string& left, string& right) {
    set<char> left_set(left.begin(), left.end());
    set<char> right_set(right.begin(), right.end());
    string res;
    absl::c_set_intersection(left_set, right_set, back_inserter(res));
    return res;
  }

  int score(char c) { return c >= 'a' ? c - 'a' + 1 : c - 'A' + 27; }

  virtual void part1(ostream& out) override {
    int sum = 0;
    for (const auto& sack : sacks) {
      vector<string> split = absl::StrSplit(sack, absl::ByLength(sack.size() / 2));
      string intersection = find_intersection(split[0], split[1]);
      sum += score(intersection[0]);
    }
    out << sum;
  }

  virtual void part2(ostream& out) override {
    int sum = 0;
    for (int i = 0; i < sacks.size(); i += 3) {
      string intersection_1_2 = find_intersection(sacks[i], sacks[i + 1]);
      string intersection = find_intersection(intersection_1_2, sacks[i + 2]);
      sum += score(intersection[0]);
    }
    out << sum;
  }
};

int main() {
  Today day;
  day.run();
}
