#include <fmt/format.h>

#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

class dense_integer_set {};

class Today : public Day {
 public:
  Today() : Day(15) {}

 protected:
  vector<pair<pos, pos>> sensorsBeacons;

  pos parse_pos(string s) {
    vector<string> split = StrSplit(s, ", ");
    return pos({stoi(split[0].substr(2)), stoi(split[1].substr(2))});
  }

  virtual void parse(istream& in) override {
    string line;
    while (getline(in, line)) {
      if (line.empty()) continue;
      // Sensor at x=2692921, y=2988627: closest beacon is at x=2453611, y=3029623
      vector<string> split = StrSplit(line, "at ");
      string second_pos_s = split[2];
      split = StrSplit(split[1], ": ");
      string first_pos_s = split[0];
      sensorsBeacons.push_back({parse_pos(first_pos_s), parse_pos(second_pos_s)});
    }
  }

  virtual void part1(ostream& out) override {
    int Y = abs(sensorsBeacons[0].first.y) < 100 ? 10 : 2000000;
    set<int> beacons_at_Y;
    // First contains a position second is +1/-1 depending if its the start/end of a range
    vector<pair<int, int>> ranges;
    for (auto sensorBeacon : sensorsBeacons) {
      pos sensor = sensorBeacon.first;
      pos beacon = sensorBeacon.second;
      if (beacon.y == Y) beacons_at_Y.insert(beacon.x);
      // Distance from beacon
      int dist = (sensor - beacon).manhattan_norm();
      int x_range_at_Y = dist - abs(Y - sensor.y);
      if (x_range_at_Y <= 0) continue;
      int left = sensor.x - x_range_at_Y;
      int right = sensor.x + x_range_at_Y;
      ranges.push_back({left, +1});
      ranges.push_back({right, -1});
    }
    c_sort(ranges);
    int sum = 0;
    int range_count = 1;
    for (int i = 1; i < ranges.size(); i++) {
      if (range_count > 0) {
        sum += ranges[i].first - ranges[i - 1].first;
        // fmt::print("Adding range {}->{}: {}\n", ranges[i - 1].first, ranges[i].first, sum);
      } else {
        if (ranges[i].first != ranges[i - 1].first) {
          sum++;
          // fmt::print("Empty space, adding one {}->{}: {}\n", ranges[i - 1].first, ranges[i].first, sum);
        };
      }
      range_count += ranges[i].second;
    }
    out << sum + 1 - beacons_at_Y.size();
  }

  virtual void part2(ostream& out) override {
    int N = abs(sensorsBeacons[0].first.y) < 100 ? 20 : 4000000;
    N = sensorsBeacons.size();
    vector<int> mini(N), maxi(N), minj(N), maxj(N);

    for (int idx = 0; idx < N; idx++) {
      pos sensor = sensorsBeacons[idx].first;
      pos beacon = sensorsBeacons[idx].second;
      int dist = (sensor - beacon).manhattan_norm();
      // Transforming to coordinates i=-x+y; j=x+y
      // The restrictions become rectangles
      // As there is only one solution
      // One of these rectangles must end just two units after another starts to let a line in between
      // This happens both for dimension i and for dimension j
      mini[idx] = -sensor.x + sensor.y - dist;
      maxi[idx] = -sensor.x + sensor.y + dist;
      minj[idx] = sensor.x + sensor.y - dist;
      maxj[idx] = sensor.x + sensor.y + dist;
    }
    c_sort(mini);
    c_sort(maxi);
    c_sort(minj);
    c_sort(maxj);
    int i, j;
    int b = 0;
    for (int a = 0; a < N; a++) {
      while (mini[a] - maxi[b] > 2) b++;
      if (mini[a] - maxi[b] == 2) {
        i = mini[a] - 1;
        break;
      }
    }
    int d = 0;
    for (int c = 0; c < N; c++) {
      while (minj[c] - maxj[d] > 2) d++;
      if (minj[c] - maxj[d] == 2) {
        j = minj[c] - 1;
        break;
      }
    }
    long long int x = (j - i) / 2;
    int y = (i + j) / 2;
    out << x * 4000000 + y;
  }
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
