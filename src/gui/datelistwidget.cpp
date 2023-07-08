#include "datelistwidget.hh"

DateListWidget::DateListWidget(int dateNumber) {
    QListWidgetItem* item = new QListWidgetItem(this);
    QLabel* dateLabel = new QLabel(QString::number(dateNumber));
    QListWidget::setItemWidget(item, dateLabel);
}

void DateListWidget::addDate() {

}
