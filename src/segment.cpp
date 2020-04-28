// Copyright (c) 2020 Jeffrey Lin. All rights reserved.

#include "drawing/segment.h"


namespace drawing {

Segment::Segment(size_t color) { color_ = color; }

void Segment::AddPoint(cinder::vec2 point) {
  points_.push_back(point);
}

std::vector<cinder::vec2> Segment::GetPoints() const { return points_; }

size_t Segment::GetColor() const { return color_; }
}  // namespace drawing