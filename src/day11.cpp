#include <queue>
#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

class Monkey {
 public:
  queue<uint> items;
  string field1, field2;
  char operation;
  uint test, monkey_if, monkey_else;
  uint inspected_times = 0;

  Monkey(string data) {
    vector<string> split = StrSplit(data, "\n  ");
    vector<string> item_strings = StrSplit(split[1].substr(16), ", ");
    for (string item_string : item_strings) {
      items.push(stoi(item_string));
    }
    stringstream(split[2].substr(17)) >> field1 >> operation >> field2;
    test = stoi(split[3].substr(19));
    monkey_if = stoi(split[4].substr(27));
    monkey_else = stoi(split[5].substr(28));
  }

  uint inspect() {
    uint item = items.front();
    items.pop();
    inspected_times++;

    // Apply operation
    uint value1 = field1 == "old" ? item : stoi(field1);
    uint value2 = field2 == "old" ? item : stoi(field2);
    if (operation == '*') item = value1 * value2;
    if (operation == '+') item = value1 + value2;

    return item;
  }

  friend std::ostream& operator<<(std::ostream& os, const Monkey& d) {
    return os << fmt::format(
               "{{items.front():{}, operation:{}{}{}, test:{}, monkeys:{}:{}}}",
               d.items.front(), d.field1, d.operation, d.field2, d.test,
               d.monkey_if, d.monkey_else);
  }
};

class Today : public Day {
 public:
  Today() : Day(11) {}

 protected:
  vector<Monkey> monkeys;

  virtual void parse(istream& in) override {
    string file = streamToString(in);
    for (string monkey_data :
         (vector<string>)absl::StrSplit(file, "\n\n", absl::SkipWhitespace())) {
      monkeys.push_back(Monkey(monkey_data));
    };
  }

  virtual void part1(ostream& out) override {
    for (int i = 0; i < 20; i++) {
      for (Monkey& monkey : monkeys) {
        while (!monkey.items.empty()) {
          uint item = monkey.inspect();
          item /= 3;
          bool divisible = item % monkey.test == 0;
          monkeys[divisible ? monkey.monkey_if : monkey.monkey_else].items.push(
              item);
        }
      }
    }

    vector<uint> inspected_times;
    for (const Monkey& monkey : monkeys) {
      inspected_times.push_back(monkey.inspected_times);
    }
    c_sort(inspected_times, greater<uint>());
    out << inspected_times[0] * inspected_times[1];
  }

  virtual void part2(ostream& out) override {}
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
