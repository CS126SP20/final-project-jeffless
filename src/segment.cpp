// Copyright (c) 2020 Jeffrey Lin. All rights reserved.

#include "drawing/segment.h"

#include <bsoncxx/array/element.hpp>

namespace drawing {

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::close_array;

Segment::Segment(const ci::Color& color) { color_ = color; }

void Segment::AddPoint(const cinder::vec2& point) { points_.push_back(point); }

auto Segment::GetPoints() const -> std::vector<cinder::vec2> { return points_; }

auto Segment::GetColor() const -> ci::Color { return color_; }

auto DeserializeSegment(const bsoncxx::array::element& segment_element) -> Segment {
  bsoncxx::document::element color = segment_element["color"];
  double r = color["r"].get_double();
  double g = color["g"].get_double();
  double b = color["b"].get_double();

  Segment segment(cinder::Color(r, g, b));

  bsoncxx::array::view points_view = segment_element["points"].get_array();
  for (const bsoncxx::array::element& point_element : points_view) {
    double x = point_element["x"].get_double();
    double y = point_element["y"].get_double();

    segment.AddPoint(cinder::vec2(x, y));
  }

  return segment;
}

auto SerializeSegment(const Segment& segment) -> document {
  document segment_object{};

  document color_object{};
  color_object << "r" << segment.GetColor().r;
  color_object << "g" << segment.GetColor().g;
  color_object << "b" << segment.GetColor().b;
  segment_object << "color" << color_object;

  auto points = segment_object << "points" << open_array;
  for (const cinder::vec2& point : segment.GetPoints()) {
    document point_object{};
    point_object << "x" << point.x;
    point_object << "y" << point.y;
    points << point_object;
  }
  points << close_array;

  return segment_object;
}

}  // namespace drawing