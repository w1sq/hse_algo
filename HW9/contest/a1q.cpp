#include <iostream>
#include <string>
#include <vector>

int charAt(const std::string &s, int d) {
  return d < (int)s.size() ? s[d] : -1;
}

void string_quicksort(std::vector<std::string> &arr, int left, int right, int d,
                      size_t &cmp_count) {
  if (right <= left)
    return;
  int lt = left, gt = right;
  int v = charAt(arr[left], d);
  int i = left + 1;
  while (i <= gt) {
    int t = charAt(arr[i], d);
    ++cmp_count;
    if (t < v)
      std::swap(arr[lt++], arr[i++]);
    else if (t > v)
      std::swap(arr[i], arr[gt--]);
    else
      i++;
  }
  string_quicksort(arr, left, lt - 1, d, cmp_count);
  if (v >= 0)
    string_quicksort(arr, lt, gt, d + 1, cmp_count);
  string_quicksort(arr, gt + 1, right, d, cmp_count);
}

int main() {
  size_t n;
  std::cin >> n;

  std::vector<std::string> arr(n);
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  size_t cmp_count = 0;
  string_quicksort(arr, 0, n - 1, 0, cmp_count);

  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << std::endl;
  }

  return 0;
}