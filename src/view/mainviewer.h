#ifndef SRC_MAINVIEWER_H_
#define SRC_MAINVIEWER_H_

#include <QColorDialog>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QScopedPointer>
#include <QSlider>
#include <QTimer>

#include "../controller/controller.h"
#include "border.h"
#include "perspective.h"
#include "qgifimage.h"
#include "qgifimage_p.h"
#include "save.h"
#include "setting.h"
#include "vertex.h"
#include "widget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainViewer;
}
QT_END_NAMESPACE

class glView;
class MainViewer : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainViewer(Controller *controller, QWidget *parent = nullptr);
  ~MainViewer();

 public slots:
  void slotVertexColor(double red, double green, double blue);
  void slotBorderColor(double red, double green, double blue);
  void slotBorderThickness(double thickness_border);
  void slotBorderType(int type_border);
  void slotVertexThickness(double value);
  void slotVertexType(int value);
  void slotPerspectiveType(int value);
  void slotSaveType(int type_save);

 private slots:
  void on_file_open_clicked();
  void on_edit_background_clicked();
  void on_edit_perspective_clicked();
  void on_edit_vertex_clicked();
  void on_edit_border_clicked();
  void on_rotate_x_box_valueChanged(int value);
  void on_rotate_y_box_valueChanged(int value);
  void on_rotate_z_box_valueChanged(int value);
  void on_scale_valueChanged(double value);
  void on_shift_x_box_valueChanged(int value);
  void on_shift_y_box_valueChanged(int value);
  void on_shift_z_box_valueChanged(int value);
  void gif_slot();
  void on_save_file_clicked();

 private:
  const int shift_perspective_x_ = 685;
  const int shift_perspective_y_ = 670;
  const int shift_vertex_x_ = 228;
  const int shift_vertex_y_ = 585;
  const int shift_save_x_ = 915;
  const int shift_save_y_ = 630;
  double xMin_{}, xMax_{};
  double yMin_{}, yMax_{};
  double zMin_{}, zMax_{};
  unsigned int edges_counter_{};
  unsigned int vertices_counter_{};
  QTimer *timer_;
  QGifImage *gif_;
  Ui::MainViewer *ui;
  Controller *object_;
  QString file_name_;
  Save *window_save_;
  Vertex *window_vertex_;
  Border *window_border_;
  glView *window_glView_;
  Perspective *window_persp_;

  void PrintInfoAboutFile(QString FileName);
  void SetSlidersPosition();
  void SetOpenGLParameters();
};
#endif  // SRC_MAINVIEWER_H_
