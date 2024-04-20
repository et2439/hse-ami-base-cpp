#include "admission.h"

struct CompareApplicants {
    static bool ComparePoints(const Applicant* applicant_1, const Applicant* applicant_2) {
        return applicant_1->points > applicant_2->points;
    }

    static bool CompareDates(const Applicant* applicant_1, const Applicant* applicant_2) {
        const Date& date1 = applicant_1->student.birth_date;
        const Date& date2 = applicant_2->student.birth_date;
        if (date1.year != date2.year) {
            return date1.year < date2.year;
        }
        if (date1.month != date2.month) {
            return date1.month < date2.month;
        }
        return date1.day < date2.day;
    }

    static bool CompareNames(const Applicant* applicant_1, const Applicant* applicant_2) {
        return applicant_1->student.name < applicant_2->student.name;
    }
};

struct SortApplicants {
    static void SortByPoints(std::vector<const Applicant*>& applicants) {
        std::sort(applicants.begin(), applicants.end(), CompareApplicants::ComparePoints);
    }

    static void SortByDate(std::vector<const Applicant*>& applicants) {
        std::sort(applicants.begin(), applicants.end(), CompareApplicants::CompareDates);
    }

    static void SortByNames(std::vector<const Applicant*>& applicants) {
        std::stable_sort(applicants.begin(), applicants.end(), CompareApplicants::CompareNames);
    }
};

struct CompareStudents {
    static bool CompareDates(const Student* student_1, const Student* student_2) {
        if (student_1->birth_date.year == student_2->birth_date.year) {
            if (student_1->birth_date.month == student_2->birth_date.month) {
                return student_1->birth_date.day <= student_2->birth_date.day;
            }
            return student_1->birth_date.month <= student_2->birth_date.month;
        }
        return student_1->birth_date.year <= student_2->birth_date.year;
    }

    static bool CompareNames(const Student* student_1, const Student* student_2) {
        return student_1->name <= student_2->name;
    }
};

struct SortStudents {
    static void SortByDate(std::vector<const Student*>& students) {
        std::sort(students.begin(), students.end(), CompareStudents::CompareDates);
    }

    static void SortByNames(std::vector<const Student*>& students) {
        std::sort(students.begin(), students.end(), CompareStudents::CompareNames);
    }
};

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    AdmissionTable table;
    std::vector<const Applicant*> sorted_applicants;
    for (const Applicant& applicant : applicants) {
        sorted_applicants.push_back(&applicant);
    }

    SortApplicants::SortByNames(sorted_applicants);
    SortApplicants::SortByDate(sorted_applicants);
    SortApplicants::SortByPoints(sorted_applicants);

    std::unordered_map<std::string, size_t> universities_max_students;
    for (const University& university : universities) {
        universities_max_students[university.name] = university.max_students;
    }

    for (const Applicant* applicant_ptr : sorted_applicants) {
        for (const std::string& uni_name : applicant_ptr->wish_list) {
            if (table[uni_name].size() < universities_max_students[uni_name]) {
                table[uni_name].push_back(&(applicant_ptr->student));
                break;
            }
        }
    }

    for (auto& [key, students] : table) {
        SortStudents::SortByDate(students);
        SortStudents::SortByNames(students);
    }

    return table;
}
