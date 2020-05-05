// Copyright (c) 2020 Jeffrey Lin. All rights reserved.

#ifndef FINALPROJECT_SEGMENT_H
#define FINALPROJECT_SEGMENT_H

#include <cinder/app/App.h>

#include <bsoncxx/builder/stream/document.hpp>
#include <vector>

namespace drawing {

using bsoncxx::builder::stream::document;

class Segment {
 public:
  explicit Segment(const ci::Color& color);
  void AddPoint(const cinder::vec2& point);
  auto GetPoints() const -> std::vector<cinder::vec2>;
  auto GetColor() const -> ci::Color;

 private:
  std::vector<cinder::vec2> points_;
  ci::Color color_;
};

auto DeserializeSegment(const bsoncxx::array::element& segment_element)
    -> Segment;
auto SerializeSegment(const Segment& segment) -> document;

}  // namespace drawing

#endif  // FINALPROJECT_SEGMENT_H
