// Copyright (c) 2020 Jeffrey Lin. All rights reserved.

#ifndef FINALPROJECT_POINT_H
#define FINALPROJECT_POINT_H

namespace drawing {

class Point {
 public:
  Point(size_t x, size_t y);
  size_t GetX() const;
  size_t GetY() const;

 private:
  size_t x_;
  size_t y_;
};

}  // namespace drawing

#endif  // FINALPROJECT_POINT_H
