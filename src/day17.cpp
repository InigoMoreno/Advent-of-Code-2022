#include <utils.hpp>

using namespace std;
using namespace absl;

vector<vector<vector<bool>>> pieces = {
    {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
    },
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
    },
    {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
};
// clang-format off
vector<vector<bool>> field = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
};
// clang-format on

class Today : public Day {
 public:
  Today() : Day(17) {}

 protected:
  string pattern;

  virtual void parse(istream& in) override {
    pattern = streamToString(in);
    cout << pattern << endl;
  }

  bool check_pos_piece(pos p, int piece) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (pieces.at(piece).at(i).at(j) and field.at(p.x + i).at(p.y + j)) {
          return false;
        }
      }
    }
    return true;
  }

  int place_pos_piece(pos p, int piece) {
    int max_height_placed = -10;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (pieces.at(piece).at(i).at(j)) {
          field.at(p.x + i).at(p.y + j) = true;
          if (p.y + j > max_height_placed) max_height_placed = p.y + j;
        }
      }
    }
    return max_height_placed;
  }

  virtual void part1(ostream& out) override {
    pos p = {3, 4};
    int piece = 0;
    int max_height = 0;
    while (piece < 2022) {
      for (char c : pattern) {
        int dir = c == '>' ? 1 : -1;
        pos pushed_pos = p + pos({dir, 0});
        if (check_pos_piece(pushed_pos, piece % 5)) p = pushed_pos;
        pos lower_pos = p + pos({0, -1});
        if (check_pos_piece(lower_pos, piece % 5))
          p = lower_pos;
        else {
          int new_max_height = place_pos_piece(p, piece % 5);
          // out << new_max_height;
          while (max_height < new_max_height) {
            for (int i = 1; i <= 7; i++) {
              field[i].push_back(0);
            }
            field[0].push_back(1);
            field[8].push_back(1);
            max_height++;
          }
          p = {3, 4 + max_height};
          piece++;
          // out << piece << ' ' << max_height << endl;
          if (piece == 2022) out << max_height;
        }
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
