#include "model.h"

#include <cmath>

/*______________________parser______________________*/
void Model::LoadObjModel(const char *filename) {
  vertices_.clear();
  index_.clear();
  vertices_count_ = 0;
  index_count_ = 0;
  std::ifstream ifs(filename, std::ios::in);
  if (!ifs.bad()) {
    std::string line;
    while (ifs >> line) {
      if (line[0] == 'v' && line.size() == 1) {
        double x, y, z;
        ifs >> x >> y >> z;
        vertices_.push_back(x);
        vertices_.push_back(y);
        vertices_.push_back(z);
        ++vertices_count_;
      }
      while (line[0] == 'f' && line.size() == 1) {
        ifs >> line;
        double first_index;
        first_index = std::stod(line);
        index_.push_back(first_index - 1);
        ifs >> line;
        ++index_count_;
        while (line[0] != 'f' && isdigit(line[0])) {
          double tmp_index = std::stod(line);
          index_.push_back((int)tmp_index - 1);
          index_.push_back((int)tmp_index - 1);
          if (ifs.eof()) break;
          ifs >> line;
          ++index_count_;
        }
        index_.push_back((int)first_index - 1);
      }
    }
    ifs.close();
  }
}
/*___________________affine_transformations___________________*/
void Model::Scale(double zoom) {
  for (size_t i = 0; i < vertices_.size(); i++) {
    vertices_[i] = vertices_[i] * zoom;
  }
}

void Model::MoveX(double xMov) {
  for (size_t i = 0; i < vertices_.size(); i += 3) {
    vertices_[i] = vertices_[i] + xMov;
  }
}

void Model::MoveY(double yMov) {
  for (size_t i = 1; i < vertices_.size(); i += 3) {
    vertices_[i] = vertices_[i] + yMov;
  }
}

void Model::MoveZ(double zMov) {
  for (size_t i = 2; i < vertices_.size(); i += 3) {
    vertices_[i] = vertices_[i] + zMov;
  }
}

void Model::RotationX(double xRot) {
  for (size_t i = 1; i < vertices_.size(); i += 3) {
    double temp_y = vertices_[i];
    double temp_z = vertices_[i + 1];
    vertices_[i] = cos(xRot) * temp_y - sin(xRot) * temp_z;
    vertices_[i + 1] = sin(xRot) * temp_y + cos(xRot) * temp_z;
  }
}

void Model::RotationY(double yRot) {
  for (size_t i = 0; i < vertices_.size(); i += 3) {
    double temp_x = vertices_[i];
    double temp_z = vertices_[i + 2];
    vertices_[i] = cos(yRot) * temp_x + sin(yRot) * temp_z;
    vertices_[i + 2] = (-1) * sin(yRot) * temp_x + cos(yRot) * temp_z;
  }
}

void Model::RotationZ(double zRot) {
  for (size_t i = 0; i < vertices_.size(); i += 3) {
    double temp_x = vertices_[i];
    double temp_y = vertices_[i + 1];
    vertices_[i] = cos(zRot) * temp_x - sin(zRot) * temp_y;
    vertices_[i + 1] = sin(zRot) * temp_x + cos(zRot) * temp_y;
  }
}
