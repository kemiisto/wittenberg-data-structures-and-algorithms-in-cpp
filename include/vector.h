#ifndef WITTENBERG_DATA_STRUCTURES_AND_ALGORITHMS_IN_CPP_VECTOR_H
#define WITTENBERG_DATA_STRUCTURES_AND_ALGORITHMS_IN_CPP_VECTOR_H

#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <stdexcept>

namespace wittenberg {
    template <typename T>
    class vector {
    public:
        using iterator = T*;
        using const_iterator = const T*;

        explicit vector(size_t num_elements = 0, const T& init = T{}) :
                allocated{num_elements}, used{num_elements} {
            assert(num_elements >= 0);
            data = new T[allocated];
            std::fill(data, data + used, init);
        }

        vector(std::initializer_list<T> init) :
                allocated{init.size()}, used{init.size()} {
            data = new T[allocated];
            std::copy(init.begin(), init.end(), data);
        }

        ~vector() {
            delete[] data;
        }

        vector(const vector& other) :
                allocated{other.allocated}, used{other.used} {
            data = new T[allocated];
            std::copy(other.data, other.data + other.used, data);
        }

        vector<T>& operator=(const vector& other) {
            if (this != &other) {
                delete[] data;
                allocated = other.allocated;
                used = other.used;
                data = new T[allocated];
                std::copy(other.data, other.data + other.used, data);
            }
            return *this;
        }

        size_t size() const {
            return used;
        }

        size_t capacity() const {
            return allocated;
        }

        bool empty() const {
            return size() == 0;
        }

        T& front() {
            return data[0];
        }

        const T& front() const {
            return data[0];
        }

        T& back() {
            return data[used - 1];
        }

        const T& back() const {
            return data[used - 1];
        }

        T& operator[](int index) {
            return data[index];
        }

        const T& operator[](int index) const {
            return data[index];
        }

        T& at(int index) {
            if (index < 0 || index >= used) {
                throw std::out_of_range("vector index out of range");
            }
            return data[index];
        }

        const T& at(int index) const {
            if (index < 0 || index >= used) {
                throw std::out_of_range("vector index out of range");
            }
            return data[index];
        }

        void push_back(const T& value) {
            resize(used + 1);
            data[used - 1] = value;
        }

        void pop_back() {
            if (used > 0) {
                --used;
            }
        }

        void clear() {
            used = 0;
        }

        void resize(size_t new_size, const T& init = T{}) {
            // allocate more space for data, if necessary
            if (new_size > allocated) {
                T* old_data = data;
                allocated = std::max(new_size, 2 * allocated);
                data = new T[allocated];
                std::copy(old_data, old_data + used, data);
                delete[] old_data;
            }
            // initialize new elements of data to init
            if (new_size > used) {
                std::fill(data + used, data + new_size, init);
            }
            used = new_size;
        }

        iterator begin() {
            return data;
        }

        iterator end() {
            return data + used;
        }

        const_iterator begin() const {
            return data;
        }

        const_iterator end() const {
            return data + used;
        }
    private:
        T* data{};
        size_t allocated;
        size_t used;
    };
}

#endif // WITTENBERG_DATA_STRUCTURES_AND_ALGORITHMS_IN_CPP_VECTOR_H
