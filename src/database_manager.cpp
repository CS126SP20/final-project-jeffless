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
  segment_object << "user_id" << user_id_;

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

}  // namespace drawing
