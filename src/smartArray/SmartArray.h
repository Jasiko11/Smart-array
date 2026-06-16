
#ifndef SMART_ARRAY_MYVECTOR_H
#define SMART_ARRAY_MYVECTOR_H
#include <stdexcept>

template <typename T = int>
class SmartArray
{
    unsigned m_size;
    unsigned m_capacity;
    T* m_data;

public:
    /**
     * @brief Konstruktor domyślny — tworzy pustą tablicę.
     */
    SmartArray();

    /**
     * @brief Konstruktor rezerwujący pamięć bez inicjalizacji elementów.
     *
     * @param size Żądana pojemność początkowa.
     */
    SmartArray(unsigned size);

    /**
     * @brief Konstruktor wypełniający tablicę podaną wartością.
     *
     * @param size Liczba elementów do utworzenia.
     * @param elem Wartość, którą wypełnione zostaną wszystkie pozycje.
     */
    SmartArray(unsigned size, T elem);

    /**
     * @brief Konstruktor kopiujący.
     *
     * @param array Tablica źródłowa.
     */
    SmartArray(SmartArray& array);

    /**
     * @brief Destruktor — zwalnia zaalokowaną pamięć.
     */
    ~SmartArray();

    /**
     * @brief Zwraca element o podanym indeksie z kontrolą zakresu.
     *
     * @param index Indeks elementu (od 0 do size()-1).
     * @return Kopia elementu na pozycji @p index.
     * @throws std::out_of_range Gdy @p index >= size().
     */
    T at(unsigned index);

    /**
     * @brief Operator indeksowania bez kontroli zakresu.
     *
     * @param index Indeks elementu.
     * @return Kopia elementu na pozycji @p index.
     */
    T operator[](unsigned index);

    /**
     * @brief Sprawdza, czy tablica jest pusta.
     * @return true gdy size() == 0, false w przeciwnym razie.
     */
    bool isEmpty() const;

    /**
     * @brief Zwraca aktualną liczbę elementów.
     * @return Liczba elementów przechowywanych w tablicy.
     */
    unsigned size() const;

    /**
     * @brief Zwraca pojemność aktualnie zaalokowanego bufora.
     *
     * @return Pojemność bufora w liczbie elementów.
     */
    unsigned capacity() const;

    /**
     * @brief Rezerwuje pamięć na co najmniej @p size elementów.
     *
     * @param size Minimalna żądana pojemność.
     */
    void reserve(unsigned size);

    /**
     * @brief Realokuje bufor do nowej pojemności.
     *
     * @param newCapacity Nowa pojemność bufora.
     */
    void reallocate(unsigned newCapacity);

    /**
     * @brief Zmienia rozmiar tablicy.
     *
     * @param size Nowy rozmiar tablicy.
     */
    void resize(unsigned size);

    /**
     * @brief Zmienia rozmiar tablicy, wypełniając nowe miejsca podaną wartością.
     *
     * @param size Nowy rozmiar tablicy.
     * @param elem Wartość, którą wypełniane są nowe pozycje.
     */
    void resize(unsigned size, T elem);

    /**
     * @brief Usuwa wszystkie elementy bez zwalniania pamięci.
     */
    void clear();

    /**
     * @brief Wstawia element na podanej pozycji.
     *
     * @param index Indeks, na który wstawiany jest element (0..size()).
     * @param elem  Element do wstawienia.
     * @throws std::out_of_range Gdy @p index > size().
     */
    void insert(unsigned index, T elem);

    /**
     * @brief Usuwa element o podanym indeksie.
     *
     * @param index Indeks elementu do usunięcia.
     * @throws std::out_of_range Gdy @p index >= size().
     */
    void erase(unsigned index);

    /**
     * @brief Usuwa @p amount elementów zaczynając od @p index.
     *
     * @param index  Indeks pierwszego usuwanego elementu.
     * @param amount Liczba elementów do usunięcia.
     * @throws std::out_of_range Gdy zakres wykracza poza tablicę.
     */
    void erase(unsigned index, unsigned amount);

    /**
    * @brief Dodaje element na koniec tablicy.
    *
    * @param elem Element do dodania.
    */
    void pushBack(T elem);

    /**
     * @brief Usuwa ostatni element tablicy.
     */
    void popBack();

    /**
     * @brief Zmniejsza pojemność do aktualnego rozmiaru.
     *
     * Przydatne po usunięciu dużej liczby elementów, by zwolnić
     * nieużywaną pamięć.
     */
    void shrinkToFit();

    /**
     * @brief Dodaje element na początek tablicy.
     *
     * @param elem Element do dodania na przód.
     */
    void pushFront(T elem);

    /**
    * @brief Usuwa pierwszy element tablicy.
    */
    void popFront();

    /**
     * @brief Porównuje dwie tablice pod względem zawartości.
     *
     * @param array Tablica do porównania.
     * @return true gdy tablice są identyczne, false w p.p.
     */
    bool operator==(SmartArray array);

    /**
     * @brief Operator przypisania — głęboka kopia.
     *
     * @param array Tablica źródłowa.
     * @return Referencja do this.
     */
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
    for (unsigned i = 0; i < copyCount; ++i) {
        newData[i] = m_data[i];
    }
    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity;
    m_size = copyCount;
}

template<typename T>
void SmartArray<T>::resize(unsigned size) {
    if (size > m_capacity) {
        unsigned newCapacity = size;
        reallocate(newCapacity);
    }
    for (unsigned i = m_size; i < size; ++i) {
        m_data[i] = T();
    }
    m_size = size;
}

template<typename T>
void SmartArray<T>::resize(unsigned size, T elem) {
    if (size > m_capacity) {
        unsigned newCapacity = size;
        reallocate(newCapacity);
    }
    for (unsigned i = m_size; i < size; ++i) {
        m_data[i] = elem;
    }
    m_size = size;
}

template<typename T>
void SmartArray<T>::clear() {
    m_size = 0;
}

template<typename T>
void SmartArray<T>::insert(unsigned index, T elem) {
    if (index > m_size) throw std::out_of_range("index out of range");
    if (m_size == m_capacity) {
        unsigned newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        reallocate(newCapacity);
    }
    for (unsigned i = m_size; i > index; --i) {
        m_data[i] = m_data[i - 1];
    }
    m_data[index] = elem;
    ++m_size;
}

template<typename T>
void SmartArray<T>::erase(unsigned index) {
    if (index >= m_size) throw std::out_of_range("index out of range");
    for (unsigned i = index; i < m_size - 1; ++i) {
        m_data[i] = m_data[i + 1];
    }
    --m_size;
}

template<typename T>
void SmartArray<T>::erase(unsigned index, unsigned amount) {
    if (index >= m_size || index + amount > m_size) throw std::out_of_range("index out of range");
    for (unsigned i = index; i < m_size - amount; ++i) {
        m_data[i] = m_data[i + amount];
    }
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
    if (m_size > 0) --m_size;
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
    for (unsigned i = 0; i < m_size; ++i) {
        if (m_data[i] != array.m_data[i]) return false;
    }
    return true;
}

template<typename T>
SmartArray<T>& SmartArray<T>::operator=(SmartArray const &array) {
    if (this == &array) return *this;
    delete[] m_data;
    m_size = array.m_size;
    m_capacity = array.m_capacity;
    m_data = (m_capacity > 0) ? new T[m_capacity] : nullptr;
    for (unsigned i = 0; i < m_size; ++i) {
        m_data[i] = array.m_data[i];
    }
    return *this;
}


#endif
