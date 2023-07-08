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

    // Connect next month button
    connect(ui->nextMonthButton, &QPushButton::clicked, this, [this]() {
        changeMonth(1);
    });

    // Connect previous month button
    connect(ui->prevMonthButton, &QPushButton::clicked, this, [this]() {
        changeMonth(-1);
    });
    connect(ui->makerButton, &QPushButton::clicked, this, [this]() {
        int year = ui->yearBox->text().toInt();
        int month = ui->monthBox->text().toInt();
        createCalendar(year, month);
    });

    displayedYear_ = currentDate.first;
    displayedMonth_ = currentDate.second;

    createCalendar(displayedYear_,
                   displayedMonth_);
}

MainWindow::~MainWindow() {
    delete calendar_;
    delete ui;
}

void MainWindow::createCalendar(int year, int month) {

    delete calendar_;

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

void MainWindow::changeMonth(int direction) {

    displayedMonth_ += direction;

    if (displayedMonth_ > 12) {
        displayedYear_ += displayedMonth_ / 12;
        displayedMonth_ = displayedMonth_ % 12;

    } else if (displayedMonth_ < 1) {
        displayedYear_ += (displayedMonth_ - 12) / 12;
        displayedMonth_ = (displayedMonth_ + 11) % 12 + 1;
    }

    ui->yearBox->setText(QString::number(displayedYear_));
    ui->monthBox->setText(QString::number(displayedMonth_));

    createCalendar(displayedYear_, displayedMonth_);
}

