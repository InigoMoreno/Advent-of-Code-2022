#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

class ListOrNum {
 public:
  bool is_list;
  int num;
  vector<ListOrNum> list;

  // For parsing
  friend istream& operator>>(istream& in, ListOrNum& D) {
    D.is_list = in.peek() == '[';
    if (D.is_list) {
      ListOrNum child;
      char c;
      D.list = vector<ListOrNum>();
      in >> c;                 // skip [
      if (in.peek() == ']') {  // special case for []
        in >> c >> std::ws;    // skip ]
        return in;
      }
      while (c != ']') {
        in >> child;
        D.list.push_back(child);
        in >> c >> std::ws;
      };

    } else
      in >> D.num >> std::ws;

    return in;
  }

  // For printing
  friend ostream& operator<<(ostream& output, const ListOrNum& D) {
    if (D.is_list)
      output << fmt::format("{}", D.list);
    else
      output << D.num;
    return output;
  }

  ListOrNum asList() const {
    if (is_list) return *this;
    ListOrNum res;
    res.list = {*this};
    res.is_list = true;
    return res;
  }

  // -1 lower 0 equal 1 higher
  static short int compare(const ListOrNum& a, const ListOrNum& b) {
    // fmt::print("Compare {} vs {}\n", a, b);
    if (!a.is_list and !b.is_list) {
      if (a.num < b.num) return -1;
      if (a.num > b.num) return 1;
      return 0;
    }

    if (a.is_list and b.is_list) {
      auto ita = a.list.begin();
      auto itb = b.list.begin();
      while (true) {
        if (ita == a.list.end() and itb == b.list.end()) return 0;
        if (ita == a.list.end()) return -1;
        if (itb == b.list.end()) return 1;
        auto subres = compare(*ita, *itb);
        if (subres != 0) return subres;
        ita++;
        itb++;
      }
    }
    return compare(a.asList(), b.asList());
  }

  bool operator<(const ListOrNum& other) const { return compare(*this, other) == -1; }
};

class Today : public Day {
 public:
  Today() : Day(13) {}

 protected:
  vector<pair<ListOrNum, ListOrNum>> comparisons;

  virtual void parse(istream& in) override {
    ListOrNum a, b;
    while (in >> a >> b) comparisons.push_back({a, b});
  }

  virtual void part1(ostream& out) override {
    int sum = 0;
    for (int i = 0; i < comparisons.size(); i++)
      if (comparisons[i].first < comparisons[i].second) sum += i + 1;
    out << sum;
  }

  virtual void part2(ostream& out) override {}
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
