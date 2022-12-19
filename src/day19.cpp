#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

struct Cost {
  int ore = 0;
  int clay = 0;
  int obsidian = 0;
  int geode = 0;
  int &operator[](int index) {
    switch (index) {
      case 0:
        return ore;
        break;
      case 1:
        return clay;
        break;
      case 2:
        return obsidian;
        break;
      case 3:
        return geode;
        break;

      default:
        break;
    }
  }
  bool operator>=(const Cost &other) const { return ore >= other.ore and clay >= other.clay and obsidian >= other.obsidian and geode >= other.geode; }
  Cost operator+(const Cost &other) const { return Cost({ore + other.ore, clay + other.clay, obsidian + other.obsidian, geode + other.geode}); }
  Cost operator-(const Cost &other) const { return Cost({ore - other.ore, clay - other.clay, obsidian - other.obsidian, geode - other.geode}); }
  friend std::ostream &operator<<(std::ostream &os, const Cost &d) {
    return os << "Cost(" << d.ore << ',' << d.clay << ',' << d.obsidian << ',' << d.geode << ')';
  }
};
struct Blueprint {
  Cost ore;
  Cost clay;
  Cost obsidian;
  Cost geode;
  Blueprint operator+(const Blueprint &other) const { return Blueprint({ore + other.ore, clay + other.clay, obsidian + other.obsidian, geode + other.geode}); }
  Cost &operator[](int index) {
    switch (index) {
      case 0:
        return ore;
        break;
      case 1:
        return clay;
        break;
      case 2:
        return obsidian;
        break;
      case 3:
        return geode;
        break;

      default:
        break;
    }
  }
  friend std::ostream &operator<<(std::ostream &os, const Blueprint &d) {
    return os << "Blueprint(" << d.ore << ',' << d.clay << ',' << d.obsidian << ',' << d.geode << ')';
  }
};

vector<Blueprint> blueprints;

class Today : public Day {
 public:
  Today() : Day(19) {}

 protected:
  virtual void parse(istream &in) override {
    string line;
    while (getline(in, line)) {
      if (line.empty()) continue;
      vector<string> split = StrSplit(line, "costs ");

      Blueprint b;
      // parse ore robot
      stringstream(split[1]) >> b.ore.ore;

      // parse clay robot
      stringstream(split[2]) >> b.clay.ore;

      // parse obsidian robot
      stringstream(split[3]) >> b.obsidian.ore;
      stringstream(split[3].substr(10)) >> b.obsidian.clay;

      // parse geode robot
      stringstream(split[4]) >> b.geode.ore;
      stringstream(split[4].substr(10)) >> b.geode.obsidian;

      blueprints.push_back(b);
    }
  }

  int dfs(int minutes_left, Cost robots, Cost resources, Blueprint &blueprint) {
    if (minutes_left == 0) return resources.geode;
    // int max_geodes = 0;
    int max_geodes = dfs(minutes_left - 1, robots, resources + robots, blueprint);
    for (int i = 3; i >= 0; i--) {
      if (resources >= blueprint[i]) {
        Cost new_robots = robots;
        new_robots[i]++;
        int sub_res = dfs(minutes_left - 1, new_robots, (resources - blueprint[i]) + robots, blueprint);
        if (sub_res > max_geodes) max_geodes = sub_res;
      }
    }
    // return dfs(minutes_left - 1, robots, resources + robots, blueprint);
    // if (max_geodes == 0) max_geodes = dfs(minutes_left - 1, robots, resources + robots, blueprint);
    return max_geodes;
  }

  virtual void part1(ostream &out) override { out << dfs(24, {1, 0, 0, 0}, {0, 0, 0, 0}, blueprints[0]); }

  virtual void part2(ostream &out) override {}
};

int main() {
  Today day;
  day.input_path = "../input/input{}-example.txt";
  day.run();
}
