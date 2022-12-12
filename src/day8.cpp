#include <utils.hpp>

using namespace std;
using namespace Eigen;
using namespace absl;

class Today : public Day {
 public:
  Today() : Day(8) {}

 protected:
  vector<vector<uint>> field;
  size_t N;

  virtual void parse(istream& in) override {
    string line;
    while (getline(in, line)) {
      if (line.empty()) continue;
      vector<uint> row(line.size());
      for (int i = 0; i < line.size(); i++) {
        row[i] = line[i] - '0';
      }
      field.push_back(row);
    }
    N = field.size();
  }

  virtual void part1(ostream& out) override {
    vector<vector<bool>> visible(N, vector<bool>(N, false));
    // left to right
    for (int i = 1; i < N - 1; i++) {
      uint max_height = field[i][0];
      for (int j = 1; j < N - 1; j++) {
        if (field[i][j] > max_height) {
          max_height = field[i][j];
          visible[i][j] = true;
        }
      }
    }

    // right to left
    for (int i = 1; i < N - 1; i++) {
      uint max_height = field[i][N - 1];
      for (int j = N - 2; j >= 1; j--) {
        if (field[i][j] > max_height) {
          max_height = field[i][j];
          visible[i][j] = true;
        }
      }
    }

    // top to bottom
    for (int j = 1; j < N - 1; j++) {
      uint max_height = field[0][j];
      for (int i = 1; i < N - 1; i++) {
        if (field[i][j] > max_height) {
          max_height = field[i][j];
          visible[i][j] = true;
        }
      }
    }

    // bottom to top
    for (int j = 1; j < N - 1; j++) {
      uint max_height = field[N - 1][j];
      for (int i = N - 2; i >= 1; i--) {
        if (field[i][j] > max_height) {
          max_height = field[i][j];
          visible[i][j] = true;
        }
      }
    }

    int visible_count = N * 4 - 4;
    for (int i = 1; i < N - 1; i++) {
      for (int j = 1; j < N - 1; j++) {
        visible_count += visible[i][j];
      }
    }
    out << visible_count;
  }

  virtual void part2(ostream& out) override {
    int max_score=1;
    vector<vector<uint>> score(N, vector<uint>(N, 1));
    for (int i = 1; i < N - 1; i++) {
      for (int j = 1; j < N - 1; j++) {
        int k;
        // looking up
        k = i - 1;
        while (k >= 0 and field[k][j] < field[i][j]) k--;
        if (k < 0) k++;
        score[i][j] *= i - k;
        // looking left
        k = j - 1;
        while (k >= 0 and field[i][k] < field[i][j]) k--;
        if (k < 0) k++;
        score[i][j] *= j - k;
        // looking right
        k = j + 1;
        while (k < N and field[i][k] < field[i][j]) k++;
        if (k >= N) k--;
        score[i][j] *= k - j;
        // looking down
        k = i + 1;
        while (k < N and field[k][j] < field[i][j]) k++;
        if (k >= N) k--;
        score[i][j] *= k - i;

        if (score[i][j]>max_score){
          max_score = score[i][j];
        }
      }
    }
    out << max_score;
  }
};

int main() {
  Today day;
  // day.input_path = "../input/input{}-example.txt";
  day.run();
}
