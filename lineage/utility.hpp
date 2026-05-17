#include <chrono>
#include <ctime>
#include <sstream>
#ifdef _WIN32
#include <windows.h>
#endif

/**
 * @brief Returns the current system time as a human-readable string.
 * @return Current timestamp formatted for logging output.
 */
std::string current_timestamp();

/**
 * @brief Pauses execution for a short fixed interval.
 */
void wait();