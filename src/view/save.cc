#include "save.h"

#include "ui_save.h"

Save::Save(QWidget *parent) : QDialog(parent), ui(new Ui::Save) { ui->setupUi(this); }

Save::~Save() { delete ui; }

void Save::on_image_clicked() {
    close();
    emit signalSaveType(0);
}

void Save::on_gif_clicked() {
    emit signalSaveType(1);
    close();
}
