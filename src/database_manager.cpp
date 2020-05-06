#include "drawing/database_manager.h"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/instance.hpp>

namespace drawing {

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;

DatabaseManager::DatabaseManager() {
  mongocxx::instance instance{};
  mongocxx::uri uri(kDatabaseUri);
  client_ = mongocxx::client(uri);
}

void DatabaseManager::OpenBoard(const std::string& board_id) {
  board_id_ = board_id;

  auto boards = client_["drawings"]["boards"];

  // Create and insert board document with board_id if it doesn't already exist
  document document{};
  document << "board_id" << board_id;
  boards.insert_one(document.view());
}

void DatabaseManager::InsertSegment(const Segment& segment) {
  auto boards = client_["drawings"]["boards"];

  document segment_object = SerializeSegment(segment);

  boards.update_one(
      make_document(kvp("board_id", board_id_)),
      make_document(
          kvp("$push", make_document(kvp("segments", segment_object)))));
}

void DatabaseManager::RemoveSegments() {
  auto boards = client_["drawings"]["boards"];

  boards.update_one(
      make_document(kvp("board_id", board_id_)),
      make_document(kvp("$unset", make_document(kvp("segments", "")))));
}

auto DatabaseManager::RetrieveSegments() -> std::vector<Segment> {
  auto boards = client_["drawings"]["boards"];

  std::vector<Segment> segments;

  bsoncxx::stdx::optional<bsoncxx::document::value> current_board =
      boards.find_one(document{} << "board_id" << board_id_ << finalize);
  bsoncxx::document::view board_view = current_board->view();

  // Nothing to serialize if the segments field doesn't exist
  if (!board_view["segments"]) {
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
