#include "minicalendarwidget.hh"
#include "ui_minicalendarwidget.h"

MiniCalendarWidget::MiniCalendarWidget(int initialYear,
                                       QString currentStyle,
                                       QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MiniCalendarWidget),
    currentYear_(initialYear),
    style_(currentStyle) {

    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);

    navigationFont_ = QFont("Karla SemiBold", 11);

    ui->currentYearLabel->setText(QString::number(currentYear_));
    ui->currentYearLabel->setFont(navigationFont_);
    ui->currentYearLabel->setAlignment(Qt::AlignCenter);

    ui->nextYearButton->setMaximumWidth(50);
    ui->nextYearButton->setMinimumWidth(50);
    ui->nextYearButton->setFont(navigationFont_);

    ui->prevYearButton->setMaximumWidth(50);
    ui->prevYearButton->setMinimumWidth(50);
    ui->prevYearButton->setFont(navigationFont_);

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
