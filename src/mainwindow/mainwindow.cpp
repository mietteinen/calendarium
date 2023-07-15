#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    QApplication::instance()->installEventFilter(this);

    monthNames_ = {"", "January", "February", "March",
                   "April", "May", "June", "July", "August",
                   "September", "October", "November", "December"};

    titleFont_ = QFont("Karla SemiBold", 24);
    navigationFont_ = QFont("Karla SemiBold", 11);

    std::pair<int, int> currentDate = util::getCurrentYearAndMonth();

    ui->yearSearchBox->setText(QString::number(currentDate.first));
    ui->monthSearchBox->setText(QString::number(currentDate.second));

    ui->yearSearchBox->setMaximumWidth(50);
    ui->monthSearchBox->setMaximumWidth(50);

    ui->searchButton->setMaximumWidth(100);
    ui->searchButton->setMinimumWidth(100);

    ui->nextMonthButton->setMinimumWidth(30);
    ui->nextMonthButton->setMinimumHeight(30);
    ui->nextMonthButton->setFont(navigationFont_);

    ui->prevMonthButton->setMinimumWidth(30);
    ui->prevMonthButton->setMinimumHeight(30);
    ui->prevMonthButton->setFont(navigationFont_);

    ui->colorModeButton->setMaximumWidth(100);
    ui->colorModeButton->setMinimumWidth(100);

    ui->miniCalendarButton->setMaximumWidth(100);
    ui->miniCalendarButton->setMinimumWidth(100);
    ui->miniCalendarButton->setCheckable(true);

    ui->yearNumberLabel->setFont(titleFont_);
    ui->monthNameLabel->setFont(titleFont_);

    ui->yearLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    ui->monthLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    ui->yearNumberLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    ui->colorModeButton->setCheckable(true);

    // Moving to the next month via the arrow buttons.
    connect(ui->nextMonthButton, &QPushButton::clicked, this, [this]() {
        changeMonth(1);
    });

    // Moving to the previous month via the arrow buttons.
    connect(ui->prevMonthButton, &QPushButton::clicked, this, [this]() {
        changeMonth(-1);
    });

    connect(ui->searchButton, &QPushButton::clicked, this, [this]() {
        int year = ui->yearSearchBox->text().toInt();
        int month = ui->monthSearchBox->text().toInt();
        createCalendar(year, month);
    });

    connect(ui->colorModeButton, &QPushButton::toggled,
                           this, &MainWindow::changeColorMode);

    connect(ui->miniCalendarButton, &QPushButton::toggled,
                              this, &MainWindow::openMiniCalendar);

    displayedYear_ = currentDate.first;
    displayedMonth_ = currentDate.second;

    miniCalendar = nullptr;
    calendar_ = nullptr;
    createCalendar(displayedYear_,
                   displayedMonth_);

    changeColorMode(false);
}

MainWindow::~MainWindow() {
    delete calendar_;
    delete ui;
}

bool MainWindow::eventFilter(QObject *object, QEvent *event) {

    if (miniCalendar && event->type() == QEvent::MouseButtonPress) {

        QWidget* clickedWidget = qobject_cast<QWidget*>(object);
        if (clickedWidget) {

            // Check if the clicked widget is neither
            // the miniCalendar nor its descendant.
            if (clickedWidget != miniCalendar &&
                clickedWidget != ui->miniCalendarButton &&
                !miniCalendar->isAncestorOf(clickedWidget)) {

                // Delete the miniCalendar and set the pointer to nullptr
                delete miniCalendar;
                miniCalendar = nullptr;
            }
        }
    }

    if (event->type() == QEvent::Move) {

        if (miniCalendar != nullptr) {

            // Find the new position of the miniCalendarButton
            // and move miniCalendar accordingly.
            QPoint buttonPos = ui->miniCalendarButton
                    ->mapToGlobal(QPoint(0, ui->miniCalendarButton->height() - 10));
            miniCalendar->move(buttonPos);
        }
    }

    return QMainWindow::eventFilter(object, event);
}

void MainWindow::createCalendar(int year, int month) {

    if (calendar_) delete calendar_;

    calendar_ = new Calendar(year, month);

    std::vector<int> calendarVector = calendar_->getCalendarVector();

    // Clear any existing widgets from the grid layout.
    QLayoutItem* item;
    while ((item = ui->calendarGrid->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Loop through the calendarVector and add the days to the grid layout.
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
                                          "border-radius: 10px;"
                                          "background-color: " + Colors::primaryColor
                                          + " }");

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

void MainWindow::changeColorMode(bool darkMode) {

    if (darkMode) {
        setStyleSheet("QMainWindow {"
                      "background-color: " + Colors::darkMain + ";"
                      "}"
                      "QPushButton {"
                      "border: none;"
                      "border-radius: 6px;"
                      "background-color: " + Colors::accentColor + ";"
                      "color: black;"
                      "padding: 4px;"
                      "}"
                      "QPushButton:hover {"
                      "background-color: " + Colors::primaryColor + ";"
                      "}"
                      "QPushButton:pressed {"
                      "background-color: " + Colors::accentColor + ";"
                      "}"
                      "QLineEdit {"
                      "color: " + Colors::lightMain + ";"
                      "background-color: " + Colors::darkSecondary + ";"
                      "border-radius: 6px;"
                      "padding: 2px"
                      "}");
        ui->monthNameLabel->setStyleSheet("QLabel {"
                                          "color: " + Colors::lightMain + ";"
                                          "}");
        ui->yearNumberLabel->setStyleSheet("QLabel {"
                                           "color: " + Colors::lightMain + ";"
                                           "}");
        ui->monthLabel->setStyleSheet("QLabel {"
                                     "color: " + Colors::lightMain + ";"
                                     "}");
        ui->yearLabel->setStyleSheet("QLabel {"
                                     "color: " + Colors::lightMain + ";"
                                     "}");
        style_ = "dark";

    } else {
        setStyleSheet("QMainWindow {"
                      "background-color: " + Colors::lightMain + ";"
                      "border-color: " + Colors::primaryColor + ";"
                      "}"
                      "QPushButton {"
                      "border: none;"
                      "border-radius: 6px;"
                      "background-color: " + Colors::accentColor + ";"
                      "color: black;"
                      "padding: 4px;"
                      "}"
                      "QPushButton:hover {"
                      "background-color: " + Colors::primaryColor + ";"
                      "}"
                      "QPushButton:pressed {"
                      "background-color: " + Colors::accentColor + ";"
                      "}"
                      "QLineEdit {"
                      "color: " + Colors::darkMain + ";"
                      "background-color: " + Colors::lightSecondary + ";"
                      "border-radius: 6px;"
                      "padding: 2px"
                      "}");
        ui->monthNameLabel->setStyleSheet("QLabel {"
                                          "color: " + Colors::darkMain + ";"
                                          "}");
        ui->yearNumberLabel->setStyleSheet("QLabel {"
                                           "color: " + Colors::darkMain + ";"
                                           "}");
        ui->monthLabel->setStyleSheet("QLabel {"
                                     "color: " + Colors::darkMain + ";"
                                     "}");
        ui->yearLabel->setStyleSheet("QLabel {"
                                     "color: " + Colors::darkMain + ";"
                                     "}");
        style_ = "light";
    }
}

void MainWindow::openMiniCalendar() {

    // Check if miniCalendar is already open.
    if (miniCalendar != nullptr) return;

    // Create an instance of MiniCalendarWidget.
    miniCalendar = new MiniCalendarWidget(displayedYear_, style_, this);

    // Find the position of miniCalendarButton and place
    // miniCalendar under it.
    QPoint buttonPos = ui->miniCalendarButton
            ->mapToGlobal(QPoint(0, ui->miniCalendarButton->height() - 10));
    miniCalendar->move(buttonPos);

    // Set window flags for miniCalendar.
    miniCalendar->setWindowFlags(Qt::Tool |
                                 Qt::FramelessWindowHint);

    miniCalendar->show();
}

