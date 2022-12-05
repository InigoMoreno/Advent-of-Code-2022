#include <stack>
#include <utils.hpp>

using std::pair;
using std::string;
using std::vector;

class Today : public Day {
 public:
  Today() : Day(5) {}

 protected:
  typedef std::tuple<uint, uint, uint> Instruction;
  vector<std::stack<char>> stacks;
  vector<Instruction> instructions;

  virtual void parse(std::istream& in) override {
    string input = streamToString(in);
    pair<string, string> split = absl::StrSplit(input, "\n\n");

    // parse first lines into stacks
    vector<string> first_lines = absl::StrSplit(split.first, "\n");
    int N = (*(first_lines.end() - 1)).size();
    for (int i = 1; i < N; i += 4) {
      std::stack<char> stack;
      for (int j = first_lines.size() - 2; j >= 0; j--) {
        if (first_lines[j].size() <= i) break;
        if (first_lines[j][i] == ' ') break;
        stack.push(first_lines[j][i]);
      }
      stacks.push_back(stack);
    }

    // parse second lines into instructions
    std::stringstream ss(split.second);
    string move, from, to;
    int a, b, c;
    while (ss >> move >> a >> from >> b >> to >> c) {
      instructions.push_back(Instruction(a, b, c));
    }
  }

  virtual void part1(std::ostream& out) override {
    vector<std::stack<char>> stacks_copy = stacks;
    for (Instruction instruction : instructions) {
      uint times = std::get<0>(instruction);
      uint i = std::get<1>(instruction) - 1;
      uint j = std::get<2>(instruction) - 1;
      while (times--) {
        stacks_copy[j].push(stacks_copy[i].top());
        stacks_copy[i].pop();
      }
    }
    for (auto stack : stacks_copy) {
      if (!stack.empty()) {
        out << stack.top();
      }
    }
  }

  virtual void part2(std::ostream& out) override {
    vector<std::stack<char>> stacks_copy = stacks;
    for (Instruction instruction : instructions) {
      uint times = std::get<0>(instruction);
      uint i = std::get<1>(instruction) - 1;
      uint j = std::get<2>(instruction) - 1;
      std::stack<char> temp;
      while (times--) {
        temp.push(stacks_copy[i].top());
        stacks_copy[i].pop();
      }
      while (!temp.empty()) {
        stacks_copy[j].push(temp.top());
        temp.pop();
      }
    }

    for (auto stack : stacks_copy) {
      if (!stack.empty()) {
        out << stack.top();
      }
    }
  }
};

int main() {
  Today day;
  day.run();
}
