#include "tests_checking.h"

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> ordered_deque;
    for (size_t i = 0; i < student_actions.size(); ++i) {
        if (student_actions[i].side == Side::Top) {
            ordered_deque.push_front(student_actions[i].name);
        }
        if (student_actions[i].side == Side::Bottom) {
            ordered_deque.push_back(student_actions[i].name);
        }
    }
    std::vector<std::string> result;
    for (size_t i = 0; i < queries.size(); ++i) {
        result.push_back(ordered_deque[queries[i] - 1]);
    }
    return result;
}
