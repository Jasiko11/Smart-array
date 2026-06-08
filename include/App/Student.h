
#ifndef INCLUDE_SMARTARRAY_STUDENT_H
#define INCLUDE_SMARTARRAY_STUDENT_H
#include <string>
#include <utility>

/**
 * @brief Class representing a student
 */
class Student {
public:
    std::string name;
    std::string surname;
    int indexNumber;
    int year;
    double gpa;

    Student():indexNumber(-1), year(1), gpa(.0){}

    Student(std::string  name, std::string  surname, int number, int year, double gpa)
        :name(std::move(name)), surname(std::move(surname)), indexNumber(number), year(year), gpa(gpa){}

    bool operator==(const Student& rhs) const {
        return indexNumber == rhs.indexNumber;
    }

    bool operator!=(const Student& rhs) const {
        return indexNumber != rhs.indexNumber;
    }
};


#endif //INCLUDE_SMARTARRAY_STUDENT_H
