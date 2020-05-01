// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include "cinder/CinderImGui.h"
#include "cinder/gl/gl.h"

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() : database_("jeff") {}

void MyApp::setup() {
  database_.OpenBoard("testing2");
  ImGui::Initialize();
}

void MyApp::update() {
  ImGui::Begin("Color Picker");
  ImGui::Separator();
  ImGui::ColorEdit3("Color", &color_);
  ImGui::SetWindowFontScale(1.8);
  ImGui::End();
}

void MyApp::draw() {
  cinder::gl::clear(ci::Color::gray(0.1f));

  ci::gl::color(color_);

  for (const drawing::Segment *segment : segments_) {
    cinder::gl::begin(GL_LINE_STRIP);
    for (const cinder::vec2 &point : segment->GetPoints()) {
      cinder::gl::vertex(point);
    }
    cinder::gl::end();
  }
}

void MyApp::mouseDown(cinder::app::MouseEvent event) {
  current_segment_ = new drawing::Segment(1);
  segments_.push_back(current_segment_);
}
void MyApp::mouseUp(cinder::app::MouseEvent event) {
  if (!segments_.empty()) {
    database_.InsertSegment(*current_segment_);
  }
}

void MyApp::mouseDrag(cinder::app::MouseEvent event) {
  current_segment_->AddPoint(event.getPos());
}

}  // namespace myapp
