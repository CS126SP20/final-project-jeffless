// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>

#include "drawing/segment.h"

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void mouseDown(cinder::app::MouseEvent event) override;
  void mouseDrag(cinder::app::MouseEvent event) override;

 private:
  std::vector<drawing::Segment *> segments_;
  drawing::Segment *current_segment_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
