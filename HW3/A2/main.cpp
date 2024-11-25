#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <numeric>

class ArrayGenerator
{
private:
    std::mt19937 rng;
    const int MAX_SIZE = 10000;
    const int MIN_VALUE = 0;
    const int MAX_VALUE = 6000;

    std::vector<int> baseArray;

public:
    ArrayGenerator() : rng(std::random_device{}())
    {
        baseArray.resize(MAX_SIZE);
    }

    // Генерация случайного массива
    std::vector<int> generateRandom(int size)
    {
        std::uniform_int_distribution<int> dist(MIN_VALUE, MAX_VALUE);
        std::vector<int> result(size);
        for (int i = 0; i < size; i++)
        {
            result[i] = dist(rng);
        }
        return result;
    }

    // Генерация массива, отсортированного по убыванию
    std::vector<int> generateReverseSorted(int size)
    {
        std::vector<int> result(size);
        for (int i = 0; i < size; i++)
        {
            result[i] = size - i;
        }
        return result;
    }

    // Генерация почти отсортированного массива
    std::vector<int> generateNearlySorted(int size)
    {
        std::vector<int> result(size);
        for (int i = 0; i < size; i++)
        {
            result[i] = i;
        }

        // Меняем местами несколько пар элементов (например, 5% от размера массива)
        int swaps = size * 0.05;
        for (int i = 0; i < swaps; i++)
        {
            int idx1 = std::uniform_int_distribution<int>(0, size - 1)(rng);
            int idx2 = std::uniform_int_distribution<int>(0, size - 1)(rng);
            std::swap(result[idx1], result[idx2]);
        }
        return result;
    }
};

class SortTester
{
private:
    // Стандартный Merge Sort
    void merge(std::vector<int> &arr, int left, int mid, int right)
    {
        std::vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right)
        {
            if (arr[i] <= arr[j])
            {
                temp[k++] = arr[i++];
            }
            else
            {
                temp[k++] = arr[j++];
            }
        }

        while (i <= mid)
            temp[k++] = arr[i++];
        while (j <= right)
            temp[k++] = arr[j++];

        for (i = 0; i < k; i++)
        {
            arr[left + i] = temp[i];
        }
    }

    void insertionSort(std::vector<int> &arr, int left, int right)
    {
        for (int i = left + 1; i <= right; i++)
        {
            int key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    long long performMultipleMeasurements(std::vector<int> &arr, bool useHybrid, int threshold, int iterations = 5)
    {
        std::vector<long long> times;
        times.reserve(iterations);

        for (int i = 0; i < iterations; i++)
        {
            times.push_back(measureSortingTime(arr, useHybrid, threshold));
        }

        if (iterations > 2)
        {
            times.erase(std::max_element(times.begin(), times.end()));
            times.erase(std::min_element(times.begin(), times.end()));
        }

        return std::accumulate(times.begin(), times.end(), 0LL) / times.size();
    }

public:
    void mergeSort(std::vector<int> &arr, int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    void hybridMergeSort(std::vector<int> &arr, int left, int right, int threshold)
    {
        if (right - left <= threshold)
        {
            insertionSort(arr, left, right);
            return;
        }

        int mid = left + (right - left) / 2;
        hybridMergeSort(arr, left, mid, threshold);
        hybridMergeSort(arr, mid + 1, right, threshold);
        merge(arr, left, mid, right);
    }

    long long measureSortingTime(std::vector<int> &arr, bool useHybrid = false, int threshold = 10)
    {
        std::vector<int> testArr = arr;
        auto start = std::chrono::high_resolution_clock::now();

        if (useHybrid)
        {
            hybridMergeSort(testArr, 0, testArr.size() - 1, threshold);
        }
        else
        {
            mergeSort(testArr, 0, testArr.size() - 1);
        }

        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    void runFullTestSuite(const std::string &outputPath)
    {
        ArrayGenerator generator;
        std::ofstream outFile(outputPath);

        outFile << "size,array_type,algorithm,threshold,time\n";

        std::vector<int> thresholds = {5, 10, 20, 30, 50};

        for (int size = 500; size <= 10000; size += 100)
        {
            auto randomArray = generator.generateRandom(size);
            auto reversedArray = generator.generateReverseSorted(size);
            auto nearlySortedArray = generator.generateNearlySorted(size);

            outFile << size << ",random,standard,0,"
                    << performMultipleMeasurements(randomArray, false, 0) << "\n";
            outFile << size << ",reversed,standard,0,"
                    << performMultipleMeasurements(reversedArray, false, 0) << "\n";
            outFile << size << ",nearly_sorted,standard,0,"
                    << performMultipleMeasurements(nearlySortedArray, false, 0) << "\n";

            for (int threshold : thresholds)
            {
                outFile << size << ",random,hybrid," << threshold << ","
                        << performMultipleMeasurements(randomArray, true, threshold) << "\n";
                outFile << size << ",reversed,hybrid," << threshold << ","
                        << performMultipleMeasurements(reversedArray, true, threshold) << "\n";
                outFile << size << ",nearly_sorted,hybrid," << threshold << ","
                        << performMultipleMeasurements(nearlySortedArray, true, threshold) << "\n";
            }

            outFile.flush();
            std::cout << "Completed tests for size " << size << std::endl;
        }

        outFile.close();
    }
};

int main()
{
    SortTester tester;
    tester.runFullTestSuite("sorting_results.csv");
    return 0;
}