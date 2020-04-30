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

  document databuilder{};
  auto arrayBuilder = databuilder
      << "playload" << open_document


  document filter;
  filter << "board_id" << board_id_;

  /*document update;
  update << "$push" << open_document << "segments" << open_document << "$each"
  <<arr.view() << close_document << close_document;

  boards.update_one(filter.view(), update.view());*/

  /*document filter;
  filter << "board_id" << board_id_;

  document update;
  update << "$set" << open_document;

  update << "segments" << open_array;

  for (const cinder::vec2& point : segment.GetPoints()) {
    update << open_document;
    update << "user_id" << user_id_;
    array << "x" << point.x;
    array << "y" << point.y;
    //array << close_document;
  }

  array << close_array;
  update << close_document;
  boards.update_one(filter.view(), update.view());*/
}

}  // namespace drawing
