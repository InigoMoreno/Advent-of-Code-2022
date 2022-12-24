#include <assert.h>

#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

vector<pos> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
string dir_labels = ">v<^";

class Today : public Day {
 public:
  Today() : Day(22) {}

 protected:
  vector<vector<char>> map;
  vector<pair<int, char>> instructions;

  virtual void parse(istream& in) override {
    vector<string> split = StrSplit(streamToString(in), "\n\n");
    vector<string> map_lines = StrSplit(split[0], '\n');
    int width = 0;
    for (string map_line : map_lines) {
      map.push_back(vector<char>(map_line.begin(), map_line.end()));
      if (map_line.size() > width) width = map_line.size();
    }
    for (vector<char>& row : map) {
      while (row.size() < width) row.push_back(' ');
    }
    // fmt::print("{}\n", map);

    stringstream ss(split[1]);
    int len;
    char turn;
    while (ss >> len >> turn) instructions.push_back({len, turn});
    ss >> len;
    instructions.push_back({len, 'z'});
    // fmt::print("{}\n", instructions);
  }
  static pair<pos, int> next_pos_1(const vector<vector<char>>& map, pos current, int dir) {
    pos next = current + dirs[dir];
    if (next.x < 0) next.x = map.size() - 1;
    if (next.y < 0) next.y = map[next.x].size() - 1;
    if (next.x >= map.size()) next.x = 0;
    if (next.y >= map[next.x].size()) next.y = 0;
    if (map[next.x][next.y] == ' ') return next_pos_1(map, next, dir);

    return {next, dir};
  }

  // clang-format off
  // hardcoding the transitions for this cube
  //  y->
  // x  12
  // |  3
  // v 45
  //   6
  // clang-format on

  // >v<^
  static pair<pos, int> next_pos_2(const vector<vector<char>>& map, pos current, int dir) {
    pos next = current + dirs[dir];
    if (next.x < 0) {
      if (next.y < 50) {
        // going up from 4, should enter 3 from left
        next.x = (50 + next.y);
        next.y = 0;
        dir = 0;
      } else if (next.y < 100) {
        // going up from 1, should enter 6 from left
        next.x = (100 + next.y);
        next.y = 0;
        dir = 0;
      } else {
        // going up from 2, should enter 6 from down
        next.x = map.size() - 1;
        next.y = next.y - 100;
      }
    }
    if (next.y < 0) {
      if (next.x < 50) {
        // going left from 1, should enter 4 from left
        next.x = (149 - next.x);
        next.y = 0;
        dir = 0;
      } else if (next.x < 100) {
        // going left from 3, should enter 4 from up
        next.y = next.x - 50;
        next.x = 100;
        dir = 1;
      } else if (next.x < 150) {
        // going left from 4, should enter 1 from left
        next.x = (149 - next.x);
        next.y = 0;
        dir = 0;
      } else {
        // going left from 6, should enter 1 from up
        next.y = next.x - 100;
        next.x = 0;
        dir = 1;
      }
    }
    if (next.x >= map.size()) {
      if (next.y < 50) {
        // going down from 6, should enter 2 from up
        next.x = 0;
        next.y = next.y + 100;
      } else if (next.y < 100) {
        // going down from 5 should enter 6 from right
        next.x = next.y + 100;
        next.y = 49;
        dir = 2;
      } else {
        // going down from 2 should enter 3 from right
        next.x = next.y - 50;
        next.y = 99;
        dir = 2;
      }
    }
    if (next.y >= map[next.x].size()) {
      if (next.x < 50) {
        // going right from 2, should go to 5 from right
        next.x = (149 - next.x);
        next.y = 99;
        dir = 2;
      } else if (next.x < 100) {
        // going right from 3, should enter 2 from down
        next.y = next.x + 50;
        next.x = 49;
        dir = 3;
      } else if (next.x < 150) {
        // going right from 5, should enter 2 from right
        next.x = (149 - next.x);
        next.y = 149;
        dir = 2;
      } else {
        // going right from 6, should enter 5 from down
        next.y = next.x - 100;
        next.x = 149;
        dir = 3;
      }
    }
    if (map.at(next.x).at(next.y) == ' ') return next_pos_2(map, next, dir);

    return {next, dir};
  }

  int generic_part(pair<pos, int> (*next_pos)(const vector<vector<char>>&, pos, int)) {
    int dir = 0;
    pos current = next_pos(map, {0, 0}, dir).first;
    for (auto [len, turn] : instructions) {
      while (len--) {
        map[current.x][current.y] = dir_labels[dir];
        auto [next, next_dir] = next_pos(map, current, dir);
        if (map[next.x][next.y] == '#') break;
        current = next;
        dir = next_dir;
      }
      if (turn == 'R')
        dir = mod(dir + 1, 4);
      else if (turn == 'L')
        dir = mod(dir - 1, 4);
    }
    return (current.x + 1) * 1000 + (current.y + 1) * 4 + dir;
  }

  virtual void part1(ostream& out) override { out << generic_part(next_pos_1); }

  virtual void part2(ostream& out) override { out << generic_part(next_pos_2); }
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
