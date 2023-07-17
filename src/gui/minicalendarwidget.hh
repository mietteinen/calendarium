#ifndef MINICALENDARWIDGET_HH
#define MINICALENDARWIDGET_HH

#include <algorithm>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QPainter>
#include <QFont>

#include <src/utilities/constants.hh>

class MainWindow;

namespace Ui {
class MiniCalendarWidget;
}

class MiniCalendarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MiniCalendarWidget(int initialYear,
                                QString currentStyle,
                                MainWindow* mainWindow,
                                QWidget* parent = nullptr);
    ~MiniCalendarWidget();

    void setStyling();

signals:
    void monthButtonClicked(int year, int month);

private slots:
    void onMonthChange();

private:
    Ui::MiniCalendarWidget *ui;
    MainWindow* mainWindow_;

    QFont navigationFont_;
    int currentYear_;
    QString style_;

    std::vector<QString> monthAbbreviations;

    void createMiniCalendar();
    void changeYear(int direction);
};

#endif // MINICALENDARWIDGET_HH
