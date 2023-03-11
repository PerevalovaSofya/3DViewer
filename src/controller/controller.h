#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include "../model/model.h"

class Controller {
 public:
  Controller(Model *model) : model_(model) {}
  /*_________________________parser___________________________*/
  void LoadObjectModel(const char *filename);
  /*__________________________getters__________________________*/
  int GetVerticesCount();
  int GetIndexCount();
  std::vector<double> GetVertices();
  std::vector<unsigned int> GetIndex();
  /*___________________affine_transformations__________________*/
  void Scale(double zoom);
  void MoveX(double xMov);
  void MoveY(double yMov);
  void MoveZ(double zMov);
  void RotationX(double xRot);
  void RotationY(double yRot);
  void RotationZ(double zRot);

 private:
  Model *model_;
};

#endif  // SRC_CONTROLLER_H_
