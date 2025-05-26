#include <vector>
#include <string>
#include <random>
#include <algorithm>

static const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$:;^&*()-";

std::string randomString(size_t minLen, size_t maxLen, std::mt19937& rng) {
    std::uniform_int_distribution<size_t> lenDist(minLen, maxLen);
    std::uniform_int_distribution<size_t> charDist(0, chars.size() - 1);
    size_t len = lenDist(rng);
    std::string s;
    for (size_t i = 0; i < len; ++i)
        s += chars[charDist(rng)];
    return s;
}

std::vector<std::string> generateRandom(size_t count, size_t minLen, size_t maxLen) {
    std::vector<std::string> arr;
    std::mt19937 rng(std::random_device{}());
    for (size_t i = 0; i < count; ++i)
        arr.push_back(randomString(minLen, maxLen, rng));
    return arr;
}

std::vector<std::string> generateReverseSorted(size_t count, size_t minLen, size_t maxLen) {
    auto arr = generateRandom(count, minLen, maxLen);
    std::sort(arr.begin(), arr.end());
    std::reverse(arr.begin(), arr.end());
    return arr;
}

std::vector<std::string> generateAlmostSorted(size_t count, size_t minLen, size_t maxLen, size_t swaps) {
    auto arr = generateRandom(count, minLen, maxLen);
    std::sort(arr.begin(), arr.end());
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, count - 1);
    for (size_t i = 0; i < swaps; ++i) {
        size_t a = dist(rng), b = dist(rng);
        std::swap(arr[a], arr[b]);
    }
    return arr;
}