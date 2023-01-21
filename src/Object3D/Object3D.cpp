//
// Created by co_cy on 20.01.23.
//

#include "Object3D.h"

#include <QFile>
#include <QTextStream>

namespace s_21 {

Object3D Object3D::FromFile(QString &filename) {
  QFile file(filename);
  // Валидация ошибок
  if (!file.exists()) {
    throw std::logic_error("Файл не существует!");
  }
  if (!file.open(QIODevice::ReadOnly)) {
    throw std::logic_error("Не удалось открыть файл!");
  }

  // Валидация Форматов
  if (filename.endsWith(".obj")) {
    return FromObjFile(file);
  }

  // Обработка не допустимых форматов
  throw std::logic_error("Неизвестный формат файла!");
}

Object3D Object3D::FromObjFile(QFile &file) {
  Object3D new_obj;

  QTextStream stream(&file);
  QString line;

  for (unsigned long long i = 0; stream.readLineInto(&line); ++i) {
    if (line.isEmpty()) continue;  // Проверка на пустые строки: "\n"

    QTextStream line_stream(&line, QIODevice::ReadOnly);
    QString tmp;

    line_stream >> tmp;  // Получаем тип в строке
    if (tmp == 'v') {  // обозначает вершину с параметрами x, y, z, [w]
      // Проходимся по всем 3-м координатам x -> y -> z, [w] - откидываем
      for (int col = 0; col < 3; ++col) {
        // Считываем одну из координат x / y / z в виде строки
        line_stream >> tmp;
        if (tmp.isEmpty()) {
          throw std::logic_error("Не удалось считать позицию(" +
                                 std::to_string(col) + ") вершины в строке " +
                                 std::to_string(i) +
                                 ". Возможно файл повреждён!");
        }

        bool ok;
        double pos = tmp.toDouble(&ok);
        if (!ok) {
          throw std::logic_error(
              "Не удалось преобразовать позицию(" + std::to_string(col) +
              ") вершины в число. Строка: " + std::to_string(i) +
              ". Возможно файл "
              "повреждён!");
        }

        new_obj.vertex_.push_back(pos);
      }
    } else if (tmp == 'f') {
      QVector<SizeType> face;

      while (!line_stream.atEnd()) {
        line_stream >> tmp;
        tmp = tmp.split('/')[0];
        bool ok;
        SizeType ind = tmp.toInt(&ok) - 1;
        if (!ok) {
          throw std::logic_error(
              "Не удалось преобразовать вершину в число. Строка: " +
              std::to_string(i) + ". Возможно файл повреждён!");
        }
        if (ind >= (new_obj.vertex_.size() / 3)) {
          throw std::logic_error(
              "Указана неверный индекс.  Строка: " + std::to_string(i) +
              ". Возможно файл повреждён!");
        }

        face.push_back(ind);
      }
      if (face.size() < 3) {
        throw std::logic_error(
            "Указано слишком мало вершин для полигона.  Строка: " +
            std::to_string(i) + ". Возможно файл повреждён!");
      }
      face.shrink_to_fit();
      new_obj.faces_.push_back(std::move(face));
    }
  }

  new_obj.vertex_.shrink_to_fit();
  new_obj.faces_.shrink_to_fit();
  return new_obj;
}

}  // namespace s_21