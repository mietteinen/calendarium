#include <cmath>
#include <vector>

#ifndef CALENDAR_HH
#define CALENDAR_HH


class Calendar
{
public:
    Calendar(int year, int month);

    std::vector<int> getCalendarVector();

private:
    int year_;
    int month_;

    // Holds how many days each month has.
    // Index zero is zero to make indexing
    // the vector more intuitive.
    std::vector<int> monthDays_;

    // Holds the whole calendar, with zeros
    // in place of days from the previous or
    // upcoming month.
    std::vector<int> calendarVector_;

    // First day of the month, with the
    // number 1 being Monday and so on.
    int firstDay_;

    /**
     * @brief Finds what weekday is the
     * first day of the month. Monday is 1
     * and Sunday is 7.
     */
    void findFirstDay();

    /**
     * @brief Adds the dates to
     * calendarVector_.
     */
    void generateCalendar();

    /**
     * @brief Checks if the current year
     * is a leap year.
     * @return A boolean value (true if
     * the current year is a leap year).
     */
    bool isLeapYear() const;
};

#endif // CALENDAR_HH
