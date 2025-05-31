#pragma once

#include <iostream>
#include <cassert>

using namespace std;

namespace NP
{
    template <typename T>
    class DynamicArray
    {
    private:
        T* buffer;
        size_t _size;
        size_t _capacity;

        static constexpr size_t DEFAULT_INITIAL_CAPACITY = 10;
        static constexpr double GROWTH_FACTOR = 2.0;

        void reallocate(size_t new_capacity_val);

    public:
        DynamicArray();
        DynamicArray(size_t initialCapacity);
        DynamicArray(size_t count, const T& value);

        ~DynamicArray();
        DynamicArray(const DynamicArray& other);
        DynamicArray& operator=(const DynamicArray& other);

        T& at(size_t index);
        const T& at(size_t index) const;
        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
        T* data_ptr();
        const T* data_ptr() const;

        void push_back(const T& value);
        void pop_back();
        void clear();
        void resize(size_t newSize);
        void resize(size_t newSize, const T& value);

        void reserve(size_t newCapacity);
        void shrink_to_fit();

        size_t size() const;
        size_t capacity() const;
        bool empty() const;
        size_t max_size() const;
        size_t memory_usage() const;
    };

    template <typename T>
    void NP::DynamicArray<T>::reallocate(size_t new_capacity_val) 
    {
        T* new_buffer = nullptr;
        if (new_capacity_val > 0) 
        {
            new_buffer = new T[new_capacity_val];
        }

        if (buffer != nullptr) 
        {
            size_t elements_to_copy = _size;
            if (new_capacity_val < _size) 
            {
                elements_to_copy = new_capacity_val;
            }
            if (new_buffer != nullptr) 
            {
                for (size_t i = 0; i < elements_to_copy; ++i) 
                {
                    new_buffer[i] = buffer[i];
                }
            }
            delete[] buffer;
        }
        buffer = new_buffer;
        _capacity = new_capacity_val;
    }

    template <typename T>
    NP::DynamicArray<T>::DynamicArray(): buffer(nullptr), _size(0), _capacity(0) 
    {
        if (DEFAULT_INITIAL_CAPACITY > 0) 
        {
            reallocate(DEFAULT_INITIAL_CAPACITY);
        }
    }

    template <typename T>
    NP::DynamicArray<T>::DynamicArray(size_t initialCapacity): buffer(nullptr), _size(0), _capacity(0) {
        if (initialCapacity > 0) {
            reallocate(initialCapacity);
        }
    }

    template <typename T>
    NP::DynamicArray<T>::DynamicArray(size_t count, const T& value): buffer(nullptr), _size(0), _capacity(0) 
    {
        if (count > 0) 
        {
            reallocate(count);
            _size = count;
            for (size_t i = 0; i < _size; ++i) 
            {
                buffer[i] = value;
            }
        }
    }

    template <typename T>
    NP::DynamicArray<T>::~DynamicArray() 
    {
        delete[] buffer;
        buffer = nullptr;
    }

    template <typename T>
    NP::DynamicArray<T>::DynamicArray(const DynamicArray& other): buffer(nullptr), _size(0), _capacity(0) {
        if (other._capacity > 0) 
        {
            reallocate(other._capacity);
            _size = other._size;
            for (size_t i = 0; i < _size; ++i) 
            {
                buffer[i] = other.buffer[i];
            }
        }
    }

    template <typename T>
    NP::DynamicArray<T>& NP::DynamicArray<T>::operator=(const DynamicArray& other) 
    {
        if (this == &other) 
        {
            return *this;
        }
        delete[] buffer;
        buffer = nullptr;
        _capacity = 0;
        _size = 0;

        if (other._capacity > 0) 
        {
            reallocate(other._capacity);
            _size = other._size;
            for (size_t i = 0; i < _size; ++i) 
            {
                buffer[i] = other.buffer[i];
            }
        }
        return *this;
    }

    template <typename T>
    T& NP::DynamicArray<T>::at(size_t index) 
    {
        assert(index < _size && "DynamicArray::at - index out of range");
        return buffer[index];
    }

    template <typename T>
    const T& NP::DynamicArray<T>::at(size_t index) const 
    {
        assert(index < _size && "DynamicArray::at const - index out of range");
        return buffer[index];
    }

    template <typename T>
    T& NP::DynamicArray<T>::operator[](size_t index) 
    {
        return buffer[index];
    }

    template <typename T>
    const T& NP::DynamicArray<T>::operator[](size_t index) const 
    {
        return buffer[index];
    }

    template <typename T>
    T& NP::DynamicArray<T>::front() 
    {
        assert(!empty() && "DynamicArray::front - array is empty");
        return buffer[0];
    }

    template <typename T>
    const T& NP::DynamicArray<T>::front() const 
    {
        assert(!empty() && "DynamicArray::front const - array is empty");
        return buffer[0];
    }

    template <typename T>
    T& NP::DynamicArray<T>::back() 
    {
        assert(!empty() && "DynamicArray::back - array is empty");
        return buffer[_size - 1];
    }

    template <typename T>
    const T& NP::DynamicArray<T>::back() const 
    {
        assert(!empty() && "DynamicArray::back const - array is empty");
        return buffer[_size - 1];
    }

    template <typename T>
    T* NP::DynamicArray<T>::data_ptr() 
    {
        return buffer;
    }

    template <typename T>
    const T* NP::DynamicArray<T>::data_ptr() const 
    {
        return buffer;
    }

    template <typename T>
    void NP::DynamicArray<T>::push_back(const T& value) 
    {
        if (_size >= _capacity) 
        {
            size_t new_cap = (_capacity == 0) ? DEFAULT_INITIAL_CAPACITY : static_cast<size_t>(_capacity * GROWTH_FACTOR);
            if (new_cap <= _size) 
            {
                new_cap = _size + 1;
            }
            if (new_cap == 0 && DEFAULT_INITIAL_CAPACITY > 0 && _capacity == 0) 
            {
                new_cap = DEFAULT_INITIAL_CAPACITY;
            }
            if (new_cap == 0 && _capacity == 0 && _size == 0) 
            {
                new_cap = 1;
            }
            reserve(new_cap);
        }
        buffer[_size] = value;
        _size++;
    }

    template <typename T>
    void NP::DynamicArray<T>::pop_back() 
    {
        assert(!empty() && "DynamicArray::pop_back - array is empty");
        _size--;
    }

    template <typename T>
    void NP::DynamicArray<T>::clear() 
    {
        _size = 0;
    }

    template <typename T>
    void NP::DynamicArray<T>::resize(size_t newSize) 
    {
        if (newSize > _size) 
        {
            if (newSize > _capacity) 
            {
                reserve(newSize);
            }
            assert(_capacity >= newSize && "Internal error: resize did not ensure sufficient capacity after reserve.");
            for (size_t i = _size; i < newSize; ++i) 
            {
                assert(i < _capacity && "Internal error: resize trying to write past allocated capacity.");
                buffer[i] = T();
            }
        }
        _size = newSize;
    }

    template <typename T>
    void NP::DynamicArray<T>::resize(size_t newSize, const T& value) 
    {
        if (newSize > _size) {
            if (newSize > _capacity) 
            {
                reserve(newSize);
            }
            assert(_capacity >= newSize && "Internal error: resize(value) did not ensure sufficient capacity after reserve.");
            for (size_t i = _size; i < newSize; ++i) 
            {
                assert(i < _capacity && "Internal error: resize(value) trying to write past allocated capacity.");
                buffer[i] = value;
            }
        }
        _size = newSize;
    }

    template <typename T>
    void NP::DynamicArray<T>::reserve(size_t newCapacity) 
    {
        if (newCapacity > _capacity) 
        {
            reallocate(newCapacity);
        }
    }

    template <typename T>
    void NP::DynamicArray<T>::shrink_to_fit() 
    {
        if (_capacity > _size) 
        {
            if (_size == 0) 
            {
                delete[] buffer;
                buffer = nullptr;
                _capacity = 0;
            }
            else 
            {
                T* new_buffer = new T[_size];
                for (size_t i = 0; i < _size; ++i) 
                {
                    new_buffer[i] = buffer[i];
                }
                delete[] buffer;
                buffer = new_buffer;
                _capacity = _size;
            }
        }
    }

    template <typename T>
    size_t NP::DynamicArray<T>::size() const 
    {
        return _size;
    }

    template <typename T>
    size_t NP::DynamicArray<T>::capacity() const 
    {
        return _capacity;
    }

    template <typename T>
    bool NP::DynamicArray<T>::empty() const 
    {
        return _size == 0;
    }

    template <typename T>
    size_t NP::DynamicArray<T>::max_size() const 
    {
        if (sizeof(T) == 0)
        {
            return ((size_t)-1);
        } 
        return ((size_t)-1) / sizeof(T);
    }

    template <typename T>
    size_t NP::DynamicArray<T>::memory_usage() const 
    {
        return _capacity * sizeof(T);
    }
}