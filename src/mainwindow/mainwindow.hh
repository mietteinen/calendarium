#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QLabel>
#include <QFontDatabase>
#include <QDebug>

#include <src/calendar/calendar.hh>
#include <src/gui/datelistwidget.hh>
#include <src/gui/minicalendarwidget.hh>
#include <src/utilities/utilities.hh>
#include <src/utilities/constants.hh>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject* object, QEvent* event) override;

private slots:
    /**
     * @brief Displays the calendar inside
     * the window.
     */
    void createCalendar(int year, int month);
    void changeMonth(int direction);
    void changeColorMode(bool darkMode);
    void openMiniCalendar();

private:
    Ui::MainWindow *ui;

    QFont titleFont_;
    QFont navigationFont_;

    Calendar* calendar_;

    int displayedYear_;
    int displayedMonth_;

    std::vector<QString> monthNames_;
    MiniCalendarWidget* miniCalendar;
};
#endif // MAINWINDOW_HH
