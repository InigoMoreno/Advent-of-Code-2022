#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

class Today : public Day {
 public:
  Today() : Day(12) {}

 protected:
  vector<vector<int>> elevation;
  pos start, end;
  uint N, M;

  virtual void parse(istream& in) override {
    string file = streamToString(in);
    vector<string> lines = absl::StrSplit(file, '\n', absl::SkipWhitespace());
    N = lines.size();
    M = lines[0].size();
    // Elevation surrounded by 100m walls to avoid having to check for borders
    elevation = vector<vector<int>>(N + 2, vector<int>(M + 2, 100));
    for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++) {
        if (lines[i][j] == 'S') {
          start = {i + 1, j + 1};
          elevation[i + 1][j + 1] = 0;
        } else if (lines[i][j] == 'E') {
          end = {i + 1, j + 1};
          elevation[i + 1][j + 1] = 'z' - 'a';
        } else
          elevation[i + 1][j + 1] = lines[i][j] - 'a';
      }
  }
  typedef pair<pos, uint> pos_steps;

  virtual void part1(ostream& out) override {
    set<pos> visited;
    queue<pos_steps> q;
    q.push(pos_steps(start, 0));
    visited.insert(start);
    while (!q.empty()) {
      auto front = q.front();
      q.pop();
      pos current = front.first;
      uint steps = front.second;
      // fmt::print("{}: {}\n", front, char('a' + elevation[current.x][current.y]));
      if (current == end) {
        out << steps;
        break;
      }
      for (pos delta : vector<pos>{{0, 1}, {1, 0}, {-1, 0}, {0, -1}}) {
        pos neighbour = current + delta;
        if (elevation[neighbour.x][neighbour.y] - elevation[current.x][current.y] > 1) continue;
        if (visited.count(neighbour)) continue;
        q.push({neighbour, steps + 1});
        visited.insert(neighbour);
      }
    }
  }

  virtual void part2(ostream& out) override {}
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
