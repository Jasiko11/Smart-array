#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "Student.h"
#include <string>

#include "SmartArray/SmartArray.h"

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
     * @brief Wyszukuje studentów po nazwisku.
     * @param surname Poszukiwane nazwisko (lub fragment).
     * @return Nowa instancja SmartArray z wynikami.
     */
    SmartArray<Student> searchBySurname(const std::string& surname);

    /**
     * @brief Wyszukuje studentów spełniających kryterium roku i minimalnej średniej.
     * @param year Rok studiów.
     * @param minGpa Minimalna średnia ocen.
     * @return SmartArray z dopasowanymi studentami.
     */
    SmartArray<Student> searchByYearAndGpa(int year, double minGpa);

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
     * @brief Zapisuje kolekcję studentów do pliku binarnego.
     * @param filename Ścieżka do pliku.
     * @return true jeśli zapis przebiegł pomyślnie.
     */
    bool saveToBinaryFile(const std::string& filename);

    /**
     * @brief Wczytuje kolekcję studentów z pliku binarnego.
     * @param filename Ścieżka do pliku.
     * @return true jeśli odczyt przebiegł pomyślnie.
     */
    bool loadFromBinaryFile(const std::string& filename);
};

#endif