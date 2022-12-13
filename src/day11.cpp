#include <queue>
#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

typedef unsigned long long int T;
class Monkey {
 public:
  queue<T> items;
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

  T inspect() {
    T item = items.front();
    items.pop();
    inspected_times++;

    // Apply operation
    T value1 = field1 == "old" ? item : stoi(field1);
    T value2 = field2 == "old" ? item : stoi(field2);
    if (operation == '*') item = value1 * value2;
    if (operation == '+') item = value1 + value2;

    return item;
  }

  friend std::ostream& operator<<(std::ostream& os, const Monkey& d) {
    return os << fmt::format("{{items.front():{}, operation:{}{}{}, test:{}, monkeys:{}:{}}}", d.items.front(), d.field1, d.operation, d.field2, d.test,
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
    for (string monkey_data : (vector<string>)absl::StrSplit(file, "\n\n", absl::SkipWhitespace())) {
      monkeys.push_back(Monkey(monkey_data));
    };
  }

  virtual void part1(ostream& out) override {
    vector<Monkey> monkeys_copy(monkeys);
    for (int i = 0; i < 20; i++) {
      for (Monkey& monkey : monkeys_copy) {
        while (!monkey.items.empty()) {
          auto item = monkey.inspect();
          item /= 3;
          bool divisible = item % monkey.test == 0;
          monkeys_copy[divisible ? monkey.monkey_if : monkey.monkey_else].items.push(item);
        }
      }
    }

    vector<uint> inspected_times;
    for (const Monkey& monkey : monkeys_copy) {
      inspected_times.push_back(monkey.inspected_times);
    }
    c_sort(inspected_times, greater<uint>());
    out << inspected_times[0] * inspected_times[1];
  }

  virtual void part2(ostream& out) override {
    vector<Monkey> monkeys_copy(monkeys);

    T common_factor = 1;
    for (Monkey& monkey : monkeys_copy) common_factor *= monkey.test;

    for (int i = 0; i < 10000; i++) {
      for (Monkey& monkey : monkeys_copy) {
        while (!monkey.items.empty()) {
          auto item = monkey.inspect();
          item %= common_factor;
          bool divisible = item % monkey.test == 0;
          monkeys_copy[divisible ? monkey.monkey_if : monkey.monkey_else].items.push(item);
        }
      }
    }

    vector<T> inspected_times;
    for (const Monkey& monkey : monkeys_copy) {
      inspected_times.push_back(monkey.inspected_times);
    }
    c_sort(inspected_times, greater<T>());
    out << inspected_times[0] * inspected_times[1];
  }
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
