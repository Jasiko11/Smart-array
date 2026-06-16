#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "Student.h"
#include <string>
#include <map>

#include "../smartArray/SmartArray.h"

/**
 * @brief Klasa zarządzająca bazą danych studentów przy użyciu kontenera SmartArray.
 */
class StudentManager {
private:
    SmartArray<Student> students;

public:
    /**
     * @brief Dodaje nowego studenta na koniec tablicy.
     * @param s Obiekt studenta do dodania.
     */
    void addStudent(const Student& s);

    /**
     * @brief Usuwa studenta ze wskazanego indeksu.
     * @param index Numer indeksu w tablicy SmartArray.
     * @return true jeśli usuwanie się powiodło, false w przeciwnym wypadku.
     */
    bool removeStudent(unsigned index);

    /**
     * @brief Modyfikuje dane studenta pod konkretnym indeksem.
     * @param index Pozycja w tablicy.
     * @param updatedStudent Nowe dane studenta.
     * @return true jeśli modyfikacja się powiodła.
     */
    bool editStudent(unsigned index, const Student& updatedStudent);

    /**
     * @brief Zwraca liczbę przechowywanych studentów.
     */
    unsigned getCount() const;

    /**
     * @brief Pobiera studenta z określonego indeksu.
     * @param index Pozycja w tablicy.
     * @return Obiekt klasy Student.
     */
    Student getStudent(unsigned index);

    /**
     * @brief Oblicza średnią ocen (GPA) wszystkich studentów w bazie.
     */
    double calculateAverageGpa();

    /**
     * @brief Zaawansowana agregacja: Oblicza średnią ocen studentów tylko z wybranego roku studiów.
     * @param year Kryterium roku studiów.
     */
    double calculateAverageGpaForYear(int year);

    /**
 * @brief Wyszukuje studentów po dowolnym polu lub polach.
 * @param criteria Dane studenta do wyszukiwania.
 * @return SmartArray<Student> zawierający studentów spełniających kryterium.
 */
    SmartArray<Student> searchByField(const std::map<std::string, std::string>& criteria);

    /**
     * @brief Zapisuje studentów do pliku binarnego.
     * @param filename Ścieżka do pliku.
     * @return true jeśli zapis przebiegł pomyślnie.
     */
    bool saveToBinaryFile(const std::string& filename);

    /**
     * @brief Wczytuje studentów z pliku binarnego.
     * @param filename Ścieżka do pliku.
     * @return true jeśli odczyt przebiegł pomyślnie.
     */
    bool loadFromBinaryFile(const std::string& filename);
};

#endif