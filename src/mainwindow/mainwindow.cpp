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
    navigationFont_ = QFont("Karla SemiBold", 14);

    calendarIcon_ = QIcon(":/icons/icons/CM_BLACK.png");

    std::pair<int, int> currentDate = util::getCurrentYearAndMonth();

    ui->nextMonthButton->setMaximumWidth(50);
    ui->nextMonthButton->setMinimumWidth(50);
    ui->nextMonthButton->setMaximumHeight(50);
    ui->nextMonthButton->setMinimumHeight(50);
    ui->nextMonthButton->setFont(navigationFont_);

    ui->prevMonthButton->setMaximumWidth(50);
    ui->prevMonthButton->setMinimumWidth(50);
    ui->prevMonthButton->setMaximumHeight(50);
    ui->prevMonthButton->setMinimumHeight(50);
    ui->prevMonthButton->setFont(navigationFont_);

    ui->colorModeButton->setMaximumWidth(50);
    ui->colorModeButton->setMinimumWidth(50);
    ui->colorModeButton->setMaximumHeight(50);
    ui->colorModeButton->setMinimumHeight(50);

    ui->miniCalendarButton->setMaximumWidth(50);
    ui->miniCalendarButton->setMinimumWidth(50);
    ui->miniCalendarButton->setMaximumHeight(50);
    ui->miniCalendarButton->setMinimumHeight(50);
    ui->miniCalendarButton->setCheckable(true);

    // Set the icon for miniCalendar.
    ui->miniCalendarButton->setText("");
    ui->miniCalendarButton->setIcon(calendarIcon_);
    ui->miniCalendarButton->setIconSize(QSize(32, 32));

    ui->yearNumberLabel->setFont(titleFont_);
    ui->monthNameLabel->setFont(titleFont_);

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

    // Toggling dark and light mode.
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
                    ->mapToGlobal(QPoint(-250, ui->miniCalendarButton->height() - 10));
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
            frame->setStyleSheet("QFrame { padding: 4px; "
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

    createCalendar(displayedYear_, displayedMonth_);
}

void MainWindow::changeColorMode(bool darkMode) {

    if (darkMode) {
        setStyleSheet("QMainWindow {"
                      "background-color: " + Colors::darkMain + ";"
                      "}"
                      "QPushButton {"
                      "border: 1px solid black;"
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
        style_ = "dark";

    } else {
        setStyleSheet("QMainWindow {"
                      "background-color: " + Colors::lightMain + ";"
                      "border-color: " + Colors::primaryColor + ";"
                      "}"
                      "QPushButton {"
                      "border: 1px solid black;"
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
        style_ = "light";
    }
}

void MainWindow::openMiniCalendar() {

    // Check if miniCalendar is already open.
    if (miniCalendar != nullptr) return;

    // Create an instance of MiniCalendarWidget.
    miniCalendar = new MiniCalendarWidget(displayedYear_, style_, this, this);

    // Find the position of miniCalendarButton and place
    // miniCalendar under it.
    QPoint buttonPos = ui->miniCalendarButton
            ->mapToGlobal(QPoint(-250, ui->miniCalendarButton->height() - 10));
    miniCalendar->move(buttonPos);

    // Set window flags for miniCalendar.
    miniCalendar->setWindowFlags(Qt::Tool |
                                 Qt::FramelessWindowHint);

    connect(miniCalendar, &MiniCalendarWidget::monthButtonClicked,
                    this, &MainWindow::createCalendar);

    miniCalendar->show();
}

