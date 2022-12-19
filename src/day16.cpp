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
  int start;
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
      if (valve.name == "AA") start = valves.size() - 1;
    }
    N = valves.size();
    dist = vector<vector<int>>(N, vector<int>(N, 1000));
    for (int i = 0; i < N; i++) {
      for (string tunnel : valves[i].tunnels) {
        for (int j = 0; j < N; j++) {
          if (tunnel == valves[j].name) {
            dist[i][j] = 1;
            break;
          }
        }
      }
    }

    for (int k = 0; k != N; k++)
      for (int i = 0; i != N; i++)
        for (int j = 0; j != N; j++) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
  }

  int dfs(int pos, int previous_pressure, int minutes_left, vector<bool>& opened) {
    opened[pos] = true;
    int total_flow = 0;
    for (int i = 0; i < N; i++) {
      if (opened[i]) total_flow += valves[i].flow;
    }
    int max_final_pressure = previous_pressure + total_flow * minutes_left;
    for (int i = 0; i < N; i++) {
      if (!opened[i] and dist[pos][i] < minutes_left and valves[i].flow > 0) {
        int time = dist[pos][i] + 1;
        int sub_res = dfs(i, previous_pressure + total_flow * time, minutes_left - time, opened);
        if (sub_res > max_final_pressure) max_final_pressure = sub_res;
      }
    }
    opened[pos] = false;
    return max_final_pressure;
  }

  virtual void part1(ostream& out) override {
    vector<bool> opened(valves.size(), false);
    out << dfs(start, 0, 30, opened);
  }

  int two_person_dfs(int pos, int pos_other, int previous_pressure, int minutes_left, int minutes_left_other, vector<bool>& opened) {
    if (minutes_left_other > minutes_left) {
      swap(pos, pos_other);
      swap(minutes_left, minutes_left_other);
    }
    opened[pos] = true;
    int total_flow = 0;
    for (int i = 0; i < N; i++) {
      if (opened[i]) total_flow += valves[i].flow;
    }
    int max_final_pressure = previous_pressure + total_flow * minutes_left;
    for (int i = 0; i < N; i++) {
      if (!opened[i] and dist[pos][i] < minutes_left and valves[i].flow > 0) {
        int time = dist[pos][i] + 1;
        // fmt::print("{},{},{},{},{}\n", pos_other, i, previous_pressure + total_flow * (minutes_left - minutes_left_other), minutes_left_other,
        //            minutes_left - time);
        int sub_res = two_person_dfs(i, pos_other, previous_pressure + total_flow * min(minutes_left - minutes_left_other, time), minutes_left - time,
                                     minutes_left_other, opened);
        if (sub_res > max_final_pressure) max_final_pressure = sub_res;
      }
    }
    if (minutes_left_other > 0) {
      int time = minutes_left;
      int sub_res = two_person_dfs(pos, pos_other, previous_pressure + total_flow * min(minutes_left - minutes_left_other, time), minutes_left - time,
                                   minutes_left_other, opened);
      if (sub_res > max_final_pressure) max_final_pressure = sub_res;
    }
    opened[pos] = false;
    return max_final_pressure;
  }

  virtual void part2(ostream& out) override {
    vector<bool> opened(valves.size(), false);
    out << two_person_dfs(start, start, 0, 26, 26, opened);
  }
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
