#include <cmath>

#ifndef CALENDAR_HH
#define CALENDAR_HH


class Calendar
{
public:
    Calendar(int year, int month);

    void createCalendar();

private:
    int year_;
    int month_;

    // First day of the month, with
    //
    int firstDay_;

    void findFirstDay();
};

#endif // CALENDAR_HH
