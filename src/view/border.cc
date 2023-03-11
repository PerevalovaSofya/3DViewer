#include "border.h"

#include <QDebug>

#include "ui_border.h"

Border::Border(QWidget *parent) : QDialog(parent), ui(new Ui::Border) {
  ui->setupUi(this);
}

Border::~Border() { delete ui; }

void Border::on_apply_border_clicked() { hide(); }

void Border::on_color_border_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color.isValid()) {
    red_ = color.redF();
    green_ = color.greenF();
    blue_ = color.blueF();
    ui->color_border->setStyleSheet(QString(style_sheet_).arg(color.name()));
  }
  emit signalBorderColor(red_, green_, blue_);
}

void Border::on_thickness_border_valueChanged(double arg1) {
  thickness_border_ = arg1;
  emit signalBorderThickness(thickness_border_);
}

void Border::on_type_border_currentIndexChanged(int index) {
  type_border_ = index;
  emit signalBorderType(type_border_);
}

void Border::SetBorderType(int value) {
  type_border_ = value;
  ui->type_border->setCurrentIndex(type_border_);
}

void Border::SetBorderThickness(double value) {
  thickness_border_ = value;
  ui->thickness_border->setValue(thickness_border_);
}

void Border::SetBorderColor(double red, double green, double blue) {
  color_border_.setRedF(red);
  color_border_.setGreenF(green);
  color_border_.setBlueF(blue);
  ui->color_border->setStyleSheet(
      QString(style_sheet_).arg(color_border_.name()));
}
