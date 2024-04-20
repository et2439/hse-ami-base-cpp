#include "sort_students.h"

bool CompareDates(const Student& student_1, const Student& student_2) {
    if (student_1.birth_date.year == student_2.birth_date.year) {
        if (student_1.birth_date.month == student_2.birth_date.month) {
            return student_1.birth_date.day <= student_2.birth_date.day;
        }
        return student_1.birth_date.month <= student_2.birth_date.month;
    }
    return student_1.birth_date.year <= student_2.birth_date.year;
}

bool CompareNames(Student student_1, Student student_2) {
    if (student_1.last_name == student_2.last_name) {
        return student_1.name <= student_2.name;
    }
    return student_1.last_name <= student_2.last_name;
}

void SortByDate(std::vector<Student>& students) {
    std::sort(students.begin(), students.end(), CompareDates);
}

void SortByNames(std::vector<Student>& students) {
    std::sort(students.begin(), students.end(), CompareNames);
}

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    if (sortKind == SortKind::Date) {
        SortByNames(students);
        SortByDate(students);
    }
    if (sortKind == SortKind::Name) {
        SortByDate(students);
        SortByNames(students);
    }
}
