//
// Created by co_cy on 20.01.23.
//

#ifndef INC_3DVIEWER_SRC_OBJECT3D_OBJECT3D_H_
#define INC_3DVIEWER_SRC_OBJECT3D_OBJECT3D_H_

#include <gtest/gtest_prod.h>

#include <QFile>
#include <QVector>

namespace s_21 {

class Object3D {
 private:
  FRIEND_TEST(Object3DFromFile, simple_cube);
  FRIEND_TEST(Object3DFromFile, cube);

 public:
  using T = double;
  using SizeType = QVector<T>::size_type;

 public:
  Object3D() = default;
  static Object3D FromFile(QString &filename);

 private:
  static Object3D FromObjFile(QFile &file);

 private:
  QVector<T> vertex_;
  QVector<QVector<SizeType>> faces_;
};

}  // namespace s_21

#endif  // INC_3DVIEWER_SRC_OBJECT3D_OBJECT3D_H_
