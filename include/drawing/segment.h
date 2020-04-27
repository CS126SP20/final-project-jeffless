// Copyright (c) 2020 Jeffrey Lin. All rights reserved.

#ifndef FINALPROJECT_SEGMENT_H
#define FINALPROJECT_SEGMENT_H

#include <vector>

#include "point.h"

namespace drawing {

class Segment {
 public:
  explicit Segment(size_t color);
  void AddPoint(size_t x, size_t y);
  std::vector<Point> GetPoints() const;
  size_t GetColor() const;
 private:
  std::vector<Point> points_;
  size_t color_;
};

}  // namespace drawing

#endif  // FINALPROJECT_SEGMENT_H
