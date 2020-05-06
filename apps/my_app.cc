// Copyright (c) 2020 Jeffrey Lin. All rights reserved.

#include "my_app.h"

#include "cinder/CinderImGui.h"
#include "cinder/gl/gl.h"

namespace myapp {

MyApp::MyApp() : state_{ProgramState::kLogin} {}

void MyApp::setup() { ImGui::Initialize(); }

void MyApp::update() {
  if (state_ == ProgramState::kLogin) {
    ImGui::Begin("Login");

    ImGui::InputText("Board Name", board_name_, IM_ARRAYSIZE(board_name_));
    if (ImGui::Button("Start")) {
      state_ = ProgramState::kDrawing;
      database_ = new drawing::DatabaseManager();
      database_->OpenBoard(board_name_);
    }

    ImGui::SetWindowFontScale(kScaleFactor);
    ImGui::End();
  } else {
    ImGui::Begin("Color Picker");
    ImGui::ColorEdit3("Color", &segment_color_);
    ImGui::SetWindowFontScale(kScaleFactor);
    ImGui::End();

    ImGui::Begin("Options");

    if (ImGui::Button("Clear Board")) {
      database_->RemoveSegments();
      current_segment_ = nullptr;
    }

    ImGui::InputText("Board Name", board_name_, IM_ARRAYSIZE(board_name_));
    if (ImGui::Button("Start")) {
      database_->OpenBoard(board_name_);
      current_segment_ = nullptr;
    }

    ImGui::SetWindowFontScale(kScaleFactor);
    ImGui::End();
  }
}

void MyApp::draw() {
  cinder::gl::clear(ci::Color::gray(0.1f));
  if (state_ == ProgramState::kDrawing) {
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
    current_segment_ = new drawing::Segment(segment_color_);
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
