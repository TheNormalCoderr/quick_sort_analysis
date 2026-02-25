#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;
using namespace std::chrono;

/* ---------------- HOARE + SENTINEL (First Pivot) ---------------- */
int partition_first(vector<int> &vec, int low, int high)
{
    int pivot = vec[low];
    int i = low;
    int j = high + 1;

    while (true)
    {
        do
        {
            i++;
        } while (vec[i] < pivot);
        do
        {
            j--;
        } while (vec[j] > pivot);

        if (i >= j)
            break;

        swap(vec[i], vec[j]);
    }

    swap(vec[low], vec[j]);
    return j;
}

void quickSort_first(vector<int> &vec, int low, int high)
{
    if (low < high)
    {
        int p = partition_first(vec, low, high);
        quickSort_first(vec, low, p - 1);
        quickSort_first(vec, p + 1, high);
    }
}

/* ---------------- RANDOM PIVOT VERSION ---------------- */
int partition_random(vector<int> &vec, int low, int high)
{
    int randomIndex = low + rand() % (high - low + 1);
    swap(vec[low], vec[randomIndex]); // bring random pivot to front

    int pivot = vec[low];
    int i = low;
    int j = high + 1;

    while (true)
    {
        do
        {
            i++;
        } while (vec[i] < pivot);
        do
        {
            j--;
        } while (vec[j] > pivot);

        if (i >= j)
            break;

        swap(vec[i], vec[j]);
    }

    swap(vec[low], vec[j]);
    return j;
}

void quickSort_random(vector<int> &vec, int low, int high)
{
    if (low < high)
    {
        int p = partition_random(vec, low, high);
        quickSort_random(vec, low, p - 1);
        quickSort_random(vec, p + 1, high);
    }
}

/* ---------------- MAIN ---------------- */
int main()
{
    const int START_SIZE = 5'000;
    const int MAX_SIZE = 1'20'000;
    const int STEP_SIZE = 2'000;
    const int FIRST_TRIALS = 1;
    const int RANDOM_TRIALS = 30;

    srand(time(nullptr));

    ofstream fout("quicksort_comparison.txt");
    fout << "ArraySize\tFirstPivot_Time_us\tRandomPivot_Time_us\n";

    for (int size = START_SIZE; size <= MAX_SIZE; size += STEP_SIZE)
    {
        double totalFirst = 0;
        double totalRandom = 0;

        for (int t = 0; t < FIRST_TRIALS; t++)
        {
            vector<int> arr1(size + 1);

            for (int i = 0; i < size; i++)
            {
                arr1[i] = rand() % size;
            }

            arr1[size] = INT_MAX;

            sort(arr1.begin(), arr1.end());
            auto start1 = high_resolution_clock::now();
            quickSort_first(arr1, 0, size - 1);
            auto end1 = high_resolution_clock::now();

            totalFirst += duration<double, micro>(end1 - start1).count();
        }

        for (int t = 0; t < RANDOM_TRIALS; t++)
        {
            vector<int> arr2(size + 1);

            for (int i = 0; i < size; i++)
            {
                arr2[i] = rand() % size;
            }

            arr2[size] = INT_MAX;

            sort(arr2.begin(), arr2.end());
            auto start2 = high_resolution_clock::now();
            quickSort_random(arr2, 0, size - 1);
            auto end2 = high_resolution_clock::now();

            totalRandom += duration<double, micro>(end2 - start2).count();
        }

        double avgFirst = totalFirst / FIRST_TRIALS;
        double avgRandom = totalRandom / RANDOM_TRIALS;

        fout << size << "\t" << avgFirst << "\t" << avgRandom << "\n";

        cout << "Size: " << size
             << " | First Pivot: " << avgFirst
             << " µs | Random Pivot: " << avgRandom << " µs\n";
    }

    fout.close();
    cout << "\nData saved to quicksort_comparison.txt\n";
    return 0;
}