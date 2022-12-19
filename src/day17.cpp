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

  virtual void parse(istream& in) override {
    pattern = streamToString(in);
    pattern.erase(remove_if(pattern.begin(), pattern.end(), ::isspace), pattern.end());
  }

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
    long long int p_max_height = 0;
    long long int p_piece = 0;
    while (piece < N) {
      // Use this cout to find the ammount of pieces in a cycle, you should find a cycle and add the sum to the left
      // cout << piece - p_piece << ' ' << max_height - p_max_height << endl;
      p_max_height = max_height;
      p_piece = piece;
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

  virtual void part1(ostream& out) override { out << generic_part(20220); }

  virtual void part2(ostream& out) override {
    long long int N = 1000000000000;
    long long int start = 5000ll;
    long long int rep = 1725;  // There's a repetition every 1725 pieces, use cout above to find out this number
                               // In the example it is 35
    long long int times = (N - start) / rep;
    long long int remainder = (N - start) % rep;
    long long int increase = generic_part(start + rep + remainder) - generic_part(start + remainder);
    out << generic_part(start + remainder) + times * increase;
    // out << generic_part(N) << endl;
  }
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
