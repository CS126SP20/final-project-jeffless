// Copyright (c) 2020 Jeffrey Lin. All rights reserved.

#include "drawing/segment.h"

namespace drawing {

Segment::Segment(size_t color) { color_ = color; }

void Segment::AddPoint(size_t x, size_t y) {
  Point p(x, y);
  points_.push_back(p);
}

std::vector<Point> Segment::GetPoints() const { return points_; }

size_t Segment::GetColor() const { return color_; }
}  // namespace drawing