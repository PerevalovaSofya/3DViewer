#ifndef SRC_MODEL_H_
#define SRC_MODEL_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class Model {
 public:
  /*_________________________parser___________________________*/
  void LoadObjModel(const char *filename);

  /*__________________________getters__________________________*/
  int GetVerticesCount() { return vertices_count_; }
  int GetIndexCount() { return index_count_; }
  std::vector<double> GetVertices() { return vertices_; }
  std::vector<unsigned int> GetIndex() { return index_; }

  /*___________________affine_transformations__________________*/
  void Scale(double zoom);
  void MoveX(double xMov);
  void MoveY(double yMov);
  void MoveZ(double zMov);
  void RotationX(double xRot);
  void RotationY(double yRot);
  void RotationZ(double zRot);

 private:
  int vertices_count_{};
  int index_count_{};
  std::vector<double> vertices_{};     // v
  std::vector<unsigned int> index_{};  // f
};

#endif  // SRC_MODEL_H_
