#ifndef __UTILS_H__
#define __UTILS_H__
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>
#include <fmt/core.h>

std::vector<std::string> split(const std::string& target, char c) {
  std::string temp;
  std::stringstream stringstream{ target };
  std::vector<std::string> result;

  while (std::getline(stringstream, temp, c)) {
    result.push_back(temp);
  }

  return result;
}

template <typename M>
M eigenRead(std::istream &in, char separator)
{
    std::string line;
    std::vector<typename M::Scalar> values;
    uint rows = 0;
    while (std::getline(in, line) && line.size()>0)
    {
        std::stringstream lineStream(line);
        std::string cell;
        while (std::getline(lineStream, cell, separator))
        {
            values.push_back(std::stod(cell));
        }
        ++rows;
    }
    return Eigen::Map<const M>(values.data(), rows, values.size() / rows);
}

class Day
{
public:
    void run()
    {
      fmt::print("../input{}.txt\n", day_number);
      std::ifstream input(fmt::format("../input{}.txt", day_number));
      parse(input);

      std::cout << "Part1: ";
      part1(std::cout);
      std::cout << std::endl;

      std::cout << "Part2: ";
      part2(std::cout);
      std::cout << std::endl;
    };
    Day(int number) : day_number(number) {};

protected:
    virtual void parse(std::istream &in) {}
    virtual void part1(std::ostream &out) {}
    virtual void part2(std::ostream &out) {}
    int day_number;
};

#include <utils.hpp>

#endif