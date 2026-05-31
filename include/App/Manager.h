
#ifndef INCLUDE_SMARTARRAY_MANAGER_H
#define INCLUDE_SMARTARRAY_MANAGER_H

#include <fstream>
#include <iostream>

#include "Student.h"
#include "SmartArray/SmartArray.h"

/**
 * @brief Class managing students
 */
class Manager {
    SmartArray<Student> m_students;
    /**
     * @brief Writes string to binary file
     */
    static void writeStr(std::ofstream& f, const std::string& s) {
        auto len = static_cast<unsigned>(s.size());
        f.write(reinterpret_cast<const char*>(&len), sizeof(len));
        f.write(s.data(), len);
    }

    /**
     * @brief Reads string from binary file
     */
    static std::string readStr(std::ifstream& f) {
        unsigned len = 0;
        f.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string s(len, '\0');
        f.read(&s[0], len);
        return s;
    }
public:
    /**
     * @brief Adding a new student
     * @param student Student to add
     */
    void add(const Student& student) {
        m_students.pushBack(student);
    }

    /**
     * @brief Removes student from an index
     * @param index Index of student to remove
     */
    void remove(unsigned index) {
        m_students.erase(index);
    }

    /**
     * @return Returns the number of students
     */
    unsigned count() {
        return m_students.size();
    }

    /**
     * @brief Prints all students
     */
    void print() {
        for (unsigned i = 0; i < m_students.size(); ++i) {
            std::cout << "Imie: " << m_students[i].name
            << "Nazwisko: " << m_students[i].surname
            << "Numer indeksu: " << m_students[i].indexNumber
            << "Rok: " << m_students[i].year
            << "Srednia: " << m_students[i].gpa << std::endl;
        }
    }

    /**
     * @brief Prints students in a range
     * @param start Starting index
     * @param stop Ending index
     */
    void print(unsigned start, unsigned stop) {
        if (stop > m_students.size()) {
            throw std::out_of_range("Wrong range");
        }
        for (unsigned i = start; i < m_students.size(); ++i) {
            std::cout << "Imie: " << m_students[i].name
            << "Nazwisko: " << m_students[i].surname
            << "Numer indeksu: " << m_students[i].indexNumber
            << "Rok: " << m_students[i].year
            << "Srednia: " << m_students[i].gpa << std::endl;
        }
    }

};

#endif //INCLUDE_SMARTARRAY_MANAGER_H
