// Copyright (c) 2020 Jeffrey Lin. All rights reserved.

#ifndef FINALPROJECT_DATABASE_MANAGER_H
#define FINALPROJECT_DATABASE_MANAGER_H

#include <mongocxx/client.hpp>
#include <vector>

#include "segment.h"

namespace drawing {

const std::string kDatabaseUri("mongodb://localhost:27017");

// Class to handle interactions with the MongoDB database
class DatabaseManager {
 public:
  DatabaseManager();

  // Load board internally with matching id for other methods to operate on
  void OpenBoard(const std::string& board_id);

  // Insert segment into current board
  void InsertSegment(const Segment& segment);

  // Clear all segments from the current board
  void RemoveSegments();

  // Deserialize all of the segments in the current board into a vector
  auto RetrieveSegments() -> std::vector<Segment>;

  // Retrieve all of the board ids
  auto RetrieveBoardIds() -> std::vector<std::string>;

 private:
  mongocxx::client client_;
  std::string board_id_;
};

}  // namespace drawing

#endif  // FINALPROJECT_DATABASE_MANAGER_H
