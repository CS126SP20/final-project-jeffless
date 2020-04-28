// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <map>

#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() {}

void MyApp::setup() {}

void MyApp::update() {}

void MyApp::draw() {
  cinder::gl::clear(ci::Color::gray(0.1f));

  ci::gl::color(1.0f, 0.5f, 0.25f);

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

void MyApp::mouseDrag(cinder::app::MouseEvent event) {
  current_segment_->AddPoint(event.getPos());
}

}  // namespace myapp
