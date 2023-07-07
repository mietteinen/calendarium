#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    std::pair<int, int> currentDate = util::getCurrentYearAndMonth();

    ui->yearBox->setText(QString::number(currentDate.first));
    ui->monthBox->setText(QString::number(currentDate.second));

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
        QLabel* label = new QLabel(QString::number(day));
        ui->calendarGrid->addWidget(label, row, col);

        // Increment the row and column
        col++;
        if (col == 7) {
            col = 0;
            row++;
        }
    }
}

