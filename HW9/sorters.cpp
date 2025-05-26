#include <functional>
#include <map>
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

void merge(std::vector<std::string> &arr, int left, int mid, int right,
           std::function<bool(const std::string &, const std::string &)> comp) {
  int n1 = mid - left + 1, n2 = right - mid;
  std::vector<std::string> L(arr.begin() + left, arr.begin() + mid + 1);
  std::vector<std::string> R(arr.begin() + mid + 1, arr.begin() + right + 1);
  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (comp(L[i], R[j]))
      arr[k++] = L[i++];
    else
      arr[k++] = R[j++];
  }
  while (i < n1)
    arr[k++] = L[i++];
  while (j < n2)
    arr[k++] = R[j++];
}
void mergesort(
    std::vector<std::string> &arr, int left, int right,
    std::function<bool(const std::string &, const std::string &)> comp) {
  if (left >= right)
    return;
  int mid = left + (right - left) / 2;
  mergesort(arr, left, mid, comp);
  mergesort(arr, mid + 1, right, comp);
  merge(arr, left, mid, right, comp);
}

int charAt(const std::string &s, int d) {
  return d < (int)s.size() ? s[d] : -1;
}

void string_quicksort(std::vector<std::string> &arr, int left, int right, int d,
                      size_t &cmp_count) {
  if (right <= left)
    return;
  int lt = left, gt = right;
  int v = charAt(arr[(left + right) / 2], d);
  int i = left;
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

void quicksort(
    std::vector<std::string> &arr, int left, int right,
    std::function<bool(const std::string &, const std::string &)> comp) {
  if (left >= right)
    return;
  int i = left, j = right;
  std::string pivot = arr[(left + right) / 2];
  while (i <= j) {
    while (comp(arr[i], pivot))
      ++i;
    while (comp(pivot, arr[j]))
      --j;
    if (i <= j) {
      std::swap(arr[i], arr[j]);
      ++i;
      --j;
    }
  }
  if (left < j)
    quicksort(arr, left, j, comp);
  if (i < right)
    quicksort(arr, i, right, comp);
}

void msd_radix_sort(std::vector<std::string> &arr, int left, int right, int d,
                    size_t &cmp_count, int cutoff = 0) {
  if (right <= left)
    return;
  if (cutoff > 0 && right - left + 1 <= cutoff) {
    string_quicksort(arr, left, right, d, cmp_count);
    return;
  }
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
