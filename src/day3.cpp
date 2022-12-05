#include <absl/algorithm/container.h>
#include <absl/strings/str_split.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <map>
#include <utils.hpp>
#include <vector>

using namespace std;
using namespace Eigen;
using namespace absl;

class Today : public Day {
 public:
  Today() : Day(3) {}

 protected:
  vector<pair<string, string>> sacks;

  virtual void parse(istream& in) override {
    string line;
    while (in >> line) {
      pair<string, string> split =
          absl::StrSplit(line, absl::ByLength(line.size() / 2));
      sacks.push_back(split);
    }
  }

  char find_union(pair<string, string>& sack){
    set<char> left(sack.first.begin(), sack.first.end());
    for (char c : sack.second) {
      if (left.find(c) != left.end()) return c;
    }
  }

  virtual void part1(ostream& out) override {
    int sum = 0;
    for (auto sack : sacks) {
      char common = find_union(sack);
      int score = common >= 'a' ? common - 'a' + 1 : common - 'A' + 27;
      sum += score;
    }
    out << sum;
  }

  virtual void part2(ostream& out) override {}
};

int main() {
  Today day;
  day.run();
}
