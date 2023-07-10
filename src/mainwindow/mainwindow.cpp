#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    monthNames_ = {"", "January", "February", "March",
                   "April", "May", "June", "July", "August",
                   "September", "October", "November", "December"};

    QFontDatabase::addApplicationFont(":/fonts/LemonMilk.otf");
    QFont titleFont = QFont("LemonMilk", 24);

    std::pair<int, int> currentDate = util::getCurrentYearAndMonth();

    ui->yearSearchBox->setText(QString::number(currentDate.first));
    ui->monthSearchBox->setText(QString::number(currentDate.second));

    ui->yearSearchBox->setMaximumWidth(50);
    ui->monthSearchBox->setMaximumWidth(50);

    ui->searchButton->setMaximumWidth(100);

    ui->nextMonthButton->setMaximumWidth(30);
    ui->nextMonthButton->setMinimumHeight(30);

    ui->prevMonthButton->setMaximumWidth(30);
    ui->prevMonthButton->setMinimumHeight(30);

    ui->yearNumberLabel->setFont(titleFont);
    ui->monthNameLabel->setFont(titleFont);

    ui->yearLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    ui->monthLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    ui->yearNumberLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    // Connect next month button
    connect(ui->nextMonthButton, &QPushButton::clicked, this, [this]() {
        changeMonth(1);
    });

    // Connect previous month button
    connect(ui->prevMonthButton, &QPushButton::clicked, this, [this]() {
        changeMonth(-1);
    });
    connect(ui->searchButton, &QPushButton::clicked, this, [this]() {
        int year = ui->yearSearchBox->text().toInt();
        int month = ui->monthSearchBox->text().toInt();
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

        if (day == 0) {
            if (row == 5) {
                break;
            }
        } else {
            // Create a custom QFrame to allow for more styling.
            QFrame* frame = new QFrame;
            frame->setStyleSheet("QFrame { padding: 2px; "
                                          "border: 1px solid black; "
                                          "border-radius: 6px }");

            // Create a layout for the frame
            QHBoxLayout* frameLayout = new QHBoxLayout(frame);
            frameLayout->setContentsMargins(0, 0, 0, 0);

            // Create the DateListWidget and set it as the child of the frame.
            DateListWidget* date = new DateListWidget(day);
            date->setStyleSheet("border: none; background-color: transparent");

            frameLayout->addWidget(date);

            // Add the frame to the grid layout.
            ui->calendarGrid->addWidget(frame, row, col);
        }

        // Increment the row and column
        col++;
        if (col == 7) {
            col = 0;
            row++;
        }
    }
    ui->yearNumberLabel->setText(QString::number(year));
    ui->monthNameLabel->setText(monthNames_.at(month));
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

    ui->yearSearchBox->setText(QString::number(displayedYear_));
    ui->monthSearchBox->setText(QString::number(displayedMonth_));

    createCalendar(displayedYear_, displayedMonth_);
}

