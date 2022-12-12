#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

class Today : public Day {
 public:
  Today() : Day(10) {}

 protected:
  vector<int> signal;

  virtual void parse(istream& in) override {
    int X = 1;
    string instruction;
    while (in >> instruction) {
      if (instruction == "noop") signal.push_back(X);
      if (instruction == "addx") {
        signal.push_back(X);
        signal.push_back(X);
        int ammount;
        in >> ammount;
        X += ammount;
      }
    }
  }

  virtual void part1(ostream& out) override {
    int sum = 0;
    for (int i = 20; i < signal.size(); i += 40) sum += signal[i - 1] * i;
    out << sum;
  }

  virtual void part2(ostream& out) override {
    out << endl;
    for (int i = 0; i < signal.size(); i++) {
      int position = signal[i] - (i % 40);
      if (-1 <= position and position <= 1)
        out << "▓";
      else
        out << ' ';
      if (i % 40 == 39) out << endl;
    }
  }
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
