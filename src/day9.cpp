#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

class Today : public Day {
 public:
  Today() : Day(9) {}

 protected:
  struct motion {
    char dir;
    uint times;
  };
  struct pos {
    int x;
    int y;
    bool operator<(const pos& other) const {
      return (x < other.x) or (x == other.x and y < other.y);
    }
    friend std::ostream& operator<<(std::ostream& os, const pos& d) {
      return os << '(' << d.x << ',' << d.x << ')';
    }
  };
  vector<motion> motions;

  virtual void parse(istream& in) override {
    motion m;
    while (in >> m.dir >> m.times) {
      motions.push_back(m);
    }
  }

  // Pull tail towards head
  bool pull(const pos& head, pos& tail) {
    if (head.x - tail.x > 1) {
      tail.x++;
      if (tail.y > head.y) tail.y--;
      if (tail.y < head.y) tail.y++;
      return true;
    }
    if (head.x - tail.x < -1) {
      tail.x--;
      if (tail.y > head.y) tail.y--;
      if (tail.y < head.y) tail.y++;
      return true;
    }
    if (head.y - tail.y > 1) {
      tail.y++;
      if (tail.x > head.x) tail.x--;
      if (tail.x < head.x) tail.x++;
      return true;
    }
    if (head.y - tail.y < -1) {
      tail.y--;
      if (tail.x > head.x) tail.x--;
      if (tail.x < head.x) tail.x++;
      return true;
    }
    return false;
  }

  void move(pos& head, char dir) {
    switch (dir) {
      case 'R':
        head.x++;
        break;
      case 'L':
        head.x--;
        break;
      case 'U':
        head.y++;
        break;
      case 'D':
        head.y--;
        break;
    }
  }

  int generic_part(int N) {
    set<pos> visited;
    vector<pos> snake(N + 1, {0, 0});
    visited.insert(snake[N]);
    for (motion m : motions) {
      while (m.times--) {
        move(snake[0], m.dir);
        for (int i = 1; i <= N; i++) {
          pull(snake[i - 1], snake[i]);
        }
        visited.insert(snake[N]);
      }
    }
    return visited.size();
  }

  virtual void part1(ostream& out) override { out << generic_part(1); }

  virtual void part2(ostream& out) override { out << generic_part(9); }
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
