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

  virtual void part2(ostream& out) override {}
};

int main() {
  Today day;
  day.input_path = "../input/input{}-example.txt";
  day.run();
}
