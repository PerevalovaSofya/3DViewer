#include "widget.h"

widget::widget(QWidget* parent)
    : QOpenGLWidget(parent), index_buf_(QOpenGLBuffer::IndexBuffer) {
  InitParametrs();
}

widget::~widget() {
  makeCurrent();
  doneCurrent();
  array_buf_.destroy();
  index_buf_.destroy();
}

void widget::initializeGL() {
  initializeOpenGLFunctions();
  InitParametrs();
  glLineStipple(1, 0x00F0);
  InitShaders();
  array_buf_.create();
  index_buf_.create();
}

void widget::InitParametrs() {
  prev_scale_ = 1;
  prev_move_x_ = 0;
  prev_move_y_ = 0;
  prev_move_z_ = 0;
  prev_rotate_x_ = 0;
  prev_rotate_y_ = 0;
  prev_rotate_z_ = 0;
  projection_ortho_ = 0;
  aspect_ = 0;
  line_type_ = 0;
  point_type_ = 0;
  line_width_ = 0;
}

void widget::InitShaders() {
  if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh"))
    close();
  if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                       ":/fshader.fsh"))
    close();
  if (!program.link()) close();
  if (!program.bind()) close();
}

void widget::resizeGL(int w, int h) {
  aspect_ = qreal(w) / qreal(h ? h : 1);
  SetGLProjection();
}

void widget::SetGLProjection() {
  projection_.setToIdentity();
  if (this->projection_ortho_ == 1) {
    projection_.ortho(-8, 8, -6, 6, -10, 10);
  } else {
    projection_.perspective(40, aspect_, 0.1f, 20.0f);
  }
}

void widget::paintGL() {
  glClearColor(background_red_, background_green_, background_blue_, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  QMatrix4x4 matrix;
  matrix.translate(-0.1, -0.1, -5.0);
  matrix.rotate(60, 0, 0, 0);
  matrix.scale(0.7);
  program.bind();
  program.setUniformValue("qt_ModelViewProjectionMatrix", projection_ * matrix);
  InitObject();
  Draw();
  program.release();
}

void widget::InitObject() {
  QVector<QVector3D> vertices1;
  std::vector<double> vertices = object_->GetVertices();
  std::vector<GLuint> indices = object_->GetIndex();
  for (int i = 0; i < vertices.size(); i += 3) {
    vertices1.push_back(
        QVector3D(vertices[i], vertices[i + 1], vertices[i + 2]));
  }
  array_buf_.bind();
  array_buf_.allocate(vertices1.data(), sizeof(QVector3D) * vertices1.size());
  array_buf_.release();

  index_buf_.bind();
  index_buf_.allocate(indices.data(), sizeof(GLuint) * indices.size());
  index_buf_.release();
  lines_ = indices.size();
}

void widget::Draw() {
  array_buf_.bind();
  program.bind();
  int offset = 0;
  int vertexLocation = program.attributeLocation("qt_Vertex");
  program.enableAttributeArray(vertexLocation);
  program.setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3,
                             sizeof(QVector3D));

  offset += sizeof(QVector3D);

  int texcoordLocation = program.attributeLocation("qt_MultiTexCoord0");
  program.enableAttributeArray(texcoordLocation);
  program.setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2,
                             sizeof(QVector3D));

  InitVer();
  index_buf_.bind();
  if (point_type_ != 0) {
    glDrawElements(GL_POINTS, lines_, GL_UNSIGNED_INT, 0);
  }
  InitLine();
  glDrawElements(GL_LINES, lines_, GL_UNSIGNED_INT, 0);
  array_buf_.release();
  index_buf_.release();
}

void widget::InitVer() {
  program.setUniformValue(
      "result_color", QVector4D(vertex_red_, vertex_green_, vertex_blue_, 1));
  glPointSize(point_size_ * 2);
  if (point_type_ == 1) {
    glEnable(GL_POINT_SMOOTH);
  } else if (point_type_ == 2) {
    glDisable(GL_POINT_SMOOTH);
  }
}

void widget::InitLine() {
  program.setUniformValue("result_color",
                          QVector4D(edge_red_, edge_green_, edge_blue_, 1));
  glLineWidth(line_width_);
  if (line_type_ == 1) {
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
}

void widget::SetBackgroundColor(float red, float green, float blue) {
  background_red_ = static_cast<GLclampf>(red);
  background_green_ = static_cast<GLclampf>(green);
  background_blue_ = static_cast<GLclampf>(blue);

  update();
}

void widget::SetVertexColor(float red, float green, float blue) {
  vertex_red_ = static_cast<GLclampf>(red);
  vertex_green_ = static_cast<GLclampf>(green);
  vertex_blue_ = static_cast<GLclampf>(blue);

  update();
}

void widget::SetEdgeColor(float red, float green, float blue) {
  edge_red_ = static_cast<GLclampf>(red);
  edge_green_ = static_cast<GLclampf>(green);
  edge_blue_ = static_cast<GLclampf>(blue);

  update();
}

void widget::GetModelObject(Controller* _object) {
  object_ = _object;
  update();
}

void widget::SetProjectionType(int projection_type) {
  projection_ortho_ = projection_type;
  SetGLProjection();
  update();
}
void widget::SetLineWidth(int thickness_border) {
  line_width_ = thickness_border;
  update();
}

void widget::SetLineType(int type_border) {
  line_type_ = type_border;
  update();
}

void widget::SetPointType(int type_vertex) {
  point_type_ = type_vertex;
  update();
}

void widget::SetPointSize(double thickness_vertex) {
  point_size_ = thickness_vertex;
  update();
}

void widget::Scaling(double value) {
  if (value != 0.0) {
    object_->Scale(value / prev_scale_);
    prev_scale_ = value;
  }
}

void widget::ShiftX(int value) {
  object_->MoveX((value - prev_move_x_) / shift_magic_);
  prev_move_x_ = value;
}

void widget::ShiftY(int value) {
  object_->MoveY((value - prev_move_y_) / shift_magic_);
  prev_move_y_ = value;
}

void widget::ShiftZ(int value) {
  object_->MoveZ((value - prev_move_z_) / shift_magic_);
  prev_move_z_ = value;
}

void widget::RotationX(int value) {
  object_->RotationX((value - prev_rotate_x_) / rotate_magic_);
  prev_rotate_x_ = value;
}

void widget::RotationY(int value) {
  object_->RotationY((value - prev_rotate_y_) / rotate_magic_);
  prev_rotate_y_ = value;
}

void widget::RotationZ(int value) {
  object_->RotationZ((value - prev_rotate_z_) / rotate_magic_);
  prev_rotate_z_ = value;
}
