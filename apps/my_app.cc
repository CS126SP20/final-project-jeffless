// Copyright (c) 2020 Jeffrey Lin. All rights reserved.

#include "my_app.h"

#include "cinder/CinderImGui.h"
#include "cinder/gl/gl.h"

namespace myapp {

MyApp::MyApp() : state_{ProgramState::kLogin} {}

void MyApp::setup() {
  ImGui::Initialize();
  database_ = new drawing::DatabaseManager();
}

void MyApp::update() {
  if (state_ == ProgramState::kLogin) {
    ImGui::Begin("Login");

    ImGui::InputText("Board Name", board_name_, IM_ARRAYSIZE(board_name_));
    if (ImGui::Button("Start")) {
      state_ = ProgramState::kDrawing;
      database_->OpenBoard(board_name_);
    }

    ImGui::SetWindowFontScale(kScaleFactor);
    ImGui::End();
  } else {
    ImGui::Begin("Drawing Options");

    ImGui::ColorEdit3("Color", &segment_color_);

    if (ImGui::Button("Clear Board")) {
      database_->RemoveSegments();
      current_segment_ = nullptr;
    }

    ImGui::SetWindowFontScale(kScaleFactor);
    ImGui::End();

    ImGui::Begin("Boards");

    ImGui::InputText("Board Name", board_name_, IM_ARRAYSIZE(board_name_));
    if (ImGui::Button("Create Board")) {
      database_->OpenBoard(board_name_);
      current_segment_ = nullptr;
    }

    ImGui::Separator();
    ImGui::Text("");
    ImGui::Text("Join Existing Board");

    // Dynamically generate buttons for each board in the database
    for (const auto& board_item : database_->RetrieveBoardIds()) {
      if (ImGui::Button(board_item.c_str())) {
        database_->OpenBoard(board_item);
        current_segment_ = nullptr;
      }
    }

    ImGui::SetWindowFontScale(kScaleFactor);
    ImGui::End();
  }
}

void MyApp::draw() {
  cinder::gl::clear(ci::Color::gray(0.1f));
  if (state_ == ProgramState::kDrawing) {
    std::vector<drawing::Segment> segments = database_->RetrieveSegments();

    // Render current segment so the user can view it as it is being drawn, but
    // do not insert into database as it is not complete
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
