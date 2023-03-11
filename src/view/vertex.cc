#include "vertex.h"

#include "ui_vertex.h"

Vertex::Vertex(QWidget *parent) : QDialog(parent), ui(new Ui::Vertex) {
  ui->setupUi(this);
}

Vertex::~Vertex() { delete ui; }

void Vertex::on_apply_vertex_clicked() { close(); }

void Vertex::on_color_vertex_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color.isValid()) {
    red_ = color.redF();
    green_ = color.greenF();
    blue_ = color.blueF();
    ui->color_vertex->setStyleSheet(QString(style_sheet_).arg(color.name()));
  }
  emit signalVertexColor(red_, green_, blue_);
}

void Vertex::on_thickness_vertex_valueChanged(double arg1) {
  thickness_vertex_ = arg1;
  emit signalVertexThickness(thickness_vertex_);
}

void Vertex::on_type_vertex_currentIndexChanged(int index) {
  type_vertex_ = index;
  emit signalVertexType(type_vertex_);
}

void Vertex::setVertexType(int value) {
  type_vertex_ = value;
  ui->type_vertex->setCurrentIndex(type_vertex_);
}

void Vertex::setVertexThickness(double value) {
  thickness_vertex_ = value;
  ui->thickness_vertex->setValue(thickness_vertex_);
}

void Vertex::setVertexColor(double red, double green, double blue) {
  color_vertex_.setRedF(red);
  color_vertex_.setGreenF(green);
  color_vertex_.setBlueF(blue);
  ui->color_vertex->setStyleSheet(
      QString(style_sheet_).arg(color_vertex_.name()));
}
