#include <chrono>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random> 
#include <fstream>


class ArrayGenerator {
public:
    // Генерация случайного массива
    static std::vector<int> generateRandomArray(int size, int range = 6000) {
        std::vector<int> arr(size);
        // Используем std::mt19937 для генерации случайных чисел
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, range);

        for (int i = 0; i < size; ++i) {
            arr[i] = dist(gen);
        }
        return arr;
    }

    // Генерация отсортированного массива по убыванию
    static std::vector<int> generateSortedArray(int size, int range = 6000) {
        std::vector<int> arr = generateRandomArray(size, range);
        std::sort(arr.begin(), arr.end(), std::greater<int>());  // Сортируем по убыванию
        return arr;
    }

    // Генерация почти отсортированного массива по убыванию
    static std::vector<int> generateAlmostSortedArray(int size, int range = 6000, int num_swaps = 10) {
        std::vector<int> arr = generateSortedArray(size, range);  // Генерируем отсортированный по убыванию массив
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, size - 1);

        // Создаём случайные перестановки в массиве
        for (int i = 0; i < num_swaps; ++i) {
            int idx1 = dist(gen);
            int idx2 = dist(gen);
            std::swap(arr[idx1], arr[idx2]);
        }

        return arr;
    }

    // Генерация подмассива заданного размера
    static std::vector<int> generateSubArray(const std::vector<int>& arr, int size) {
        return std::vector<int>(arr.begin(), arr.begin() + size);
    }
};




// void merge(std::vector<int>& arr, int left, int mid, int right) {
//     int n1 = mid - left + 1;
//     int n2 = right - mid;
//     std::vector<int> L(n1), R(n2);
    
//     for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
//     for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];
    
//     int i = 0, j = 0, k = left;
//     while (i < n1 && j < n2) {
//         if (L[i] <= R[j]) {
//             arr[k++] = L[i++];
//         } else {
//             arr[k++] = R[j++];
//         }
//     }

//     while (i < n1) arr[k++] = L[i++];
//     while (j < n2) arr[k++] = R[j++];
// }

// void mergeSort(std::vector<int>& arr, int left, int right) {
//     if (left < right) {
//         int mid = left + (right - left) / 2;
//         mergeSort(arr, left, mid);
//         mergeSort(arr, mid + 1, right);
//         merge(arr, left, mid, right);
//     }
// }


// void insertionSort(std::vector<int>& arr, int left, int right) {
//     for (int i = left + 1; i <= right; ++i) {
//         int key = arr[i];
//         int j = i - 1;
//         while (j >= left && arr[j] > key) {
//             arr[j + 1] = arr[j];
//             --j;
//         }
//         arr[j + 1] = key;
//     }
// }


// void hybridMergeSort(std::vector<int>& arr, int left, int right, int threshold) {
//     if (right - left + 1 <= threshold) {
//         insertionSort(arr, left, right);
//     } else {
//         if (left < right) {
//             int mid = left + (right - left) / 2;
//             hybridMergeSort(arr, left, mid, threshold);
//             hybridMergeSort(arr, mid + 1, right, threshold);
//             merge(arr, left, mid, right);
//         }
//     }
// }


class SortTester {
public:
    // Метод для замера времени работы Merge Sort
    long long measureMergeSortTime(std::vector<int>& arr, const std::string& dataType, int size) {
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(arr, 0, arr.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long time = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        logTime("mergeSort_" + dataType + ".txt", size, time);
        return time;
    }

    // Метод для замера времени работы Hybrid Merge Sort
    static long long measureHybridSortTime(std::vector<int>& arr, int threshold, const std::string& dataType, int size) {
        auto start = std::chrono::high_resolution_clock::now();
        hybridMergeSort(arr, 0, arr.size() - 1, threshold);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long time = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        logTime("hybridSort_" + dataType + "_threshold" + std::to_string(threshold) + ".txt", size, time);
        return time;
    }

    static void merge(std::vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        std::vector<int> L(n1), R(n2);
        
        for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
        for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];
        
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        }

        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }

    static void mergeSort(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    static void insertionSort(std::vector<int>& arr, int left, int right) {
        for (int i = left + 1; i <= right; ++i) {
            int key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }

    static void hybridMergeSort(std::vector<int>& arr, int left, int right, int threshold) {
        if (right - left + 1 <= threshold) {
            insertionSort(arr, left, right);
        } else {
            if (left < right) {
                int mid = left + (right - left) / 2;
                hybridMergeSort(arr, left, mid, threshold);
                hybridMergeSort(arr, mid + 1, right, threshold);
                merge(arr, left, mid, right);
            }
        }
    }

    // Функция для записи времени в файл
    static void logTime(const std::string& filename, int size, long long time) {
        std::ofstream outFile(filename, std::ios::app); // Открываем файл для дозаписи
        if (outFile.is_open()) {
            outFile << size << "\t" << time << "\n";  // Записываем размер и время
            outFile.close();
        } else {
            std::cerr << "Error opening file " << filename << "\n";
        }
    }
};


int main() {
    srand(time(0));  // Инициализация генератора случайных чисел

    // Генерация массива максимального размера (10000)
    std::vector<int> fullRandomArray = ArrayGenerator::generateRandomArray(10000);
    std::vector<int> fullSortedArray = ArrayGenerator::generateSortedArray(10000);
    std::vector<int> fullAlmostSortedArray = ArrayGenerator::generateAlmostSortedArray(10000);

    // Инициализация тестера
    SortTester tester;

    // Запуск экспериментов для разных размеров
    for (int size = 500; size <= 10000; size += 100) {
        std::vector<int> randomArray = ArrayGenerator::generateSubArray(fullRandomArray, size);
        std::vector<int> sortedArray = ArrayGenerator::generateSubArray(fullSortedArray, size);
        std::vector<int> almostSortedArray = ArrayGenerator::generateSubArray(fullAlmostSortedArray, size);

        // Измеряем время для Merge Sort
        tester.measureMergeSortTime(randomArray, "random", size);
        tester.measureMergeSortTime(sortedArray, "sorted", size);
        tester.measureMergeSortTime(almostSortedArray, "almost_sorted", size);

        // Измеряем время для Hybrid Merge Sort
		int threshold = 30;
        tester.measureHybridSortTime(randomArray, threshold, "random", size);
        tester.measureHybridSortTime(sortedArray, threshold, "sorted", size);
        tester.measureHybridSortTime(almostSortedArray, threshold, "almost_sorted", size);
        
    }

    return 0;
}
