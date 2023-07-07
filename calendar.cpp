#include "calendar.hh"

Calendar::Calendar(int year, int month)
    : year_(year), month_(month) {

    monthDays_ = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    findFirstDay();

    if (isLeapYear(year_)) {
        monthDays_.at(2) = 29;
    }
}

void Calendar::findFirstDay() {

    /* The equation used for the calculation of
     * the first day of the month is from the
     * following link:
     *
     *      https://cs.uwaterloo.ca/~alopez-o/math-faq/node73.html
     */

    int month;
    int century;

    // Represents the year, for example 2023 -> 23.
    // January and February are from the previous year.
    int year;

    century = year_ / 100;
    year = year_ % 100;

    if (month_ <= 2) {
        if (month_ == 2) {
            month = 12;
        } else {
            month = 11;
        }
        year -= 1;

    } else {
        month = month_ - 2;
    }

    firstDay_ = static_cast<int>(1 + std::floor(2.6 * month)
              - 2 * century + year + std::floor(year / 4)
                                   + std::floor(century / 4)) % 7;
}

void Calendar::generateCalendar() {

   int daysInMonth;

   calendar_.clear();

   daysInMonth = monthDays_.at(year_);

   // Fill the calendar with the appropriate dates
   int currentDay = 1 - firstDay_;
   for (int i = 0; i < 42; ++i) {
       if (currentDay >= 1 && currentDay <= daysInMonth)
           calendar_.push_back(currentDay);
       else
           calendar_.push_back(0);

       currentDay++;
   }
}

bool Calendar::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
