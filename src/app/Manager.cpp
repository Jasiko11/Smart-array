#include "Manager.h"
#include <fstream>
#include <iostream>

void StudentManager::addStudent(const Student& s) {
    students.pushBack(s);
}

bool StudentManager::removeStudent(unsigned index) {
    if (index >= students.size()) return false;
    students.erase(index);
    return true;
}

bool StudentManager::editStudent(unsigned index, const Student& updatedStudent) {
    if (index >= students.size()) return false;
    students.erase(index);
    students.insert(index, updatedStudent);
    return true;
}

unsigned StudentManager::getCount() const {
    return students.size();
}

Student StudentManager::getStudent(unsigned index) {
    return students.at(index);
}


double StudentManager::calculateAverageGpa() {
    if (students.isEmpty()) return 0.0;
    double sum = 0.0;
    for (unsigned i = 0; i < students.size(); ++i) {
        sum += students.at(i).gpa;
    }
    return sum / students.size();
}

double StudentManager::calculateAverageGpaForYear(int year) {
    if (students.isEmpty()) return 0.0;
    double sum = 0.0;
    unsigned count = 0;
    for (unsigned i = 0; i < students.size(); ++i) {
        Student s = students.at(i);
        if (s.year == year) {
            sum += s.gpa;
            count++;
        }
    }
    return sum / count;
}

#include <map>
#include <string>


SmartArray<Student> StudentManager::searchByField(const std::map<std::string, std::string>& criteria) {
    SmartArray<Student> result;

    if (criteria.empty()) {
        return result;
    }

    for (unsigned i = 0; i < students.size(); ++i) {
        Student s = students.at(i);
        bool match = true;

        for (const auto& [field, value] : criteria) {
            if (field == "name") {
                if (s.name != value) match = false;
            }
            else if (field == "surname") {
                if (s.surname != value) match = false;
            }
            else if (field == "index") {
                try {
                    int v = std::stoi(value);
                    if (s.indexNumber != v) match = false;
                } catch (...) {
                    match = false;
                }
            }
            else if (field == "year") {
                try {
                    int v = std::stoi(value);
                    if (s.year != v) match = false;
                } catch (...) {
                    match = false;
                }
            }
            else if (field == "gpa") {
                try {
                    double v = std::stod(value);
                    if (s.gpa != v) match = false;
                } catch (...) {
                    match = false;
                }
            }
            else {
                match = false;
            }

            if (!match) break;
        }

        if (match) {
            result.pushBack(s);
        }
    }

    return result;
}

bool StudentManager::saveToBinaryFile(const std::string& filename) {
    std::ofstream ofs(filename, std::ios::binary);
    if (ofs.good()) {
        unsigned count = students.size();
        ofs.write(reinterpret_cast<const char*>(&count), sizeof(count));

        for (unsigned i = 0; i < count; ++i) {
            Student s = students.at(i);

            size_t nameLen = s.name.size();
            ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
            ofs.write(s.name.data(), nameLen);

            size_t surnameLen = s.surname.size();
            ofs.write(reinterpret_cast<const char*>(&surnameLen), sizeof(surnameLen));
            ofs.write(s.surname.data(), surnameLen);

            ofs.write(reinterpret_cast<const char*>(&s.indexNumber), sizeof(s.indexNumber));
            ofs.write(reinterpret_cast<const char*>(&s.year), sizeof(s.year));
            ofs.write(reinterpret_cast<const char*>(&s.gpa), sizeof(s.gpa));
        }
        return true;
    }
    return false;
}

bool StudentManager::loadFromBinaryFile(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (ifs.good()) {
        unsigned count = 0;
        ifs.read(reinterpret_cast<char*>(&count), sizeof(count));

        students.clear();

        for (unsigned i = 0; i < count; ++i) {
            Student s;
            size_t nameLen = 0, surnameLen = 0;

            ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
            s.name.resize(nameLen);
            ifs.read(&s.name[0], nameLen);

            ifs.read(reinterpret_cast<char*>(&surnameLen), sizeof(surnameLen));
            s.surname.resize(surnameLen);
            ifs.read(&s.surname[0], surnameLen);

            ifs.read(reinterpret_cast<char*>(&s.indexNumber), sizeof(s.indexNumber));
            ifs.read(reinterpret_cast<char*>(&s.year), sizeof(s.year));
            ifs.read(reinterpret_cast<char*>(&s.gpa), sizeof(s.gpa));

            students.pushBack(s);
        }
        return true;
    }
    return false;
}