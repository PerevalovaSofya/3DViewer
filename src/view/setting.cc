#include "setting.h"

Setting::Setting() {
  setDefaultOpenGLParameters();
  configReadFile();
}

Setting::~Setting() { configWriteFile(); }

void Setting::setDefaultOpenGLParameters() {
  type_vertex_ = 0, thickness_vertex_ = 1.0;
  red_vertex_ = 1.0, green_vertex_ = 0.0, blue_vertex_ = 0.0;
  type_border_ = 0, thickness_border_ = 3.0;
  red_border_ = 0.0, green_border_ = 0.0, blue_border_ = 1.0;
  red_background_ = 0.7, green_background_ = 1.0, blue_background_ = 1.0;
  perspective_type_ = 1;
}

void Setting::configWriteFile() {
  std::ofstream fout;
  fout.open(f_str, std::ios_base::out | std::ios_base::trunc);
  if (fout.is_open()) {
    fout << type_vertex_ << " " << thickness_vertex_ << " " << red_vertex_
         << " " << green_vertex_ << " " << blue_vertex_ << " ";
    fout << type_border_ << " " << thickness_border_ << " " << red_border_
         << " " << green_border_ << " " << blue_border_ << " ";
    fout << red_background_ << " " << green_background_ << " "
         << blue_background_ << " " << perspective_type_;
    fout.close();
  }
}

void Setting::configReadFile() {
  std::ifstream fout;
  fout.open(f_str, std::ios_base::in);
  if (fout.is_open()) {
    fout >> type_vertex_ >> thickness_vertex_ >> red_vertex_ >> green_vertex_ >>
        blue_vertex_;
    fout >> type_border_ >> thickness_border_ >> red_border_ >> green_border_ >>
        blue_border_;
    fout >> red_background_ >> green_background_ >> blue_background_ >>
        perspective_type_;
    fout.close();
  }
}
