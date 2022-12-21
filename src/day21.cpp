#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

typedef long long int T;

class Monkey {
 public:
  string name;
  bool is_number;
  bool has_number = false;
  T number;
  string a, b;
  char op;

  void reset() { has_number = false; }

  T get(map<string, Monkey>& monkeys) {
    if (!has_number and !is_number) {
      T lhs = monkeys[a].get(monkeys);
      T rhs = monkeys[b].get(monkeys);
      switch (op) {
        case '+':
          number = lhs + rhs;
          break;
        case '-':
          number = lhs - rhs;
          break;
        case '*':
          number = lhs * rhs;
          break;
        case '/':
          number = lhs / rhs;
          break;
        default:
          return -1;
          break;
      }
      has_number = true;
    }
    return number;
  };

  friend istream& operator>>(istream& in, Monkey& D) {
    in >> D.name;
    D.name = D.name.substr(0, 4);
    in >> D.a;
    try {
      D.number = std::stoi(D.a);
      D.is_number = true;
    } catch (std::invalid_argument& e) {
      D.is_number = false;
      in >> D.op >> D.b;
    }
    return in;
  }
};

class Today : public Day {
 public:
  Today() : Day(21) {}

 protected:
  map<string, Monkey> monkeys;

  virtual void parse(istream& in) override {
    Monkey m;
    while (in >> m) {
      monkeys[m.name] = m;
    }
  }

  virtual void part1(ostream& out) override { out << monkeys["root"].get(monkeys); }

  T lhs(T i) {
    for (auto& [key, val] : monkeys) val.reset();
    monkeys["humn"].number = i;
    return monkeys[monkeys["root"].a].get(monkeys);
  }

  virtual void part2(ostream& out) override {
    T prev_lhs = 0;
    T rhs = monkeys[monkeys["root"].b].get(monkeys);
    T start = 0;
    T end = 53023858883128;
    T mid;
    T sign = lhs(end) > lhs(start) ? 1 : -1;
    while (start < end) {
      mid = start + (end - start) / 2LL;
      // fmt::print("{}, {}, {}\n", lhs(start) - rhs, lhs(mid) - rhs, lhs(end) - rhs);
      T mid_lhs = lhs(mid);
      if (mid_lhs == rhs) break;
      if (sign * mid_lhs > sign * rhs)
        end = mid;
      else
        start = mid;
    }
    // as there we are not taking into account decimals
    // there could be more than one solution in integer
    // but only one of these is valid in double
    // in our case this was always the first one, but could be otherwise
    for (int d : {-2, -1, 0, 1, 2}) {
      if (lhs(mid + d) == rhs) {
        out << mid + d;
        break;
      }
    }
  }
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
