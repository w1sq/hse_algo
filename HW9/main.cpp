#include <iostream>
#include <string>
#include <vector>

#include "StringGenerator.cpp"
#include "StringSortTester.cpp"

int main(int argc, char *argv[]) {
  if (argc < 6) {
    std::cerr << "Usage: " << argv[0]
              << " <type> <n> <minLen> <maxLen> <sortType> [cutoff]\n";
    return 1;
  }
  std::string type = argv[1];
  size_t n = std::stoul(argv[2]);
  size_t minLen = std::stoul(argv[3]);
  size_t maxLen = std::stoul(argv[4]);
  int sortType = std::stoi(argv[5]);
  int cutoff = argc > 6 ? std::stoi(argv[6]) : 0;

  std::vector<std::string> arr;
  if (type == "random")
    arr = generateRandom(n, minLen, maxLen);
  else if (type == "reverse")
    arr = generateReverseSorted(n, minLen, maxLen);
  else if (type == "almost")
    arr = generateAlmostSorted(n, minLen, maxLen, n / 20);
  else {
    std::cerr << "Unknown type\n";
    return 1;
  }

  auto result = testSort(arr, static_cast<SortType>(sortType), cutoff);
  std::cout << result.time_ms << " " << result.cmp_count << std::endl;
  return 0;
}