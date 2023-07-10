#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QLabel>
#include <QFontDatabase>

#include <src/calendar/calendar.hh>
#include <src/utilities/utilities.hh>
#include <src/gui/datelistwidget.hh>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
     * @brief Displays the calendar inside
     * the window.
     */
    void createCalendar(int year, int month);
    void changeMonth(int direction);

private:
    Ui::MainWindow *ui;

    Calendar* calendar_;

    int displayedYear_;
    int displayedMonth_;

    std::vector<QString> monthNames_;
};
#endif // MAINWINDOW_HH
