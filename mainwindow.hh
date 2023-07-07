#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QLabel>

#include <calendar.hh>
#include <utilities.hh>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Calendar* calendar_;

    /**
     * @brief Displays the calendar inside
     * the window.
     */
    void createCalendar_();
};
#endif // MAINWINDOW_HH
