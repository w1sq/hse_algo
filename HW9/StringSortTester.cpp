#include <chrono>
#include <cstddef>
#include <functional>
#include <string>
#include <vector>

#include "sorters.cpp"

enum class SortType {
  QuickSort = 0,
  MergeSort = 1,
  StringQuickSort = 2,
  StringMergeSort = 3,
  MSDRadixSort = 4,
  MSDRadixSortWithCutoff = 5
};

struct SortResult {
  double time_ms;
  size_t cmp_count;
};

struct CmpCounter {
  size_t *counter;
  CmpCounter(size_t *c) : counter(c) {}
  bool operator()(const std::string &a, const std::string &b) {
    ++(*counter);
    return a < b;
  }
};

SortResult testSort(std::vector<std::string> arr, SortType type,
                    int cutoff = 0) {
  size_t cmp_count = 0;
  auto start = std::chrono::high_resolution_clock::now();
  switch (type) {
  case SortType::QuickSort:
    quicksort(arr, 0, arr.size() - 1, CmpCounter(&cmp_count));
    break;
  case SortType::MergeSort:
    mergesort(arr, 0, arr.size() - 1, CmpCounter(&cmp_count));
    break;
  case SortType::StringQuickSort:
    string_quicksort(arr, 0, arr.size() - 1, 0, cmp_count);
    break;
  case SortType::StringMergeSort:
    string_mergesort(arr, 0, arr.size() - 1, 0, cmp_count);
    break;
  case SortType::MSDRadixSort:
    msd_radix_sort(arr, 0, arr.size() - 1, 0, cmp_count, 0);
    break;
  case SortType::MSDRadixSortWithCutoff:
    msd_radix_sort(arr, 0, arr.size() - 1, 0, cmp_count, cutoff);
    break;
  }
  auto end = std::chrono::high_resolution_clock::now();
  double time_ms =
      std::chrono::duration<double, std::milli>(end - start).count();
  return {time_ms, cmp_count};
}