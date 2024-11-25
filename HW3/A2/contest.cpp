#include <iostream>
#include <vector>

class HybridSorter
{
private:
    const int THRESHOLD = 15;

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

    void hybridMergeSort(std::vector<int> &arr, int left, int right)
    {
        if (right - left <= THRESHOLD)
        {
            insertionSort(arr, left, right);
            return;
        }

        int mid = left + (right - left) / 2;
        hybridMergeSort(arr, left, mid);
        hybridMergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }

public:
    void sort(std::vector<int> &arr)
    {
        if (arr.size() <= 1)
            return;
        hybridMergeSort(arr, 0, arr.size() - 1);
    }
};

int main()
{
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    HybridSorter sorter;
    sorter.sort(arr);

    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i];
        if (i < n - 1)
            std::cout << " ";
    }
    std::cout << "\n";

    return 0;
}