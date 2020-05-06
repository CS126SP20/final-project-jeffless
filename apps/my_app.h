// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>

#include "drawing/database_manager.h"
#include "drawing/segment.h"

namespace myapp {

const float kScaleFactor = 2.6f;

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
  // Keep track of current ProgramState
  ProgramState state_;

  // Pointer to DatabaseManager so it can be created later
  drawing::DatabaseManager *database_;

  // Pointer to current Segment being drawn
  drawing::Segment *current_segment_;

  // Object to store color stored by ImGui color picker
  ci::Color segment_color_ = ci::Color::white();

  // Object to store board id entered in login
  char board_name_[32];
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
