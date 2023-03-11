#ifndef SRC_SETTING_H_
#define SRC_SETTING_H_

#include <fstream>
#include <iostream>

#include "QDir"
#include "QString"

class Setting {
 public:
  static Setting& Instance() {
    static Setting instance;
    return instance;
  }

  void configWriteFile();
  void configReadFile();
  void setDefaultOpenGLParameters();

  int& getTypeVertex() { return type_vertex_; }
  int& getTypeBorder() { return type_border_; }
  int& getTypePerspective() { return perspective_type_; }
  double& getThicknessVertex() { return thickness_vertex_; }
  double& getThicknessBorder() { return thickness_border_; }

  double& getRedVertex() { return red_vertex_; }
  double& getGreenVertex() { return green_vertex_; }
  double& getBlueVertex() { return blue_vertex_; }

  double& getRedBorder() { return red_border_; }
  double& getGreenBorder() { return green_border_; }
  double& getBlueBorder() { return blue_border_; }

  double& getRedBackground() { return red_background_; }
  double& getGreenBackground() { return green_background_; }
  double& getBlueBackground() { return blue_background_; }

 private:
  Setting();
  Setting(const Setting&);
  Setting& operator=(Setting&);
  ~Setting();

  int type_vertex_{};
  int type_border_{};
  int perspective_type_{};
  double thickness_vertex_{};
  double thickness_border_{};
  double red_vertex_{}, green_vertex_{}, blue_vertex_{};
  double red_border_{}, green_border_{}, blue_border_{};
  double red_background_{}, green_background_{}, blue_background_{};
  QString temp = QDir::homePath() + "/.config.conf";
  QByteArray f = temp.toLocal8Bit();
  char* f_str = f.data();
};

#endif  // SRC_SETTING_H_
