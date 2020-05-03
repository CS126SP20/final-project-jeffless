#include "drawing/database_manager.h"

#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/types.hpp>
#include <utility>

namespace drawing {

using bsoncxx::builder::stream::array;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

DatabaseManager::DatabaseManager(const std::string& user_id) {
  user_id_ = user_id;

  mongocxx::instance instance{};
  mongocxx::uri uri("mongodb://localhost:27017");
  client_ = mongocxx::client(uri);
}

void DatabaseManager::OpenBoard(const std::string& board_id) {
  board_id_ = board_id;

  auto boards = client_["drawings"]["boards"];
  document document{};
  document << "board_id" << board_id;
  boards.insert_one(document.view());
}

void DatabaseManager::InsertSegment(const Segment& segment) {
  auto boards = client_["drawings"]["boards"];

  document segment_object{};

  document color_object{};
  color_object << "r" << segment.GetColor().r;
  color_object << "g" << segment.GetColor().g;
  color_object << "b" << segment.GetColor().b;
  segment_object << "color" << color_object;

  auto points = segment_object << "points" << open_array;
  for (const cinder::vec2& point : segment.GetPoints()) {
    document point_object{};
    point_object << "x" << point.x;
    point_object << "y" << point.y;
    points << point_object;
  }
  points << close_array;

  document filter;
  filter << "board_id" << board_id_;

  document update{};
  update << "$push" << open_document << "segments" << segment_object
         << close_document;
  boards.update_one(filter.view(), update.view());
}

auto DatabaseManager::RetrieveSegments() -> std::vector<Segment> {
  auto boards = client_["drawings"]["boards"];

  bsoncxx::stdx::optional<bsoncxx::document::value> current_board =
      boards.find_one(document{} << "board_id" << board_id_ << finalize);

  bsoncxx::document::view board_view = current_board->view();
  bsoncxx::array::view segments_view = board_view["segments"].get_array();

  std::vector<Segment> segments;
  for (const bsoncxx::array::element& segment_element : segments_view) {
    bsoncxx::document::element color = segment_element["color"];
    double r = color["r"].get_double();
    double g = color["g"].get_double();
    double b = color["b"].get_double();

    Segment segment(cinder::Color(r, g, b));

    bsoncxx::array::view points_view = segment_element["points"].get_array();
    for (const bsoncxx::array::element& point_element : points_view) {
      double x = point_element["x"].get_double();
      double y = point_element["y"].get_double();

      segment.AddPoint(cinder::vec2(x, y));
    }
    segments.push_back(segment);
  }

  return segments;
}

}  // namespace drawing
