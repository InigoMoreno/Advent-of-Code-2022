#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

class Today : public Day {
 public:
  Today() : Day(24) {}

 protected:
  set<pos> walls;
  multimap<pos, pos> blizzards_start;
  int M, N;

  virtual void parse(istream& in) override {
    vector<string> grid;
    string line;
    while (getline(in, line)) {
      if (line.empty()) continue;
      grid.push_back(line);
    }
    M = grid.size();
    N = grid[0].size();
    for (int i = 0; i < grid.size(); i++) {
      for (int j = 0; j < grid[i].size(); j++) {
        if (grid[i][j] == '#') walls.insert({i, j});
        if (grid[i][j] == '>') blizzards_start.insert({{i, j}, {0, 1}});
        if (grid[i][j] == '<') blizzards_start.insert({{i, j}, {0, -1}});
        if (grid[i][j] == 'v') blizzards_start.insert({{i, j}, {1, 0}});
        if (grid[i][j] == '^') blizzards_start.insert({{i, j}, {-1, 0}});
      }
    }
    walls.insert({-1, 1});
    walls.insert({M, N - 2});
    // fmt::print("{}\n", positions);
  }

  vector<pos> dirs = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  virtual void part1(ostream& out) override {
    multimap<pos, pos> blizzards = blizzards_start;
    set<pos> reachable;
    reachable.insert({0, 1});
    int round = 0;
    while (reachable.count({M - 1, N - 2}) == 0) {
      round++;
      multimap<pos, pos> next_blizzards;
      for (auto [current, dir] : blizzards) {
        pos next = current + dir;
        if (next.x == 0) next.x = M - 2;
        if (next.y == 0) next.y = N - 2;
        if (next.x == M - 1) next.x = 1;
        if (next.y == N - 1) next.y = 1;
        next_blizzards.insert({next, dir});
      }
      blizzards = next_blizzards;

      set<pos> next_reachable;
      for (pos current : reachable) {
        for (pos dir : dirs) {
          pos next = current + dir;
          if (blizzards.count(next)) continue;
          if (walls.count(next)) continue;
          next_reachable.insert(next);
        }
      }
      reachable = next_reachable;

#ifndef NDEBUG
      cout << round << endl;
      for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
          if (reachable.count({i, j}))
            cout << 'E';
          else if (blizzards.count({i, j}) > 1)
            cout << blizzards.count({i, j});
          else if (blizzards.count(pos({i, j})) == 1) {
            pos p = blizzards.equal_range({i, j}).first->second;
            if (p == pos({0, 1})) cout << '>';
            if (p == pos({0, -1})) cout << '<';
            if (p == pos({1, 0})) cout << 'v';
            if (p == pos({-1, 0})) cout << '^';
          } else if (walls.count({i, j}))
            cout << "#";
          else
            cout << '.';
        }
        cout << endl;
      }
#endif
    }
    out << round;
  }

  virtual void part2(ostream& out) override {}
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
