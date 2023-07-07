#include <cmath>
#include <vector>

#ifndef CALENDAR_HH
#define CALENDAR_HH


class Calendar
{
public:
    Calendar(int year, int month);

private:
    int year_;
    int month_;

    std::vector<int> calendar_;
    std::vector<int> monthDays_;

    // First day of the month, with the
    // number 1 being Monday and so on.
    int firstDay_;

    void findFirstDay();
    void generateCalendar();

    bool isLeapYear(int year) const;
};

#endif // CALENDAR_HH
