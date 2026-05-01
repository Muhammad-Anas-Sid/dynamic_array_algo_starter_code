#include "da_algo.h"

DynamicArray::DynamicArray(const int initial_capacity, const int capacity_increment) {
    this->capacity = initial_capacity;
    this->array = new int[this->capacity];
    this->array_size = 0;
}
DynamicArray::DynamicArray(const int initial_capacity) {
    this->capacity = initial_capacity;
    this->array = new int[this->capacity];
    this->array_size = 0;
}
DynamicArray::DynamicArray() {
    this->capacity = 10;
    this->array = new int[this->capacity];
    this->array_size = 0;
}
DynamicArray::DynamicArray(const DynamicArray& other) {
    this->capacity = other.capacity;
    this->array_size = other.array_size;
    this->array = new int[this->capacity];
    for (int i = 0; i < this->array_size; i++) {
        this->array[i] = other.array[i];
    }
}
DynamicArray& DynamicArray::operator = (const DynamicArray& other) {
    if (this != &other) {
        delete[] this->array;
        this->capacity = other.capacity;
        this->array_size = other.array_size;
        this->array = new int[this->capacity];
        for (int i = 0; i < this->array_size; i++) {
            this->array[i] = other.array[i];
        }
    }
    return *this;
}
DynamicArray::~DynamicArray() {
    delete[] this->array;
}

bool DynamicArray::insert(const int value) {
    if (this->array_size >= this->capacity) {
        int new_capacity = this->capacity * 2;
        int* new_array = new int[new_capacity];
        for (int i = 0; i < this->array_size; i++) {
            new_array[i] = this->array[i];
        }
        delete[] this->array;
        this->array = new_array;
        this->capacity = new_capacity;
    }
    this->array[this->array_size++] = value;
    return true;
 }
bool DynamicArray::insert(const int index, const int value) {
    if (index < 0 || index > this->array_size) {
        return false;
    }
    if (this->array_size >= this->capacity) {
        int new_capacity = this->capacity * 2;
        int* new_array = new int[new_capacity];
        for (int i = 0; i < this->array_size; i++) {
            new_array[i] = this->array[i];
        }
        delete[] this->array;
        this->array = new_array;
        this->capacity = new_capacity;
    }
    for (int i = this->array_size; i > index; i--) {
        this->array[i] = this->array[i - 1];
    }
    this->array[index] = value;
    this->array_size++;
    return true;
 }

bool DynamicArray::remove(const int index) {
    if (index < 0 || index >= this->array_size) {
        return false;
    }
    for (int i = index; i < this->array_size - 1; i++) {
        this->array[i] = this->array[i + 1];
    }
    this->array_size--;
    return true;
}
bool DynamicArray::remove() {
    if (this->array_size == 0) {
        return false;
    }
    this->array_size--;
    return true;
}
bool DynamicArray::append(const int value) {
    return this->insert(value);
}
int& DynamicArray::operator [] (int index) {
    if (index < 0 || index >= this->array_size) {
        throw std::out_of_range("Index out of range");
    }
    return this->array[index];
}	
int DynamicArray::get(const int index) {
    if (index < 0 || index >= this->array_size) {
        throw std::out_of_range("Index out of range");
    }
    return this->array[index];
}
bool DynamicArray::set(const int index, const int value) {
    if (index < 0 || index >= this->array_size) {
        throw std::out_of_range("Index out of range");
    }
    this->array[index] = value;
    return true;
}

void DynamicArray::print() {
    for (int i = 0; i < this->array_size; i++) {
        std::cout << this->array[i] << " ";
    }
    std::cout << std::endl;
}

void DynamicArray::bubbleSortAsc() {
    for (int i = 0; i < this->array_size - 1; i++) {
        for (int j = 0; j < this->array_size - i - 1; j++) {
            if (this->array[j] > this->array[j + 1]) {
                std::swap(this->array[j], this->array[j + 1]);
            }
        }
    }
}
void DynamicArray::bubbleSortDsc() {
    for (int i = 0; i < this->array_size - 1; i++) {
        for (int j = 0; j < this->array_size - i - 1; j++) {
            if (this->array[j] < this->array[j + 1]) {
                std::swap(this->array[j], this->array[j + 1]);
            }
        }
    }
}
void DynamicArray::insertionSortAsc() {
    for (int i = 1; i < this->array_size; i++) {
        int key = this->array[i];
        int j = i - 1;
        while (j >= 0 && this->array[j] > key) {
            this->array[j + 1] = this->array[j];
            j--;
        }
        this->array[j + 1] = key;
    }
}
void DynamicArray::insertionSortDsc() {
    for (int i = 1; i < this->array_size; i++) {
        int key = this->array[i];
        int j = i - 1;
        while (j >= 0 && this->array[j] < key) {
            this->array[j + 1] = this->array[j];
            j--;
        }
        this->array[j + 1] = key;
    }
}
void DynamicArray::selectionSortAsc() {
    for (int i = 0; i < this->array_size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < this->array_size; j++) {
            if (this->array[j] < this->array[min_idx]) {
                min_idx = j;
            }
        }
        std::swap(this->array[i], this->array[min_idx]);
    }
}
void DynamicArray::selectionSortDsc() {
    for (int i = 0; i < this->array_size - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < this->array_size; j++) {
            if (this->array[j] > this->array[max_idx]) {
                max_idx = j;
            }
        }
        std::swap(this->array[i], this->array[max_idx]);
    }
}

int DynamicArray::getKthLargest(const int k) {
    if (k <= 0 || k > this->array_size) {
        throw std::out_of_range("k is out of range");
    }
    this->selectionSortDsc();
    return this->array[k - 1];
 }
int DynamicArray::getKthSmallest(const int k) {
    if (k <= 0 || k > this->array_size) {
        throw std::out_of_range("k is out of range");
    }
    this->selectionSortAsc();
    return this->array[k - 1];
 }

int DynamicArray::linearSearch(const int value) {
    for (int i = 0; i < this->array_size; i++) {
        if (this->array[i] == value) {
            return i;
        }
    }
    return -1;
 }
int DynamicArray::binarySearch(const int value) {
    this->selectionSortAsc();
    int left = 0, right = this->array_size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (this->array[mid] == value) {
            return mid;
        }
        else if (this->array[mid] < value) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
 }

DynamicArray DynamicArray::merge(const DynamicArray& b) const { 
    DynamicArray result(this->array_size + b.array_size);
    for (int i = 0; i < this->array_size; i++) {
        result.append(this->array[i]);
    }
    for (int i = 0; i < b.array_size; i++) {
        result.append(b.array[i]);
    }
    return result;
}
