#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

class Today : public Day {
 public:
  Today() : Day(23) {}

 protected:
  vector<pos> positions;
  virtual void parse(istream& in) override {
    vector<string> grid;
    string line;
    while (getline(in, line)) {
      if (line.empty()) continue;
      grid.push_back(line);
    }
    for (int i = 0; i < grid.size(); i++) {
      for (int j = 0; j < grid[i].size(); j++) {
        if (grid[i][j] == '#') positions.push_back(pos({i, j}));
      }
    }
    // fmt::print("{}\n", positions);
  }

  vector<pos> dirs = {{-1, 0}, {-1, 1}, {-1, -1}, {1, 0}, {1, -1}, {1, 1}, {0, -1}, {0, 1}};
  vector<pos> cardinal_dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  vector<vector<pos>> check = {{{-1, 0}, {-1, 1}, {-1, -1}}, {{1, 0}, {1, 1}, {1, -1}}, {{0, -1}, {-1, -1}, {1, -1}}, {{0, 1}, {-1, 1}, {1, 1}}};

  bool round(set<pos>& positions_set, int round_number) {
    multimap<pos, pos> proposals;

    for (pos position : positions_set) {
      bool wants_to_move = false;
      for (pos dir : dirs)
        if (positions_set.count(position + dir)) wants_to_move = true;
      if (!wants_to_move) continue;

      for (int i = 0; i < 4; i++) {
        bool can_move = true;
        int cardinal_dir_idx = (round_number + i) % 4;
        for (pos dir : check[cardinal_dir_idx])
          if (positions_set.count(position + dir)) can_move = false;
        if (can_move) {
          proposals.insert({position + cardinal_dirs[cardinal_dir_idx], position});
          break;
        }
      }
    }
    bool any_moved = false;
    for (auto [desired, current] : proposals) {
      if (proposals.count(desired) > 1) continue;
      any_moved = true;
      positions_set.insert(desired);
      positions_set.erase(current);
    }
    return any_moved;
  }

  virtual void part1(ostream& out) override {
    set<pos> positions_set(positions.begin(), positions.end());
    for (int round_number = 0; round_number < 10; round_number++) {
      round(positions_set, round_number);
    }

    pos min = *positions_set.begin();
    pos max = *positions_set.begin();
    for (pos position : positions_set) {
      if (position.x > max.x) max.x = position.x;
      if (position.y > max.y) max.y = position.y;
      if (position.x < min.x) min.x = position.x;
      if (position.y < min.y) min.y = position.y;
    }
    cout << (max.x - min.x + 1) * (max.y - min.y + 1) - positions_set.size();
  }

  virtual void part2(ostream& out) override {
    set<pos> positions_set(positions.begin(), positions.end());
    int round_number = 0;
    while (round(positions_set, round_number)) {
      round_number++;
    }
    out << round_number + 1;
  }
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
