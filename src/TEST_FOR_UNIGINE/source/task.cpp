// this file you need to fill
// этот файл вам нужно заполнить
#include "../include/task.h"
#define _USE_MATH_DEFINES
#include <cmath>

/*Функция нахождения угла отклонения между направлением видимости и осью ОХ в
 * градусах*/

float findAngle(float x, float y) {
  float angle = 0;
  if (x == 0.0) {
    angle = 90;
  } else if (y != 0) {
    angle = atan(x / y) * 180 / M_PI;
  }
  return angle;
}

/* Подсчет числа всех камер */

size_t countUnits(const std::vector<unit> &input_units) {
  size_t count = 0;
  for (auto i : input_units) {
    count++;
  }
  return count;
}

/* Функция нахождение сигнума скалярного произведения векторов */

int sgn(float x1, float y1, float x0, float y0) {
  int res = 0;
  if ((x1 * y0 - y1 * x0) < 0) {
    res = -1;
  } else if ((x1 * y0 - y1 * x0) > 0) {
    res = 1;
  }
  return res;
}

void Task::checkVisible(const std::vector<unit> &input_units,
                        std::vector<int> &result) {
  size_t count_units = countUnits(input_units);
  for (size_t i = 0; i < count_units; i++) {
    int count = 0;
    float angle_dist = findAngle(
        input_units[i].direction.x,
        input_units[i].direction.y); // Угол отклонения от оси ОХ в градусах
    float angle_edge[2];
    angle_edge[0] =
        angle_dist + input_units[i].fov_deg /
                         2; // Угол отклонения левой границы сектора от ОХ
    angle_edge[1] =
        angle_dist - input_units[i].fov_deg /
                         2; // Угол отклонения правой границы сектора от ОХ
    vec2 sector[2];         // массив векторов границ сектора
    int dir_x, dir_y;

    for (int k = 0; k < 2; k++) {
      dir_x = input_units[i].direction.x >= 0 ? 1 : -1;
      dir_y = input_units[i].direction.y >= 0 ? 1 : -1;
      sector[k].x =
          input_units[i].distance * cos(angle_edge[k] * M_PI / 180) * dir_x;
      sector[k].y =
          input_units[i].distance * sin(angle_edge[k] * M_PI / 180) * dir_y;
    }

    for (size_t j = 0; j < count_units; j++) {
      if (i == j) {
        continue;
      } else {
        vec2 point;
        point.x =
            ((input_units[j].position.x - input_units[i].position.x) * dir_x);
        point.y =
            ((input_units[j].position.y - input_units[i].position.y) * dir_y);
        if ((point.x >= 0 && point.y >= 0) &&
            (sqrt(point.x * point.x + point.y * point.y) <
             input_units[i].distance)) {
          if (sgn(sector[0].x, sector[0].y, point.x, point.y) ==
              sgn(point.x, point.y, sector[1].x, sector[1].y)) {
            count++;
          }
        }
      }
    }
    result.push_back(count);
  }
}
