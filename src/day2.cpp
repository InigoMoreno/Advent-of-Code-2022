#include <utils.hpp>

using namespace std;
// using namespace Eigen;
// using namespace absl;

class Today : public Day {
 public:
  Today() : Day(2) {}

 protected:
  // points[i][j] = score for playing j against i
  vector<vector<uint>> points = {
      {3, 6, 0},
      {0, 3, 6},
      {6, 0, 3},
  };
  vector<pair<uint, uint>> strategy;

  virtual void parse(istream& in) override {
    char a, b;
    while (in >> a >> b) strategy.push_back({a - 'A', b - 'X'});
  }
  virtual void part1(ostream& out) override {
    uint score = 0;
    for (const auto& [a, b] : strategy) score += points[a][b] + b + 1;
    out << score;
  }

  // points[i][j] = piece need to played to win/draw/loose (j) against piece i
  vector<vector<uint>> wdl_move = {
      {2, 0, 1},
      {0, 1, 2},
      {1, 2, 0},
  };

  virtual void part2(ostream& out) override {
    uint score = 0;
    for (const auto& [a, b] : strategy) score += b * 3 + wdl_move[a][b] + 1;
    out << score;
  }
};

int main() {
  Today day;
  day.run();
}
