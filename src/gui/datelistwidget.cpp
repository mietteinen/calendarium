#include "datelistwidget.hh"

DateListWidget::DateListWidget(int dateNumber) {

    dateNumberFont = QFont("Inconsolata Medium", 11);

    QListWidgetItem* item = new QListWidgetItem(this);
    QLabel* dateLabel = new QLabel(QString::number(dateNumber));

    dateLabel->setFont(dateNumberFont);

    QListWidget::setItemWidget(item, dateLabel);

    item->setFlags(item->flags() | Qt::ItemIsSelectable);
    item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
}

void DateListWidget::addDate() {

}
