#ifndef MINICALENDARWIDGET_HH
#define MINICALENDARWIDGET_HH

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
    explicit MiniCalendarWidget(int initialYear, QWidget *parent = nullptr);
    ~MiniCalendarWidget();

private:
    Ui::MiniCalendarWidget *ui;

    QFont navigationFont_;
    int currentYear_;
};

#endif // MINICALENDARWIDGET_HH
