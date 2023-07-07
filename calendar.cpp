#include "calendar.hh"

Calendar::Calendar(int year, int month)
    : year_(year), month_(month) {

    monthDays_ = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    findFirstDay();

    if (isLeapYear()) {
        monthDays_.at(2) = 29;
    }

    generateCalendar();
}

std::vector<int> Calendar::getCalendarVector() {

    return calendarVector_;
}

void Calendar::findFirstDay() {

    int modifier = (14 - month_) / 12;
    int yearModified = year_ - modifier;
    int monthModified = month_ + 12 * modifier - 2;

    // Using Gauss's algorithm to determine the day of the week.
    firstDay_ = (1 + yearModified + yearModified / 4
                   - yearModified / 100
                   + yearModified / 400
                   + (31 * monthModified) / 12) % 7;

    // Setting Sunday to 7 to make it more intuitive.
    if (firstDay_ == 0) {
        firstDay_ = 7;
    }
}

void Calendar::generateCalendar() {

   int daysInMonth;

   calendarVector_.clear();

   daysInMonth = monthDays_.at(month_);

   // Fill the calendar with the appropriate dates.
   int currentDay = 1 - (firstDay_ - 1);
   for (int i = 0; i < 42; ++i) {
       if (currentDay >= 1 && currentDay <= daysInMonth)
           calendarVector_.push_back(currentDay);
       else
           calendarVector_.push_back(0);

       currentDay++;
   }
}

bool Calendar::isLeapYear() const {
    return (year_ % 4 == 0 && year_ % 100 != 0) || (year_ % 400 == 0);
}
