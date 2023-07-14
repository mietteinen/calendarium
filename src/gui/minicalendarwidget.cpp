#include "minicalendarwidget.hh"
#include "ui_minicalendarwidget.h"

MiniCalendarWidget::MiniCalendarWidget(int initialYear, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MiniCalendarWidget),
    currentYear_(initialYear) {

    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);

    navigationFont_ = QFont("Karla SemiBold", 11);

    ui->currentYearLabel->setText(QString::number(currentYear_));
    ui->currentYearLabel->setFont(navigationFont_);
    ui->currentYearLabel->setAlignment(Qt::AlignCenter);

    ui->nextYearButton->setFont(navigationFont_);
    ui->prevYearButton->setFont(navigationFont_);

    setStyleSheet("QFrame {"
                  "background-color: " + Colors::lightMain + ";"
                  "padding: 10px;"
                  "border: 1px solid black;"
                  "border-radius: 10px"
                  "}"
                  "QLabel {"
                  "padding: 1px;"
                  "}");
}

MiniCalendarWidget::~MiniCalendarWidget() {
    delete ui;
}
