#include <iostream>
#include <map>
#include <string>
#include <vector>

void string_quicksort(std::vector<std::string> &arr, int left, int right, int d,
                      size_t &cmp_count);

int charAt(const std::string &s, int d) {
  return d < (int)s.size() ? s[d] : -1;
}

void msd_radix_sort(std::vector<std::string> &arr, int left, int right, int d,
                    size_t &cmp_count, int cutoff = 0) {
  if (right <= left)
    return;
  //   if (cutoff > 0 && right - left + 1 <= cutoff) {
  //     string_quicksort(arr, left, right, d, cmp_count);
  //     return;
  //   }
  std::map<int, std::vector<std::string>> buckets;
  for (int i = left; i <= right; ++i)
    buckets[charAt(arr[i], d)].push_back(arr[i]);
  int idx = left;
  for (auto &[key, bucket] : buckets) {
    for (auto &s : bucket)
      arr[idx++] = s;
  }
  idx = left;
  for (auto &[key, bucket] : buckets) {
    int sz = bucket.size();
    if (sz > 1)
      msd_radix_sort(arr, idx, idx + sz - 1, d + 1, cmp_count, cutoff);
    idx += sz;
  }
}

int main() {
  size_t n;
  std::cin >> n;

  std::vector<std::string> arr(n);
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  size_t cmp_count = 0;
  msd_radix_sort(arr, 0, n - 1, 0, cmp_count, 0);

  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << std::endl;
  }

  return 0;
}