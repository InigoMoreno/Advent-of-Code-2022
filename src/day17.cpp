#include <deque>
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
typedef vector<vector<bool>> field_type;
field_type start_field = {
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

  virtual void parse(istream& in) override { pattern = streamToString(in); }

  bool check_pos_piece(lpos p, int piece, const field_type& field) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (pieces.at(piece).at(i).at(j) and field.at(p.x + i).at(p.y + j)) {
          return false;
        }
      }
    }
    return true;
  }

  int place_pos_piece(lpos p, int piece, field_type& field) {
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

  long long int generic_part(long long int N) {
    auto field = start_field;
    lpos p = {3, 4};
    long long int piece = 0;
    long long int max_height = 0;
    while (piece < N) {
      for (char c : pattern) {
        if (c != '>' and c != '<') continue;
        int dir = c == '>' ? 1 : -1;
        lpos pushed_pos = p + lpos({dir, 0});
        if (check_pos_piece(pushed_pos, piece % 5, field)) p = pushed_pos;
        lpos lower_pos = p + lpos({0, -1});
        if (check_pos_piece(lower_pos, piece % 5, field))
          p = lower_pos;
        else {
          long long int new_max_height = place_pos_piece(p, piece % 5, field);
          while (max_height < new_max_height) {
            for (int i = 1; i <= 7; i++) {
              field[i].push_back(0);
            }
            field[0].push_back(1);
            field[8].push_back(1);
            max_height++;
          }
          p = {3, 4l + max_height};
          piece++;
          if (piece == N) return max_height;
        }
      }
    }
  }

  virtual void part1(ostream& out) override { out << generic_part(2022); }

  virtual void part2(ostream& out) override { out << generic_part(2022);}
};

int main() {
  Today day;
  day.input_path = "../input/input{}-example.txt";
  day.run();
}
