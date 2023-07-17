#include "minicalendarwidget.hh"
#include "ui_minicalendarwidget.h"

MiniCalendarWidget::MiniCalendarWidget(int initialYear,
                                       QString currentStyle,
                                       MainWindow* mainWindow,
                                       QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MiniCalendarWidget),
    mainWindow_(mainWindow),
    currentYear_(initialYear),
    style_(currentStyle) {

    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);

    navigationFont_ = QFont("Karla SemiBold", 11);

    monthAbbreviations = {"", "Jan", "Feb", "Mar", "Apr",
                              "May", "Jun", "Jul", "Aug",
                              "Sep", "Oct", "Nov", "Dec"};

    ui->currentYearLabel->setText(QString::number(currentYear_));
    ui->currentYearLabel->setFont(navigationFont_);
    ui->currentYearLabel->setAlignment(Qt::AlignCenter);

    ui->nextYearButton->setMaximumWidth(50);
    ui->nextYearButton->setMinimumWidth(50);
    ui->nextYearButton->setFont(navigationFont_);

    ui->prevYearButton->setMaximumWidth(50);
    ui->prevYearButton->setMinimumWidth(50);
    ui->prevYearButton->setFont(navigationFont_);

    connect(ui->nextYearButton, &QPushButton::clicked, this, [this]() {
        changeYear(1);
    });

    connect(ui->prevYearButton, &QPushButton::clicked, this, [this]() {
        changeYear(-1);
    });

    createMiniCalendar();
    setStyling();
}

MiniCalendarWidget::~MiniCalendarWidget() {
    delete ui;
}

void MiniCalendarWidget::setStyling() {

    if (style_ == "light") {

        setStyleSheet("QFrame {"
                      "background-color: " + Colors::lightMain + ";"
                      "padding: 10px;"
                      "border: 1px solid " + Colors::darkMain + ";"
                      "border-radius: 10px"
                      "}"
                      "QLabel {"
                      "color: " + Colors::darkMain + ";"
                      "padding: 1px;"
                      "}");
    } else {

        setStyleSheet("QFrame {"
                      "background-color: " + Colors::darkMain + ";"
                      "padding: 10px;"
                      "border: 1px solid " + Colors::lightMain + ";"
                      "border-radius: 10px"
                      "}"
                      "QLabel {"
                      "color: " + Colors::lightMain + ";"
                      "padding: 1px;"
                      "}");
    }

}

void MiniCalendarWidget::onMonthChange() {

    QPushButton* clickedButton;
    QString buttonText;
    int index;

    clickedButton = qobject_cast<QPushButton*>(sender());

    if (!clickedButton) return;

    buttonText = clickedButton->text();

    auto it = std::find(monthAbbreviations.begin(),
                        monthAbbreviations.end(),
                        buttonText);

    if (it != monthAbbreviations.end()) {
        index = std::distance(monthAbbreviations.begin(), it);
        emit monthButtonClicked(currentYear_, index);
    }
}

void MiniCalendarWidget::createMiniCalendar() {

    int monthIndex = 1;
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            QString abbreviation = monthAbbreviations[monthIndex];

            QPushButton* button = new QPushButton();
            button->setMaximumHeight(30);
            button->setMinimumHeight(30);
            button->setText(abbreviation);

            connect(button, &QPushButton::clicked,
                      this, &MiniCalendarWidget::onMonthChange);

            ui->miniCalendarGrid->addWidget(button, row, col);

            monthIndex++;
        }
    }
}

void MiniCalendarWidget::changeYear(int direction) {

    currentYear_ += direction;
    ui->currentYearLabel->setText(QString::number(currentYear_));
}
