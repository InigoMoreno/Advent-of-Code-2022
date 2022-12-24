#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;


template <typename T>
class Node {
 public:
  T val;
  Node<T>* nxt = 0;
  Node<T>* prv = 0;
  friend std::ostream& operator<<(std::ostream& os, const Node& d) {
    // if (d.prv) os << (*d.prv).val << "<";
    os << d.val;
    // if (d.nxt) os << ">" << (*d.nxt).val;
    return os;
  }
};

template <typename T>
class cyclicqueue {
 public:
  vector<Node<T>> v;

  cyclicqueue(vector<T> data) : v(data.size()) {
    for (size_t i = 0; i < v.size(); i++) {
      v[i].val = data[i];
      if (i > 0) {
        v[i - 1].nxt = &v[i];
        v[i].prv = &v[i - 1];
      }
      v[0].prv = &v[v.size() - 1];
      v[v.size() - 1].nxt = &v[0];
    }
  }

  void shift(size_t i, size_t times) {
    Node<T>* prv = v[i].prv;
    Node<T>* nxt = v[i].nxt;

    prv->nxt = nxt;
    nxt->prv = prv;

    while (times--) {
      prv = prv->nxt;
      nxt = nxt->nxt;
    }

    prv->nxt = &v[i];
    v[i].prv = prv;
    v[i].nxt = nxt;
    nxt->prv = &v[i];
  }

  friend std::ostream& operator<<(std::ostream& os, const cyclicqueue<T>& d) {
    os << "{";
    const Node<T>* it = &d.v[0];
    for (int i = 0; i < d.v.size(); i++) {
      os << *it << ", ";
      it = it->nxt;
    }
    os << "}";
    return os;
  }
};

class Today : public Day {
 public:
  Today() : Day(20) {}

 protected:
  vector<int> data;

  virtual void parse(istream& in) override {
    int a;
    while (in >> a) data.push_back(a);
  }

  template <typename T>
  T generic_part(T decription_key, int times) {
    vector<T> multiplied_data(data.size());
    for (int i = 0; i < data.size(); i++) multiplied_data[i] = decription_key * data[i];
    cyclicqueue<T> sequence(multiplied_data);
    while (times--) {
      for (size_t i = 0; i < data.size(); i++) {
        T times = mod(sequence.v[i].val, (T)sequence.v.size() - 1);
        sequence.shift(i, times);
      }
    }
    T sum = 0;
    auto it = &sequence.v[0];
    while (it->val != 0) it = it->nxt;
    for (int i = 1; i <= 3000; i++) {
      it = it->nxt;
      if (i % 1000 == 0) sum += it->val;
    }
    return sum;
  }

  virtual void part1(ostream& out) override { out << generic_part<int>(1, 1); }

  virtual void part2(ostream& out) override { out << generic_part<long int>(811589153, 10); }
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
