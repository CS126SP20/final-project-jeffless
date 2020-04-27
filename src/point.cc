// Copyright (c) 2020 Jeffrey Lin. All rights reserved.

#include "drawing/point.h"

namespace drawing {

Point::Point(size_t x, size_t y) {
  x_ = x;
  y_ = y;
}

size_t Point::GetX() const { return x_; }

size_t Point::GetY() const { return y_; }

}  // namespace drawing