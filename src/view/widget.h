#ifndef SRC_WIDGET_H_
#define SRC_WIDGET_H_

#include <QMainWindow>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QQuaternion>

#include "../controller/controller.h"

class widget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit widget(QWidget *parent = nullptr);
  ~widget();
  using QOpenGLWidget::QOpenGLWidget;

  void SetBackgroundColor(float red, float green, float blue);
  void SetVertexColor(float red, float green, float blue);
  void SetEdgeColor(float red, float green, float blue);
  void GetModelObject(Controller *_object);
  void SetProjectionType(int projection_type);
  void SetLineWidth(int thickness_border);
  void SetLineType(int type_border);
  void SetPointType(int type_vertex);
  void SetPointSize(double thickness_vertex);
  void Scaling(double value);
  void ShiftX(int value);
  void ShiftY(int value);
  void ShiftZ(int value);
  void RotationX(int value);
  void RotationY(int value);
  void RotationZ(int value);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

  void InitShaders();
  void InitLine();
  void InitVer();
  void InitParametrs();
  void InitObject();
  void Draw();
  void SetGLProjection();
  QOpenGLShaderProgram program;

 private:
  const int shift_magic_ = 10;
  const int rotate_magic_ = 57;
  Controller *object_;
  QMatrix4x4 projection_;
  GLsizei lines_;
  GLfloat point_size_;
  QOpenGLBuffer array_buf_, index_buf_;
  GLclampf background_red_, background_green_, background_blue_;
  GLdouble edge_red_, edge_green_, edge_blue_;
  GLdouble vertex_red_, vertex_green_, vertex_blue_;
  float aspect_{};
  int line_type_, point_type_, projection_ortho_{};
  double line_width_{};
  double prev_scale_{};
  double prev_move_x_{}, prev_move_y_{}, prev_move_z_{};
  double prev_rotate_x_{}, prev_rotate_y_{}, prev_rotate_z_{};
};
#endif  // SRC_WIDGET_H_
