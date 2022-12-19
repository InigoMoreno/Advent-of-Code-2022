#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

typedef vector<bool> VB;
typedef vector<VB> VVB;
typedef vector<VVB> VVVB;

class Today : public Day {
 public:
  Today() : Day(18) {}

 protected:
  VVVB droplet;
  vector<tuple<int, int, int>> data;
  virtual void parse(istream& in) override {
    int a, b, c;
    int M = 0, N = 0, O = 0;
    char comma;
    while (in >> a >> comma >> b >> comma >> c) {
      data.push_back({a + 1, b + 1, c + 1});
      if (a > M) M = a;
      if (b > N) N = b;
      if (c > O) O = c;
    }
    droplet = VVVB(M + 3, VVB(N + 3, VB(O + 3, false)));
    for (auto [x, y, z] : data) droplet[x][y][z] = true;
  }

  vector<tuple<int, int, int>> dirs = {
      {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1},
  };
  virtual void part1(ostream& out) override {
    int count = 0;
    for (auto [x, y, z] : data)
      for (auto [dx, dy, dz] : dirs)
        if (!droplet.at(x + dx).at(y + dy).at(z + dz)) count++;
    out << count;
  }

  virtual void part2(ostream& out) override {
    int M = droplet.size();
    int N = droplet[0].size();
    int O = droplet[0][0].size();
    VVVB exterior(M, VVB(N, VB(O, false)));
    queue<tuple<int, int, int>> q;
    q.push({0, 0, 0});
    exterior[0][0][0] = true;
    while (!q.empty()) {
      auto [x, y, z] = q.front();
      q.pop();
      for (auto [dx, dy, dz] : dirs) {
        if (x + dx < 0 or x + dx >= M) continue;
        if (y + dy < 0 or y + dy >= N) continue;
        if (z + dz < 0 or z + dz >= O) continue;
        if (exterior.at(x + dx).at(y + dy).at(z + dz)) continue;
        if (droplet.at(x + dx).at(y + dy).at(z + dz)) continue;
        exterior.at(x + dx).at(y + dy).at(z + dz) = true;
        q.push({x + dx, y + dy, z + dz});
      }
    }

    int count = 0;
    for (auto [x, y, z] : data)
      for (auto [dx, dy, dz] : dirs)
        if (exterior.at(x + dx).at(y + dy).at(z + dz)) count++;
    out << count;
  }
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
