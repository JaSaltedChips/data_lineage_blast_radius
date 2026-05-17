#include "utility.hpp"

void wait() {
#ifdef _WIN32
Sleep(1000);
#endif
}

std::string current_timestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::ctime(&t);
    std::string timestamp = ss.str();
    timestamp.pop_back(); // remove the newline character added by ctime
    return timestamp;
}