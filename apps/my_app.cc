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
    if (ImGui::Button("Start")) {
      state_ = ProgramState::kDrawing;
      database_ = new drawing::DatabaseManager();
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
  cinder::gl::clear(ci::Color::gray(0.1f));
  if (state_ == ProgramState::kLogin) {
  } else {
    std::vector<drawing::Segment> segments = database_->RetrieveSegments();

    // Render current segment so the user can view it as it is being drawn
    if (current_segment_ != nullptr) {
      segments.push_back(*current_segment_);
    }

    for (const drawing::Segment& segment : segments) {
      ci::gl::color(segment.GetColor());
      cinder::gl::begin(GL_LINE_STRIP);
      for (const cinder::vec2& point : segment.GetPoints()) {
        cinder::gl::vertex(point);
      }
      cinder::gl::end();
    }
  }
}

void MyApp::mouseDown(cinder::app::MouseEvent event) {
  if (state_ == ProgramState::kDrawing) {
    current_segment_ = new drawing::Segment(color_);
  }
}

void MyApp::mouseUp(cinder::app::MouseEvent event) {
  if (state_ == ProgramState::kDrawing && current_segment_ != nullptr) {
    database_->InsertSegment(*current_segment_);
  }
}

void MyApp::mouseDrag(cinder::app::MouseEvent event) {
  if (state_ == ProgramState::kDrawing) {
    current_segment_->AddPoint(event.getPos());
  }
}

}  // namespace myapp
