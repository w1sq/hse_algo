#include <iostream>
#include <string>
#include <vector>

bool stringLess(const std::string &a, const std::string &b, int d,
                size_t &cmp_count) {
  for (size_t i = d; i < a.size() && i < b.size(); ++i) {
    ++cmp_count;
    if (a[i] < b[i])
      return true;
    if (a[i] > b[i])
      return false;
  }
  ++cmp_count;
  return a.size() < b.size();
}

void string_merge(std::vector<std::string> &arr, int left, int mid, int right,
                  int d, size_t &cmp_count) {
  int n1 = mid - left + 1, n2 = right - mid;
  std::vector<std::string> L(arr.begin() + left, arr.begin() + mid + 1);
  std::vector<std::string> R(arr.begin() + mid + 1, arr.begin() + right + 1);
  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (stringLess(L[i], R[j], d, cmp_count))
      arr[k++] = L[i++];
    else
      arr[k++] = R[j++];
  }
  while (i < n1)
    arr[k++] = L[i++];
  while (j < n2)
    arr[k++] = R[j++];
}

void string_mergesort(std::vector<std::string> &arr, int left, int right, int d,
                      size_t &cmp_count) {
  if (left >= right)
    return;
  int mid = left + (right - left) / 2;
  string_mergesort(arr, left, mid, d, cmp_count);
  string_mergesort(arr, mid + 1, right, d, cmp_count);
  string_merge(arr, left, mid, right, d, cmp_count);
}

int main() {
  size_t n;

  std::cin >> n;

  std::vector<std::string> arr(n);
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  size_t cmp_count = 0;
  string_mergesort(arr, 0, n - 1, 0, cmp_count);

  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << std::endl;
  }

  return 0;
}