// Copyright (c) 2020 Jeffrey Lin. All rights reserved.

#ifndef FINALPROJECT_SEGMENT_H
#define FINALPROJECT_SEGMENT_H

#include <vector>
#include <cinder/app/App.h>


namespace drawing {

class Segment {
 public:
  explicit Segment(size_t color);
  void AddPoint(cinder::vec2 point);
  std::vector<cinder::vec2> GetPoints() const;
  size_t GetColor() const;
 private:
  std::vector<cinder::vec2> points_;
  size_t color_;
};

}  // namespace drawing

#endif  // FINALPROJECT_SEGMENT_H
