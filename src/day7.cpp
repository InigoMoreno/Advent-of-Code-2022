#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

class FileOrDir : public std::enable_shared_from_this<FileOrDir> {
 private:
  size_t _size = 0;

 public:
  bool is_dir;
  string name;
  vector<shared_ptr<FileOrDir>> children;
  shared_ptr<FileOrDir> parent;

  FileOrDir() : is_dir(true), name("/") {}

  FileOrDir(string dir_or_size, string name) : name(name) {
    is_dir = dir_or_size == "dir";
    if (!is_dir) _size = stoul(dir_or_size);
  }

  size_t size() {
    if (is_dir and _size == 0)
      for (auto child : children) _size += child->size();
    return _size;
  }

  void populate(istream& in) {
    while (true) {
      in >> std::ws;
      if (in.eof()) break;
      if (in.peek() == '$') break;
      string a, b;
      in >> a >> b;
      shared_ptr<FileOrDir> child = make_shared<FileOrDir>(a, b);
      child->parent = shared_from_this();
      children.push_back(child);
    }
  }

  shared_ptr<FileOrDir> cd(string where) {
    if (where == "..") return parent;
    for (auto child : children)
      if (child->is_dir and where == child->name) return child;
  }

  size_t sum_sizes_at_most_N(size_t N) {
    size_t sum = is_dir and size() <= N ? size() : 0;
    for (auto child : children) sum += child->sum_sizes_at_most_N(N);
    return sum;
  }

  size_t min_size_at_least_N(size_t N) {
    size_t res = is_dir and size() >= N ? size() : -1;
    for (auto child : children) {
      size_t subres = child->min_size_at_least_N(N);
      if (subres < res) res = subres;
    }
    return res;
  }
};

class Today : public Day {
 public:
  Today() : Day(7) {}

 protected:
  shared_ptr<FileOrDir> root;

  virtual void parse(istream& in) override {
    string ignore;
    in >> ignore >> ignore >> ignore;
    root = make_shared<FileOrDir>();
    shared_ptr<FileOrDir> cwd = root;
    while (in >> ignore) {
      string command;
      in >> command;
      if (command == "ls") {
        cwd->populate(in);
      } else if (command == "cd") {
        string where;
        in >> where;
        cwd = cwd->cd(where);
      }
    }
  }

  virtual void part1(ostream& out) override {
    out << root->sum_sizes_at_most_N(100000);
  }

  virtual void part2(ostream& out) override {
    out << root->min_size_at_least_N(root->size() - size_t(40000000));
  }
};

int main() {
  Today day;
  day.run();
}