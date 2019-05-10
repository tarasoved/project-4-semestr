#include "coordinate_of_calculated_point.h"
#include "ui_coordinate_of_calculated_point.h"

coordinate_of_calculated_point::coordinate_of_calculated_point(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::coordinate_of_calculated_point)
{
    ui->setupUi(this);
}

coordinate_of_calculated_point::~coordinate_of_calculated_point()
{
    delete ui;
}
