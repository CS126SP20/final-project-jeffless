// Copyright (c) 2020 Jeffrey Lin. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <drawing/segment.h>

#include <bsoncxx/json.hpp>
#include <catch2/catch.hpp>

using ci::Color;
using cinder::vec2;
using drawing::Segment;
using std::vector;

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::open_array;

TEST_CASE("Segment sanity check", "[constructor][AddPoint][GetPoints]") {
  Segment segment(Color::white());

  REQUIRE(segment.GetPoints().empty());

  SECTION("Add one point, check size correct") {
    segment.AddPoint(vec2(0, 0));
    REQUIRE(segment.GetPoints().size() == 1);
  }

  SECTION("Add two points, check size correct") {
    segment.AddPoint(vec2(0, 0));
    segment.AddPoint(vec2(1, 1));
    REQUIRE(segment.GetPoints().size() == 2);
  }

  SECTION("Add two points, check points correct") {
    vector<vec2> correct_points;
    correct_points.push_back(vec2(0, 0));
    correct_points.push_back(vec2(1, 1));

    segment.AddPoint(vec2(0, 0));
    segment.AddPoint(vec2(1, 1));

    REQUIRE(segment.GetPoints() == correct_points);
  }
}

TEST_CASE("Deserialize segment", "[DeserializeSegment][GetPoints][GetColor]") {
  std::ifstream file("assets/test_board.json");

  std::string board;
  file >> board;
  file.close();

  bsoncxx::stdx::string_view board_string(board);
  bsoncxx::document::value board_object = bsoncxx::from_json(board_string);

  // Get first (and only) segment for validation
  bsoncxx::array::element segment_element =
      board_object.view()["segments"].get_array().value[0];

  Segment deserialized_segment = drawing::DeserializeSegment(segment_element);

  SECTION("Deserialized segment color") {
    REQUIRE(deserialized_segment.GetColor() == Color::white());
  }

  SECTION("Deserialized segment points size") {
    REQUIRE(deserialized_segment.GetPoints().size() == 2);
  }

  SECTION("Deserialized segment points correct") {
    vector<vec2> correct_points;
    correct_points.push_back(vec2(0, 0));
    correct_points.push_back(vec2(1, 1));

    REQUIRE(deserialized_segment.GetPoints() == correct_points);
  }
}

TEST_CASE("Serialize segment", "[SerializeSegment][constructor][GetPoints][GetColor]") {
  Segment segment(Color::white());
  segment.AddPoint(vec2(0,0));
  segment.AddPoint(vec2(1,1));

  document serialized_segment = drawing::SerializeSegment(segment);
  std::string serialized_string = bsoncxx::to_json(serialized_segment);

  std::ifstream segment_file("assets/test_segment.json");

  std::string segment_string;
  segment_file >> segment_string;
  segment_file.close();

  REQUIRE(serialized_string == segment_string);
}
