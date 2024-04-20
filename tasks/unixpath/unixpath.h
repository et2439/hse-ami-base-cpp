#pragma once

#include <string>
#include <string_view>
#include <deque>

std::string NormalizePath(std::string_view current_working_dir, std::string_view path);
