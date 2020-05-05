#include "drawing/database_manager.h"

#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/types.hpp>
#include <utility>

namespace drawing {

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

DatabaseManager::DatabaseManager() {
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

  document segment_object = SerializeSegment(segment);

  document filter;
  filter << "board_id" << board_id_;

  document update{};
  update << "$push" << open_document << "segments" << segment_object
         << close_document;
  boards.update_one(filter.view(), update.view());
}

auto DatabaseManager::RetrieveSegments() -> std::vector<Segment> {
  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_document;

  auto boards = client_["drawings"]["boards"];

  std::vector<Segment> segments;

  bsoncxx::stdx::optional<bsoncxx::document::value> current_board =
      boards.find_one(document{} << "board_id" << board_id_ << finalize);

  bsoncxx::document::view board_view = current_board->view();

  if (!board_view["segments"].operator bool()) {
    return segments;
  }

  bsoncxx::array::view segments_view = board_view["segments"].get_array();

  for (const bsoncxx::array::element& segment_element : segments_view) {
    Segment segment = DeserializeSegment(segment_element);
    segments.push_back(segment);
  }

  return segments;
}

}  // namespace drawing
