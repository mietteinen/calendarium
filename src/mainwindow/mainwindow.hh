#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QFontDatabase>
#include <QMainWindow>
#include <QLabel>
#include <QDebug>
#include <QIcon>

#include <src/gui/minicalendarwidget.hh>
#include <src/gui/datelistwidget.hh>
#include <src/utilities/utilities.hh>
#include <src/utilities/constants.hh>
#include <src/calendar/calendar.hh>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    /**
     * @brief Displays the calendar inside
     * the window.
     */
    void createCalendar(int year, int month);

protected:
    bool eventFilter(QObject* object, QEvent* event) override;

private slots:
    void changeMonth(int direction);
    void changeColorMode(bool darkMode);
    void openMiniCalendar(bool open);

private:
    Ui::MainWindow *ui;
    MiniCalendarWidget* miniCalendar;

    QFont titleFont_;
    QFont navigationFont_;

    QIcon calendarIcon_;
    QIcon colorModeIcon_;

    QString style_;

    Calendar* calendar_;

    int displayedYear_;
    int displayedMonth_;

    std::vector<QString> monthNames_;
};
#endif // MAINWINDOW_HH
