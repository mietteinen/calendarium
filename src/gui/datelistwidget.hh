#ifndef DATELISTWIDGET_HH
#define DATELISTWIDGET_HH

#include <QListWidget>
#include <QLabel>

class DateListWidget : public QListWidget {

public:
    DateListWidget(int dateNumber);

    /**
     * @brief To be done, for adding new events.
     */
    void addDate();
};

#endif // DATELISTWIDGET_HH
