#include "utilities.hh"

#include <chrono>
#include <ctime>

namespace util {

std::pair<int, int> getCurrentYearAndMonth() {

    std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm* localTime = std::localtime(&currentTime);

    int currentYear = localTime->tm_year + 1900;
    int currentMonth = localTime->tm_mon + 1;

    return std::make_pair(currentYear, currentMonth);
}

} // namespace util
