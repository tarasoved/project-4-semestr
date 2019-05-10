#ifndef COORDINATE_OF_CALCULATED_POINT_H
#define COORDINATE_OF_CALCULATED_POINT_H

#include <QDialog>

namespace Ui {
class coordinate_of_calculated_point;
}

class coordinate_of_calculated_point : public QDialog
{
    Q_OBJECT

public:
    explicit coordinate_of_calculated_point(QWidget *parent = 0);
    ~coordinate_of_calculated_point();

private:
    Ui::coordinate_of_calculated_point *ui;
};

#endif // COORDINATE_OF_CALCULATED_POINT_H
