#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

class Solver {
 private:
  const std::string kAlphabet = "abcdefghijklmnopqrstuvwxyz";
  size_t numOfTests = 0;

  std::string SolveTest() {
    bool ans = false;
    std::set<std::string> strExists;

    size_t strNum = 0;
    std::cin >> strNum;

    std::string curStr = "";
    for (size_t i = 0; i < strNum; i++) {
      std::cin >> curStr;
      if (ans) {
        continue;
      }
      strExists.insert(curStr);
      std::reverse(curStr.begin(), curStr.end());
      if (curStr.size() == 1 || strExists.count(curStr)) {
        ans = true;
      } else if (curStr.size() == 2) {
        for (auto c : kAlphabet) {
          if (strExists.count(curStr + c)) {
            ans = true;
            break;
          }
        }
      } else if (curStr.size() == 3 && strExists.count(curStr.substr(0, 2))) {
        ans = true;
      }
    }

    if (ans) {
      return "YES";
    }
    return "NO";
  }

 public:
  Solver(size_t num) : numOfTests(num) {}

  std::vector<std::string> solve() {
    std::vector<std::string> result;
    for (size_t i = 0; i < numOfTests; i++) {
      result.push_back(SolveTest());
    }
    return result;
  }
};

int main() {
  size_t numOfTests = 0;
  std::cin >> numOfTests;
  Solver slv(numOfTests);
  std::vector<std::string> result = slv.solve();
  for (auto res : result) {
    std::cout << res << "\n";
  }
}