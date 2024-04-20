#include "provinces.h"

int64_t CountPassports(const std::vector<int>& provinces) {
    if (provinces.size() < 2) {
        return 0;
    }

    int64_t count = 0;

    std::multiset<int64_t> set_provinces;
    for (const auto& province : provinces) {
        set_provinces.insert(static_cast<int64_t>(province));
    }

    while (set_provinces.size() > 1) {
        const auto min_province1 = set_provinces.begin();
        const auto min_province2 = std::next(set_provinces.begin());
        int64_t new_province = *min_province1 + *min_province2;
        count += new_province;
        set_provinces.insert(new_province);
        set_provinces.erase(min_province1);
        set_provinces.erase(min_province2);
    }
    return count;
}