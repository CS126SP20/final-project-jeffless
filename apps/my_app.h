// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>

#include "drawing/database_manager.h"
#include "drawing/segment.h"

namespace myapp {

enum class ProgramState { kLogin, kDrawing };

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void mouseDown(cinder::app::MouseEvent event) override;
  void mouseUp(cinder::app::MouseEvent event) override;
  void mouseDrag(cinder::app::MouseEvent event) override;

 private:
  ProgramState state_;

  drawing::DatabaseManager *database_;
  char board_[32];
  char name_[32];

  //std::vector<drawing::Segment *> segments_;
  drawing::Segment *current_segment_;
  ci::Color color_ = ci::Color::white();
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
