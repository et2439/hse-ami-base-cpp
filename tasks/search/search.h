#pragma once

#include <string_view>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <tuple>
#include <algorithm>

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count);