#ifndef MINICALENDARWIDGET_HH
#define MINICALENDARWIDGET_HH

#include <QPushButton>
#include <QWidget>
#include <QPainter>
#include <QFont>

#include <src/utilities/constants.hh>

namespace Ui {
class MiniCalendarWidget;
}

class MiniCalendarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MiniCalendarWidget(int initialYear,
                                QString currentStyle,
                                QWidget *parent = nullptr);
    ~MiniCalendarWidget();

    void setStyling();

private:
    Ui::MiniCalendarWidget *ui;

    QFont navigationFont_;
    int currentYear_;
    QString style_;

    std::vector<QString> monthAbbreviations;

    void createMiniCalendar();
};

#endif // MINICALENDARWIDGET_HH
