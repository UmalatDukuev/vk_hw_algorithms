/* Напишите программу, которая использует кучу для слияния K отсортированных
   массивов суммарной длиной N.

 Требования:
 - Время работы O(N * logK)
 - Куча должна быть реализована в виде шаблонного класса.
 - Решение должно поддерживать передачу функции сравнения снаружи.
 - Куча должна быть динамической.
*/


#include <cmath>
#include <iostream>

struct Iter {
    int k;
    size_t IndOfArr;
    Iter() = default;
    Iter(const int& k, const size_t& ind) : k(k), IndOfArr(ind) {}
    ~Iter() = default;
};

bool operator<(const Iter& l, const Iter& r) {
    return l.k < r.k;
}

template <typename T>
class IsLessDefault {
public:
    bool operator()(const T& l, const T& r) { return l < r; }
};

template <typename K, typename V>
struct Pair {
    K first;
    V second;

    Pair() = default;
    Pair(K k, V value) : first(k), second(value) {}
    ~Pair() = default;
};

template <typename T, typename IsLess>
class Heap {
private:
    void SiftDown(const size_t& index);
    void SiftUp(const size_t& index);
public:
    Heap(const IsLess& less = IsLessDefault<T>())
        : size(0), capacity(0), array(nullptr), isLess(less) {};
    Heap(const size_t& SizeOfHeap, const size_t& CapacityOfHeap, const T* heap,
        const IsLess& less = IsLessDefault<T>()) = delete;
    ~Heap() { delete[] array; }
    void add(const T& iter);
    T extract();

protected:
    size_t size;
    size_t capacity;
    T* array;
    IsLess isLess;
};

template <typename T, typename IsLess>
void Heap<T, IsLess>::SiftDown(const size_t& ind) {
    size_t left = 2 * ind + 1;
    size_t right = 2 * ind + 2;
    size_t largest = ind;
    while (
        largest < size / 2 &&
        (isLess(array[left], array[largest]) ||
            (right < size && isLess(array[right], array[largest])))) {
        if (right >= size || isLess(array[left], array[right])) {
            std::swap(array[left], array[largest]);
            largest = left;
        }
        else {
            std::swap(array[right], array[largest]);
            largest = right;
        }

        left = 2 * largest + 1;
        right = 2 * largest + 2;
    }
}

template <typename T, typename IsLess>
void Heap<T, IsLess>::SiftUp(const size_t& ind) {
    size_t current = ind;
    size_t parent = std::floor((current - 1) / 2);

    while (current != 0 && isLess(array[current], array[parent])) {
        std::swap(array[parent], array[current]);
        current = parent;
        parent = std::floor((current - 1) / 2);
    }
}

template <typename T, typename IsLess>
void Heap<T, IsLess>::add(const T& iter) {
    if (capacity == 0) {
        capacity = 1;
        array = new T[capacity];
    }
    else if (size == capacity) {
        capacity *= 2;
        T* newArray = new T[capacity];
        std::copy(array, array + size, newArray);
        delete[] array;
        array = newArray;
    }
    array[size] = iter;
    ++size;

    SiftUp(size - 1);
}

template <typename T, typename IsLess>
T Heap<T, IsLess>::extract() {
    std::swap(array[0], array[size - 1]);
    T result = array[size - 1];
    --size;
    SiftDown(0);
    return result;
}

Pair<int*, size_t> merge(const size_t k, const size_t* SizeOfArr, int** MainArr) {
    size_t size = 0;
    for (size_t i = 0; i < k; ++i) {
        size += SizeOfArr[i];
    }
    int* result = new int[size];

    Heap<Iter, IsLessDefault<Iter>> heap;
    for (size_t i = 0; i < k; ++i) {
        if (SizeOfArr[i] > 0) {
            heap.add(Iter(MainArr[i][0], i));
        }
    }

    auto* counter = new size_t[k];
    for (size_t i = 0; i < k; ++i) {
        counter[i] = 1;
    }

    for (size_t i = 0; i < size; ++i) {
        auto minIter = heap.extract();
        int iter = minIter.k;
        size_t ind = minIter.IndOfArr;
        result[i] = iter;
        if (counter[ind] < SizeOfArr[ind]) {
            heap.add(Iter(MainArr[ind][counter[ind]], ind));
            ++counter[ind];
        }
    }
    delete[] counter;
    return { result, size };
}

int main() {
   
    int NumOfArrs = 0;
    std::cin >> NumOfArrs;
    auto* SizeOfArrs = new size_t[NumOfArrs];
    int** MainArr = new int* [NumOfArrs];
    for (int i = 0; i < NumOfArrs; ++i) {
        std::cin >> SizeOfArrs[i];
        MainArr[i] = new int[SizeOfArrs[i]];
        for (int j = 0; j < SizeOfArrs[i]; ++j) {
            std::cin >> MainArr[i][j];
        }
    }
    auto SortedArr = merge(NumOfArrs, SizeOfArrs, MainArr);

    for (int i = 0; i < SortedArr.second; ++i) {
        std::cout << SortedArr.first[i] << " ";
    }

    for (int i = 0; i < NumOfArrs; ++i) {
        delete[] MainArr[i];
    }
    delete[] MainArr;
    delete[] SizeOfArrs;
    delete[] SortedArr.first;
    return 0;
}
