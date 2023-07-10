#include "datelistwidget.hh"

DateListWidget::DateListWidget(int dateNumber) {
    QListWidgetItem* item = new QListWidgetItem(this);
    QLabel* dateLabel = new QLabel(QString::number(dateNumber));
    QListWidget::setItemWidget(item, dateLabel);

    item->setFlags(item->flags() | Qt::ItemIsSelectable);
    item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
}

void DateListWidget::addDate() {

}
