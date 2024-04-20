#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string path_str = static_cast<std::string>(path);
    std::deque<std::string> dirs;
    if (path_str.empty()) {
        return "/";
    }
    if (path_str[0] != '/') {
        path_str = static_cast<std::string>(current_working_dir) + "/" + path_str;
    }
    for (size_t i = 0; i < path_str.size(); ++i) {
        if (path_str[i] == '/') {
            continue;
        }
        std::string dir;
        while (i < path_str.size() && path_str[i] != '/') {
            dir += path_str[i];
            ++i;
        }
        if (dir == "..") {
            if (!dirs.empty()) {
                dirs.pop_back();
            }
        } else if (dir != ".") {
            dirs.push_back(dir);
        }
    }
    path_str = "";
    for (const auto& dir : dirs) {
        path_str += "/" + dir;
    }
    return path_str.empty() ? "/" : path_str;
}
