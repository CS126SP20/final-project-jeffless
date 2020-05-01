// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include "cinder/CinderImGui.h"
#include "cinder/gl/gl.h"

namespace myapp {

MyApp::MyApp() : state_{ProgramState::kLogin} {}

void MyApp::setup() { ImGui::Initialize(); }

void MyApp::update() {
  if (state_ == ProgramState::kLogin) {
    ImGui::Begin("Login");
    ImGui::InputText("Board Name", board_, IM_ARRAYSIZE(board_));
    ImGui::InputText("User ID", name_, IM_ARRAYSIZE(name_));
    if (ImGui::Button("Start")) {
      state_ = ProgramState::kDrawing;
      database_  = new drawing::DatabaseManager(name_);
      database_->OpenBoard(board_);
    }
    ImGui::SetWindowFontScale(2.6f);
    ImGui::End();
  } else {
    ImGui::Begin("Color Picker");
    ImGui::ColorEdit3("Color", &color_);
    ImGui::SetWindowFontScale(2.6f);
    ImGui::End();
  }
}

void MyApp::draw() {
  if (state_ == ProgramState::kLogin) {
  } else {
    cinder::gl::clear(ci::Color::gray(0.1f));

    for (const drawing::Segment *segment : segments_) {
      ci::gl::color(segment->GetColor());
      cinder::gl::begin(GL_LINE_STRIP);
      for (const cinder::vec2 &point : segment->GetPoints()) {
        cinder::gl::vertex(point);
      }
      cinder::gl::end();
    }
  }
}

void MyApp::mouseDown(cinder::app::MouseEvent event) {
  if (state_ == ProgramState::kDrawing) {
    current_segment_ = new drawing::Segment(color_);
    segments_.push_back(current_segment_);
  }
}

void MyApp::mouseUp(cinder::app::MouseEvent event) {
  if (state_ == ProgramState::kDrawing && !segments_.empty()) {
    database_->InsertSegment(*current_segment_);
  }
}

void MyApp::mouseDrag(cinder::app::MouseEvent event) {
  if (state_ == ProgramState::kDrawing) {
    current_segment_->AddPoint(event.getPos());
  }
}

}  // namespace myapp
