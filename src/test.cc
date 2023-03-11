#include <gtest/gtest.h>

#include <vector>

#include "model/model.h"

TEST(affine, scale) {
  Model test_model;
  std::vector<double> result_model{2, -2, -2, 2, -2, 2, -2, -2, 2, -2, -2, -2,
                                   2, 2,  -2, 2, 2,  2, -2, 2,  2, -2, 2,  -2};
  const char* filename = "object/cube.obj";
  test_model.LoadObjModel(filename);
  test_model.Scale(2);

  for (size_t i = 0; i < test_model.GetVertices().size(); i++) {
    ASSERT_EQ(result_model[i], test_model.GetVertices()[i]);
  }
}

TEST(affine, MoveX) {
  Model test_model;
  std::vector<double> result_model{3, -1, -1, 3, -1, 1, 1, -1, 1, 1, -1, -1,
                                   3, 1,  -1, 3, 1,  1, 1, 1,  1, 1, 1,  -1};
  const char* filename = "object/cube.obj";
  test_model.LoadObjModel(filename);
  test_model.MoveX(2);

  for (size_t i = 0; i < test_model.GetVertices().size(); i++) {
    ASSERT_EQ(result_model[i], test_model.GetVertices()[i]);
  }
}

TEST(affine, MoveY) {
  Model test_model;
  std::vector<double> result_model{1, 1, -1, 1, 1, 1, -1, 1, 1, -1, 1, -1,
                                   1, 3, -1, 1, 3, 1, -1, 3, 1, -1, 3, -1};
  const char* filename = "object/cube.obj";
  test_model.LoadObjModel(filename);
  test_model.MoveY(2);

  for (size_t i = 0; i < test_model.GetVertices().size(); i++) {
    ASSERT_EQ(result_model[i], test_model.GetVertices()[i]);
  }
}

TEST(affine, MoveZ) {
  Model test_model;
  std::vector<double> result_model{1, -1, 1, 1, -1, 3, -1, -1, 3, -1, -1, 1,
                                   1, 1,  1, 1, 1,  3, -1, 1,  3, -1, 1,  1};
  const char* filename = "object/cube.obj";
  test_model.LoadObjModel(filename);
  test_model.MoveZ(2);

  for (size_t i = 0; i < test_model.GetVertices().size(); i++) {
    ASSERT_EQ(result_model[i], test_model.GetVertices()[i]);
  }
}

TEST(affine, RotationX) {
  Model test_model;
  std::vector<double> result_model{
      1,  1.3254442,   -0.49315059, 1,  -0.49315059, -1.3254442,
      -1, -0.49315059, -1.3254442,  -1, 1.3254442,   -0.49315059,
      1,  0.49315059,  1.3254442,   1,  -1.3254442,  0.49315059,
      -1, -1.3254442,  0.49315059,  -1, 0.49315059,  1.3254442};
  const char* filename = "object/cube.obj";
  test_model.LoadObjModel(filename);
  test_model.RotationX(2);

  for (size_t i = 0; i < test_model.GetVertices().size(); i++) {
    ASSERT_FLOAT_EQ(result_model[i], test_model.GetVertices()[i]);
  }
}

TEST(affine, RotationY) {
  Model test_model;
  std::vector<double> result_model{
      -1.3254442, -1, -0.49315059, 0.49315059,  -1, -1.3254442,
      1.3254442,  -1, 0.49315059,  -0.49315059, -1, 1.3254442,
      -1.3254442, 1,  -0.49315059, 0.49315059,  1,  -1.3254442,
      1.3254442,  1,  0.49315059,  -0.49315059, 1,  1.3254442};
  const char* filename = "object/cube.obj";
  test_model.LoadObjModel(filename);
  test_model.RotationY(2);

  for (size_t i = 0; i < test_model.GetVertices().size(); i++) {
    ASSERT_FLOAT_EQ(result_model[i], test_model.GetVertices()[i]);
  }
}

TEST(affine, RotationZ) {
  Model test_model;
  std::vector<double> result_model{
      0.49315059,  1.3254442,   -1, 0.49315059,  1.3254442,   1,
      1.3254442,   -0.49315059, 1,  1.3254442,   -0.49315059, -1,
      -1.3254442,  0.49315059,  -1, -1.3254442,  0.49315059,  1,
      -0.49315059, -1.3254442,  1,  -0.49315059, -1.3254442,  -1};
  const char* filename = "object/cube.obj";
  test_model.LoadObjModel(filename);
  test_model.RotationZ(2);

  for (size_t i = 0; i < test_model.GetVertices().size(); i++) {
    ASSERT_FLOAT_EQ(result_model[i], test_model.GetVertices()[i]);
  }
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
