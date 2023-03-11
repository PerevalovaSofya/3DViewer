#include "mainviewer.h"

#include <QDebug>
#include <fstream>
#include <iostream>

#include "ui_mainviewer.h"
#include "widget.h"

MainViewer::MainViewer(Controller* controller, QWidget* parent)
    : QMainWindow(parent), object_(controller), ui(new Ui::MainViewer) {
  ui->setupUi(this);
  ui->openGLWidget->GetModelObject(object_);
  ui->openGLWidget->SetBackgroundColor(Setting::Instance().getRedBackground(),
                                       Setting::Instance().getGreenBackground(),
                                       Setting::Instance().getBlueBackground());
}

MainViewer::~MainViewer() { delete ui; }

void MainViewer::on_file_open_clicked() {
  QString FileName = QFileDialog::getOpenFileName(
      this, "Open a file", QDir::homePath(), "Object (*.obj)");
  if (FileName.size() != 0) {
    QByteArray f = FileName.toLocal8Bit();
    char* f_str = f.data();
    object_->LoadObjectModel(f_str);
    PrintInfoAboutFile(FileName);
    SetOpenGLParameters();
    SetSlidersPosition();
    ui->openGLWidget->GetModelObject(object_);
  }
}

void MainViewer::PrintInfoAboutFile(QString FileName) {
  QString result_vertex = QString::fromLocal8Bit(
      std::to_string(object_->GetVerticesCount()).c_str());
  QString result_edge =
      QString::fromLocal8Bit(std::to_string(object_->GetIndexCount()).c_str());
  QStringList parts = FileName.split("/");
  QString lastBit = parts.at(parts.size() - 1);
  ui->count_vertex->setText(result_vertex);
  ui->count_border->setText(result_edge);
  ui->file_name->setText(lastBit);
}

void MainViewer::SetOpenGLParameters() {
  ui->openGLWidget->RotationX(0);
  ui->openGLWidget->RotationY(0);
  ui->openGLWidget->RotationZ(0);
  ui->openGLWidget->ShiftX(0);
  ui->openGLWidget->ShiftY(0);
  ui->openGLWidget->ShiftZ(0);
  ui->openGLWidget->Scaling(1);
  ui->openGLWidget->SetLineWidth(Setting::Instance().getThicknessBorder());
  ui->openGLWidget->SetLineType(Setting::Instance().getTypeBorder());
  ui->openGLWidget->SetEdgeColor(Setting::Instance().getRedBorder(),
                                 Setting::Instance().getGreenBorder(),
                                 Setting::Instance().getBlueBorder());
  ui->openGLWidget->SetPointSize(Setting::Instance().getThicknessVertex());
  ui->openGLWidget->SetPointType(Setting::Instance().getTypeVertex());
  ui->openGLWidget->SetVertexColor(Setting::Instance().getRedVertex(),
                                   Setting::Instance().getGreenVertex(),
                                   Setting::Instance().getBlueVertex());
  ui->openGLWidget->SetProjectionType(Setting::Instance().getTypePerspective());
  ui->openGLWidget->SetBackgroundColor(Setting::Instance().getRedBackground(),
                                       Setting::Instance().getGreenBackground(),
                                       Setting::Instance().getBlueBackground());
}

void MainViewer::SetSlidersPosition() {
  ui->shift_x_box->setValue(0);
  ui->shift_y_box->setValue(0);
  ui->shift_z_box->setValue(0);
  ui->scale->setValue(1);
  ui->rotate_x_box->setValue(0);
  ui->rotate_y_box->setValue(0);
  ui->rotate_z_box->setValue(0);
}

void MainViewer::on_edit_background_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color.isValid()) {
    Setting::Instance().getRedBackground() = color.redF();
    Setting::Instance().getGreenBackground() = color.greenF();
    Setting::Instance().getBlueBackground() = color.blueF();
    ui->openGLWidget->SetBackgroundColor(
        Setting::Instance().getRedBackground(),
        Setting::Instance().getGreenBackground(),
        Setting::Instance().getBlueBackground());
  }
}

void MainViewer::on_edit_perspective_clicked() {
  window_persp_ = new Perspective(this);

  window_persp_->setGeometry(this->x() + shift_perspective_x_,
                             this->y() + shift_perspective_y_,
                             window_persp_->width(), window_persp_->height());
  window_persp_->setModal(true);
  connect(window_persp_, &Perspective::signalPerspectiveType, this,
          &MainViewer::slotPerspectiveType);
  window_persp_->exec();
}

void MainViewer::on_edit_vertex_clicked() {
  window_vertex_ = new Vertex(this);
  window_vertex_->setGeometry(
      this->x() + shift_vertex_x_, this->y() + shift_vertex_y_,
      window_vertex_->width(), window_vertex_->height());
  window_vertex_->setModal(true);
  window_vertex_->setVertexType(Setting::Instance().getTypeVertex());
  window_vertex_->setVertexThickness(Setting::Instance().getThicknessVertex());
  window_vertex_->setVertexColor(Setting::Instance().getRedVertex(),
                                 Setting::Instance().getGreenVertex(),
                                 Setting::Instance().getBlueVertex());
  connect(window_vertex_, &Vertex::signalVertexColor, this,
          &MainViewer::slotVertexColor);
  connect(window_vertex_, &Vertex::signalVertexThickness, this,
          &MainViewer::slotVertexThickness);
  connect(window_vertex_, &Vertex::signalVertexType, this,
          &MainViewer::slotVertexType);
  window_vertex_->exec();
}

void MainViewer::on_edit_border_clicked() {
  window_border_ = new Border(this);
  window_border_->setGeometry(this->x(), this->y() + shift_vertex_y_,
                              window_border_->width(),
                              window_border_->height());
  window_border_->setModal(true);
  window_border_->SetBorderThickness(Setting::Instance().getThicknessBorder());
  window_border_->SetBorderType(Setting::Instance().getTypeBorder());
  window_border_->SetBorderColor(Setting::Instance().getRedBorder(),
                                 Setting::Instance().getGreenBorder(),
                                 Setting::Instance().getBlueBorder());
  connect(window_border_, &Border::signalBorderColor, this,
          &MainViewer::slotBorderColor);
  connect(window_border_, &Border::signalBorderThickness, this,
          &MainViewer::slotBorderThickness);
  connect(window_border_, &Border::signalBorderType, this,
          &MainViewer::slotBorderType);
  window_border_->exec();
}

void MainViewer::on_rotate_x_box_valueChanged(int value) {
  ui->openGLWidget->RotationX(value);
  ui->openGLWidget->update();
}

void MainViewer::on_rotate_y_box_valueChanged(int value) {
  ui->openGLWidget->RotationY(value);
  ui->openGLWidget->update();
}

void MainViewer::on_rotate_z_box_valueChanged(int value) {
  ui->openGLWidget->RotationZ(value);
  ui->openGLWidget->update();
}

void MainViewer::on_scale_valueChanged(double value) {
  ui->openGLWidget->Scaling(value);
  ui->openGLWidget->update();
}

void MainViewer::on_shift_x_box_valueChanged(int value) {
  ui->openGLWidget->ShiftX(value);
  ui->openGLWidget->update();
}

void MainViewer::on_shift_y_box_valueChanged(int value) {
  ui->openGLWidget->ShiftY(value);
  ui->openGLWidget->update();
}

void MainViewer::on_shift_z_box_valueChanged(int value) {
  ui->openGLWidget->ShiftZ(value);
  ui->openGLWidget->update();
}

void MainViewer::slotVertexColor(double red, double green, double blue) {
  Setting::Instance().getRedVertex() = red;
  Setting::Instance().getGreenVertex() = green;
  Setting::Instance().getBlueVertex() = blue;
  ui->openGLWidget->SetVertexColor(red, green, blue);
}

void MainViewer::slotBorderColor(double red, double green, double blue) {
  Setting::Instance().getRedBorder() = red;
  Setting::Instance().getGreenBorder() = green;
  Setting::Instance().getBlueBorder() = blue;
  ui->openGLWidget->SetEdgeColor(red, green, blue);
}

void MainViewer::slotBorderThickness(double value) {
  Setting::Instance().getThicknessBorder() = value;
  ui->openGLWidget->SetLineWidth(value);
}

void MainViewer::slotVertexThickness(double value) {
  Setting::Instance().getThicknessVertex() = value;
  ui->openGLWidget->SetPointSize(value);
}

void MainViewer::slotVertexType(int value) {
  Setting::Instance().getTypeVertex() = value;
  ui->openGLWidget->SetPointType(value);
}

void MainViewer::slotBorderType(int value) {
  Setting::Instance().getTypeBorder() = value;
  ui->openGLWidget->SetLineType(value);
}

void MainViewer::slotPerspectiveType(int value) {
  Setting::Instance().getTypePerspective() = value;
  ui->openGLWidget->SetProjectionType(value);
}

void MainViewer::slotSaveType(int type_save) {
  if (type_save == 0) {
    QImage image = ui->openGLWidget->grabFramebuffer();
    QString FileName = QFileDialog::getSaveFileName(
        this, "Open a file", QDir::homePath(), "BMP (*.bmp);; JPEG(*.jpeg)");
    if (!FileName.isNull() && !FileName.isEmpty()) {
      image.save(FileName);
    }
  } else {
    gif_ = new QGifImage(QSize(640, 480));
    gif_->setDefaultDelay(100);
    timer_ = new QTimer(this);
    timer_->start(100);
    connect(timer_, SIGNAL(timeout()), this, SLOT(gif_slot()));
  }
}

void MainViewer::gif_slot() {
  if (gif_->frameCount() < 50) {
    QImage image;
    image = ui->openGLWidget->grabFramebuffer();
    image =
        image.scaled(640, 480, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    gif_->addFrame(image);
  } else {
    QString dir = QFileDialog::getExistingDirectory(
        this, tr("Open Directory"), "/home",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QString FileName = ui->file_name->text();
    FileName.resize(FileName.count() - 4);
    gif_->save(dir + "/" + FileName + ".gif");
    timer_->stop();
    delete gif_;
  }
}

void MainViewer::on_save_file_clicked() {
  window_save_ = new Save(this);
  window_save_->setGeometry(this->x() + shift_save_x_,
                            this->y() + shift_save_y_, window_save_->width(),
                            window_save_->height());
  window_save_->setModal(true);
  connect(window_save_, &Save::signalSaveType, this, &MainViewer::slotSaveType);
  window_save_->exec();
}
