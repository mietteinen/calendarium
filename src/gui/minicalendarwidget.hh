#ifndef MINICALENDARWIDGET_HH
#define MINICALENDARWIDGET_HH

#include <QWidget>

namespace Ui {
class MiniCalendarWidget;
}

class MiniCalendarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MiniCalendarWidget(int initialYear, QWidget *parent = nullptr);
    ~MiniCalendarWidget();

protected:
    void focusOutEvent(QFocusEvent* event) override;

private:
    Ui::MiniCalendarWidget *ui;
    int currentYear_;
};

#endif // MINICALENDARWIDGET_HH
