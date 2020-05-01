// Copyright (c) 2020 Jeffrey Lin. All rights reserved.

#include "drawing/segment.h"

namespace drawing {

Segment::Segment(const ci::Color& color) { color_ = color; }

void Segment::AddPoint(const cinder::vec2& point) { points_.push_back(point); }

auto Segment::GetPoints() const -> std::vector<cinder::vec2> { return points_; }

auto Segment::GetColor() const -> ci::Color { return color_; }
}  // namespace drawing