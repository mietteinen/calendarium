#include "minicalendarwidget.hh"
#include "ui_minicalendarwidget.h"

MiniCalendarWidget::MiniCalendarWidget(int initialYear, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MiniCalendarWidget),
    currentYear_(initialYear) {

    ui->setupUi(this);
}

MiniCalendarWidget::~MiniCalendarWidget() {
    delete ui;
}

void MiniCalendarWidget::focusOutEvent(QFocusEvent *event)
{
    qDebug() << "We out here";
    Q_UNUSED(event);

    close();
    deleteLater();
}
