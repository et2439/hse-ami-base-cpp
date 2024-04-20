#include "scorer.h"

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    Events sorted_events = events;
    std::sort(sorted_events.begin(), sorted_events.end(),
              [](const Event& lhs, const Event& rhs) { return lhs.time < rhs.time; });
    ScoreTable table;
    for (const auto& event : sorted_events) {
        if (event.time > score_time) {
            continue;
        }
        if (event.event_type == EventType::CheckSuccess) {
            table[event.student_name].insert(event.task_name);
        }
        if (event.event_type == EventType::CheckFailed) {
            table[event.student_name].erase(event.task_name);
        }
        if (event.event_type == EventType::MergeRequestOpen) {
            table[event.student_name].erase(event.task_name);
        }
        if (event.event_type == EventType::MergeRequestClosed) {
            table[event.student_name].insert(event.task_name);
        }
    }

    for (auto it = table.begin(); it != table.end(); ++it) {
        if (it->second.empty()) {
            it = table.erase(it);
        }
    }

    return table;
}
