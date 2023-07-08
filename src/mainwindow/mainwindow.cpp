#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    std::pair<int, int> currentDate = util::getCurrentYearAndMonth();

    ui->yearBox->setText(QString::number(currentDate.first));
    ui->monthBox->setText(QString::number(currentDate.second));

    ui->yearBox->setMaximumWidth(50);
    ui->monthBox->setMaximumWidth(50);

    ui->nextMonthButton->setMaximumWidth(30);
    ui->nextMonthButton->setMinimumHeight(30);

    ui->prevMonthButton->setMaximumWidth(30);
    ui->prevMonthButton->setMinimumHeight(30);

    connect(ui->makerButton, &QPushButton::clicked,
                       this, &MainWindow::createCalendar_);

    createCalendar_();
}

MainWindow::~MainWindow() {
    delete calendar_;
    delete ui;
}

void MainWindow::createCalendar_() {

    delete calendar_;

    int year = ui->yearBox->text().toInt();
    int month = ui->monthBox->text().toInt();

    calendar_ = new Calendar(year, month);

    std::vector<int> calendarVector = calendar_->getCalendarVector();

    // Clear any existing widgets from the grid layout.
    QLayoutItem* item;
    while ((item = ui->calendarGrid->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Loop through the calendarVector and add the days to the grid layout
    int row = 0;
    int col = 0;
    for (int day : calendarVector) {

        DateListWidget* date = new DateListWidget(day);

        if (day == 0) {
            if (row == 5) {
                break;
            }
        } else {
            ui->calendarGrid->addWidget(date, row, col);
        }

        // Increment the row and column
        col++;
        if (col == 7) {
            col = 0;
            row++;
        }
    }
}

