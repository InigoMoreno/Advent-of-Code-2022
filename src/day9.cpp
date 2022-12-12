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
      return (x < other.x) or (x==other.x and y < other.y);
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

  virtual void part1(ostream& out) override {
    set<pos> visited;
    pos head = {0, 0};
    pos tail = {0, 0};
    visited.insert(tail);
    for (motion m : motions) {
      while (m.times--) {
        switch (m.dir) {
          case 'R':
            head.x++;
            if (head.x - tail.x > 1) {
              tail.x++;
              tail.y = head.y;
            }
            break;
          case 'L':
            head.x--;
            if (head.x - tail.x < -1) {
              tail.x--;
              tail.y = head.y;
            }
            break;
          case 'U':
            head.y++;
            if (head.y - tail.y > 1) {
              tail.y++;
              tail.x = head.x;
            }
            break;
          case 'D':
            head.y--;
            if (head.y - tail.y < -1) {
              tail.y--;
              tail.x = head.x;
            }
            break;
        }
        visited.insert(tail);
      }
    }
    out << visited.size();
  }

  virtual void part2(ostream& out) override {}
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
