#include "controller.h"

/*_________________________parser___________________________*/
void Controller::LoadObjectModel(const char *filename) {
  model_->LoadObjModel(filename);
}
/*__________________________getters__________________________*/
int Controller::GetVerticesCount() { return model_->GetVerticesCount(); }
int Controller::GetIndexCount() { return model_->GetIndexCount(); }
std::vector<double> Controller::GetVertices() { return model_->GetVertices(); }
std::vector<unsigned int> Controller::GetIndex() { return model_->GetIndex(); }

/*___________________affine_transformations__________________*/
void Controller::Scale(double zoom) { model_->Scale(zoom); }
void Controller::MoveX(double zoom) { model_->MoveX(zoom); }
void Controller::MoveY(double zoom) { model_->MoveY(zoom); }
void Controller::MoveZ(double zoom) { model_->MoveZ(zoom); }
void Controller::RotationX(double zoom) { model_->RotationX(zoom); }
void Controller::RotationY(double zoom) { model_->RotationY(zoom); }
void Controller::RotationZ(double zoom) { model_->RotationZ(zoom); }
