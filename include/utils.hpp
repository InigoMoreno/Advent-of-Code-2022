#ifndef __UTILS_H__
#define __UTILS_H__
#include <absl/algorithm/container.h>
#include <absl/strings/str_split.h>
#include <fmt/core.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

struct pos {
  int x;
  int y;
  bool operator<(const pos &other) const {
    return std::tie(x, y) < std::tie(other.x, other.y);
  }
  pos operator+(const pos &other) const {
    return pos({x + other.x, y + other.y});
  }
  pos operator-(const pos &other) const {
    return pos({x - other.x, y - other.y});
  }
  friend std::ostream &operator<<(std::ostream &os, const pos &d) {
    return os << '(' << d.x << ',' << d.y << ')';
  }
  bool operator==(const pos &other) const {
    return std::tie(x, y) == std::tie(other.x, other.y);
  }
  int manhattan_norm() const {
    return abs(x)+abs(y);
  }
};

std::vector<std::string> split(const std::string &target, char c) {
  std::string temp;
  std::stringstream stringstream{target};
  std::vector<std::string> result;

  while (std::getline(stringstream, temp, c)) {
    result.push_back(temp);
  }

  return result;
}

std::string streamToString(std::istream &t) {
  t.seekg(0, std::ios::end);
  size_t size = t.tellg();
  std::string buffer(size, ' ');
  t.seekg(0);
  t.read(&buffer[0], size);
  return buffer;
}

template <typename M>
M eigenRead(std::istream &in, char separator) {
  std::string line;
  std::vector<typename M::Scalar> values;
  uint rows = 0;
  while (std::getline(in, line) && line.size() > 0) {
    std::stringstream lineStream(line);
    std::string cell;
    while (std::getline(lineStream, cell, separator)) {
      values.push_back(std::stod(cell));
    }
    ++rows;
  }
  return Eigen::Map<const M>(values.data(), rows, values.size() / rows);
}

class Day {
 public:
  std::string input_path = "../input/input{}.txt";

  void run() {
    std::ifstream input(fmt::format(input_path, day_number));
    parse(input);

    std::cout << "Part1: ";
    part1(std::cout);
    std::cout << std::endl;

    std::cout << "Part2: ";
    part2(std::cout);
    std::cout << std::endl;
  };
  Day(int number) : day_number(number){};

 protected:
  virtual void parse(std::istream &in) {}
  virtual void part1(std::ostream &out) {}
  virtual void part2(std::ostream &out) {}
  int day_number;
};

#include <utils.hpp>

#endif