
#ifndef SMART_ARRAY_MYVECTOR_H
#define SMART_ARRAY_MYVECTOR_H
#include <stdexcept>

template <typename T>
class SmartArray
{
    unsigned m_size;
    unsigned m_capacity;
    T* m_data;

public:
    SmartArray();
    SmartArray(unsigned size);
    SmartArray(unsigned size, T elem);
    SmartArray(SmartArray& array);
    ~SmartArray();

    T at(unsigned index);
    T operator[](unsigned index);
    bool isEmpty() const;
    unsigned size() const;
    unsigned capacity() const;
    void reserve(unsigned size);
    void reallocate(unsigned newCapacity);
    void resize(unsigned size);
    void resize(unsigned size, T elem);
    void clear();
    void insert(unsigned index, T elem);
    void erase(unsigned index);
    void erase(unsigned index, unsigned amount);
    void pushBack(T elem);
    void popBack();
    void shrinkToFit();
    void pushFront(T elem);
    void popFront();
    bool operator==(SmartArray array);
    SmartArray& operator=(SmartArray const& array);
};

template<typename T>
SmartArray<T>::SmartArray(): m_size(0), m_capacity(0), m_data(nullptr) {
}

template<typename T>
SmartArray<T>::SmartArray(unsigned size): m_size(0), m_capacity(size) {
    m_data = (size > 0) ? new T[size] : nullptr;
}

template<typename T>
SmartArray<T>::SmartArray(unsigned size, T elem): m_size(size), m_capacity(size) {
    m_data = (size > 0) ? new T[size] : nullptr;
    for (unsigned i = 0; i < size; ++i)
        m_data[i] = elem;
}

template<typename T>
SmartArray<T>::SmartArray(SmartArray &array) {
    m_size = array.m_size;
    m_capacity = array.m_capacity;
    m_data = (m_capacity > 0) ? new T[m_capacity] : nullptr;
    for (unsigned i = 0; i < m_size; ++i)
        m_data[i] = array.m_data[i];
}

template<typename T>
SmartArray<T>::~SmartArray() {
    delete[] m_data;
}

template<typename T>
T SmartArray<T>::at(unsigned index) {
    if (index >= m_size) {
        throw std::out_of_range("index out of range");
    }
    return m_data[index];
}

template<typename T>
T SmartArray<T>::operator[](unsigned index) {
    return m_data[index];
}

template<typename T>
bool SmartArray<T>::isEmpty() const {
    return m_size == 0;
}

template<typename T>
unsigned SmartArray<T>::size() const {
    return m_size;
}

template<typename T>
unsigned SmartArray<T>::capacity() const {
    return m_capacity;
}

template<typename T>
void SmartArray<T>::reserve(unsigned size) {
    if (size > m_capacity)
        reallocate(size);
}

template<typename T>
void SmartArray<T>::reallocate(unsigned newCapacity) {
    T* newData = (newCapacity > 0) ? new T[newCapacity] : nullptr;
    unsigned copyCount = (m_size > newCapacity) ? newCapacity : m_size;
    for (unsigned i = 0; i < copyCount; ++i)
        newData[i] = m_data[i];
    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity;
    m_size = (m_size > newCapacity) ? newCapacity : m_size;
}

template<typename T>
void SmartArray<T>::resize(unsigned size) {
    if (size > m_capacity) {
        unsigned newCapacity = size;
        reallocate(newCapacity);
    }
    for (unsigned i = m_size; i < size; ++i)
        m_data[i] = T();
    m_size = size;
}

template<typename T>
void SmartArray<T>::resize(unsigned size, T elem) {
    if (size > m_capacity) {
        unsigned newCapacity = size;
        reallocate(newCapacity);
    }
    for (unsigned i = m_size; i < size; ++i)
        m_data[i] = elem;
    m_size = size;
}

template<typename T>
void SmartArray<T>::clear() {
    m_size = 0;
}

template<typename T>
void SmartArray<T>::insert(unsigned index, T elem) {
    if (index > m_size)
        throw std::out_of_range("index out of range");
    if (m_size == m_capacity) {
        unsigned newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        reallocate(newCapacity);
    }
    for (unsigned i = m_size; i > index; --i)
        m_data[i] = m_data[i - 1];
    m_data[index] = elem;
    ++m_size;
}

template<typename T>
void SmartArray<T>::erase(unsigned index) {
    if (index >= m_size)
        throw std::out_of_range("index out of range");
    for (unsigned i = index; i < m_size - 1; ++i)
        m_data[i] = m_data[i + 1];
    --m_size;
}

template<typename T>
void SmartArray<T>::erase(unsigned index, unsigned amount) {
    if (index >= m_size || index + amount > m_size)
        throw std::out_of_range("index out of range");
    for (unsigned i = index; i < m_size - amount; ++i)
        m_data[i] = m_data[i + amount];
    m_size -= amount;
}

template<typename T>
void SmartArray<T>::pushBack(T elem) {
    if (m_size == m_capacity) {
        unsigned newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        reallocate(newCapacity);
    }
    m_data[m_size] = elem;
    m_size++;
}

template<typename T>
void SmartArray<T>::popBack() {
    if (m_size > 0)
        --m_size;
}

template<typename T>
void SmartArray<T>::shrinkToFit() {
    if (m_capacity > m_size) reallocate(m_size);
}

template<typename T>
void SmartArray<T>::pushFront(T elem) {
    insert(0, elem);
}

template<typename T>
void SmartArray<T>::popFront() {
    if (m_size > 0) erase(0);
}

template<typename T>
bool SmartArray<T>::operator==(SmartArray array) {
    if (m_size != array.m_size) return false;
    for (unsigned i = 0; i < m_size; ++i)
        if (m_data[i] != array.m_data[i]) return false;
    return true;
}

template<typename T>
SmartArray<T>& SmartArray<T>::operator=(SmartArray const &array) {
    if (this == &array) return *this;
    delete[] m_data;
    m_size = array.m_size;
    m_capacity = array.m_capacity;
    m_data = (m_capacity > 0) ? new T[m_capacity] : nullptr;
    for (unsigned i = 0; i < m_size; ++i)
        m_data[i] = array.m_data[i];
    return *this;
}


#endif
