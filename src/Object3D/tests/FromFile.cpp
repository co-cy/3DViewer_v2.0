//
// Created by co_cy on 20.01.23.
//

#include <gtest/gtest.h>

#include "Object3D.h"

namespace s_21 {

TEST(Object3DFromFile, simple_cube) {
  QString filename = "../data-samples/simple_cube.obj";
  Object3D obj = Object3D::FromFile(filename);

  ASSERT_EQ(obj.vertex_.size(), 24);
  QVector<Object3D::T> v = {-0.5, -0.5, 0.5,  0.5,  -0.5, 0.5, -0.5, 0.5,
                            0.5,  0.5,  0.5,  0.5,  -0.5, 0.5, -0.5, 0.5,
                            0.5,  -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5};
  for (int i = 0; i < 24; ++i) {
    EXPECT_DOUBLE_EQ(obj.vertex_[i], v[i]);
  }

  QVector<QVector<Object3D::SizeType>> f = {
      {1, 2, 3}, {3, 2, 4}, {3, 4, 5}, {5, 4, 6}, {5, 6, 7}, {7, 6, 8},
      {7, 8, 1}, {1, 8, 2}, {2, 8, 4}, {4, 8, 6}, {7, 1, 5}, {5, 1, 3}};
  ASSERT_EQ(obj.faces_.size(), 12);
  for (int i = 0; i < 12; ++i) {
    ASSERT_EQ(obj.faces_[i].size(), 3);
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(obj.faces_[i][j], f[i][j] - 1);
    }
  }
}

TEST(Object3DFromFile, cube) {
  QString filename = "../data-samples/cube.obj";
  Object3D obj = Object3D::FromFile(filename);

  ASSERT_EQ(obj.vertex_.size(), 24);
  QVector<Object3D::T> v = {-0.5, -0.5, 0.5,  0.5,  -0.5, 0.5, -0.5, 0.5,
                            0.5,  0.5,  0.5,  0.5,  -0.5, 0.5, -0.5, 0.5,
                            0.5,  -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5};
  for (int i = 0; i < 24; ++i) {
    EXPECT_DOUBLE_EQ(obj.vertex_[i], v[i]);
  }

  QVector<QVector<Object3D::SizeType>> f = {
      {1, 2, 3}, {3, 2, 4}, {3, 4, 5}, {5, 4, 6}, {5, 6, 7}, {7, 6, 8},
      {7, 8, 1}, {1, 8, 2}, {2, 8, 4}, {4, 8, 6}, {7, 1, 5}, {5, 1, 3}};
  ASSERT_EQ(obj.faces_.size(), 12);
  for (int i = 0; i < 12; ++i) {
    ASSERT_EQ(obj.faces_[i].size(), 3);
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(obj.faces_[i][j], f[i][j] - 1);
    }
  }
}

}  // namespace s_21
