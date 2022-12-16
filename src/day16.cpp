#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

struct Valve {
  string name;
  int flow;
  vector<string> tunnels;
};

class Today : public Day {
 public:
  Today() : Day(16) {}

 protected:
  int N;
  vector<Valve> valves;
  vector<vector<int>> dist;  // dist[i][j] distance between valve i and j
  virtual void parse(istream& in) override {
    string line;
    while (getline(in, line) and !line.empty()) {
      Valve valve;
      vector<string> split = absl::StrSplit(line, "; ");
      valve.name = split[0].substr(6, 2);
      valve.flow = stoi(split[0].substr(23));
      valve.tunnels = absl::StrSplit(split[1], ", ");
      valve.tunnels[0] = valve.tunnels[0].substr(valve.tunnels[0].size() - 2);
      valves.push_back(valve);
    }
    N = valves.size();
    dist = vector<vector<int>>(N, vector<int>(N, -1));
  }

  virtual void part1(ostream& out) override {}

  virtual void part2(ostream& out) override {}
};

int main() {
  Today day;
  day.input_path = "../input/input{}-example.txt";
  day.run();
}
