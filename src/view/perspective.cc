#include "perspective.h"

#include "ui_perspective.h"

Perspective::Perspective(QWidget *parent)
    : QDialog(parent), ui(new Ui::Perspective) {
  ui->setupUi(this);
}

Perspective::~Perspective() { delete ui; }

void Perspective::on_parallel_clicked() {
  close();
  emit signalPerspectiveType(1);
  close();
}

void Perspective::on_central_clicked() {
  emit signalPerspectiveType(0);
  close();
}
