#include "datelistwidget.hh"

DateListWidget::DateListWidget(int dateNumber) {

    dateNumberFont = QFont("Inconsolata Medium", 14);

    QListWidgetItem* item = new QListWidgetItem(this);
    QLabel* dateLabel = new QLabel(QString::number(dateNumber));

    QSize dateItemSize = item->sizeHint();
    dateItemSize.setHeight(30);
    dateItemSize.setWidth(0);
    item->setSizeHint(dateItemSize);

    dateLabel->setFixedHeight(30);
    dateLabel->setFont(dateNumberFont);

    QListWidget::setItemWidget(item, dateLabel);

    item->setFlags(item->flags() | Qt::ItemIsSelectable);
    item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
}

void DateListWidget::addItem() {


}
