#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

class Today : public Day {
 public:
  Today() : Day(14) {}

 protected:
  vector<vector<bool>> rock;
  pos min, max;
  int N, M;

  virtual void parse(istream& in) override {
    // First store them in a set
    set<pos> rock_set;
    std::string line;
    while (getline(in, line)) {
      vector<pos> path;
      for (string pos_string : (vector<string>)StrSplit(line, " -> ")) {
        pos new_pos;
        char comma;
        stringstream(pos_string) >> new_pos.x >> comma >> new_pos.y;
        path.push_back(new_pos);
      }
      for (int i = 1; i < path.size(); i++) {
        pos diff = path[i] - path[i - 1];
        if (diff.x == 0) {
          for (int y = path[i - 1].y; y <= path[i].y; y++) rock_set.insert({path[i].x, y});
          for (int y = path[i].y; y <= path[i - 1].y; y++) rock_set.insert({path[i].x, y});
        } else {
          for (int x = path[i - 1].x; x <= path[i].x; x++) rock_set.insert({x, path[i].y});
          for (int x = path[i].x; x <= path[i - 1].x; x++) rock_set.insert({x, path[i].y});
        }
      }
    }

    // find the topleft and bottomright corners
    min = *rock_set.begin();
    max = *rock_set.rbegin();
    for (pos rock : rock_set) {
      // if (rock.x < min.x) min.x = rock.x;
      // if (rock.x > max.x) max.x = rock.x;
      // if (rock.y < min.y) min.y = rock.y;
      if (rock.y > max.y) max.y = rock.y;
    }

    // expand bounding box to allow for pyramidal sand
    min.y = 0;
    max.y += 2;
    min.x = 500 - max.y - 2;
    max.x = 500 + max.y + 2;

    // transform them into a vector
    N = max.y - min.y + 1;
    M = max.x - min.x + 1;

    rock = vector<vector<bool>>(N, vector<bool>(M, false));
    for (int y = min.y; y <= max.y; y++) {
      for (int x = min.x; x <= max.x; x++) {
        rock[y - min.y][x - min.x] = rock_set.find({x, y}) != rock_set.end();
      }
    }
  }

  int count_sand(const vector<vector<bool>>& rock) {
    vector<vector<bool>> sand(rock.size(), vector<bool>(rock[0].size(), false));
    pos start = {500 - min.x, 0 - min.y};
    vector<pos> deltas = {{0, 1}, {-1, 1}, {1, 1}};
    int i = 0;
    while (true) {          // for each grain of sand
      pos current = start;  // start at begining
      bool moved = true;
      while (moved) {  // while the grain has not stopped
        moved = false;
        if (current.y - min.y == max.y) return i;  // if reach bottom, return i
        for (pos delta : deltas) {                 // look for possible movements in order
          pos next = current + delta;
          if (!sand[next.y][next.x] and !rock[next.y][next.x]) {  // if no rock nor sand
            current = next;                                       // move
            moved = true;
            break;
          }
        }
      }
      i++;
      sand[current.y][current.x] = true;  // set grain where it stopped
      if (current == start) return i;     // if placed a grain at the start return i

      // print
      // if (i % 100 == 0) {
      //   system("clear");
      //   cout << i << endl;
      //   for (int i = 0; i < N; i++) {
      //     for (int j = 0; j < M; j++) {
      //       if (rock[i][j])
      //         cout << "▓";
      //       else if (sand[i][j])
      //         cout << "o";
      //       else
      //         cout << "·";
      //     }
      //     cout << endl;
      //   }
      // }
    }
  }

  virtual void part1(ostream& out) override { out << count_sand(rock); }

  virtual void part2(ostream& out) override {
    vector<vector<bool>> extended_rock = rock;
    for (int j = 0; j < M; j++) extended_rock[N - 1][j] = true;
    out << count_sand(extended_rock);
  }
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
  return 0;
}
