

#ifndef FINALPROJECT_DATABASE_MANAGER_H
#define FINALPROJECT_DATABASE_MANAGER_H

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <map>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

#include "segment.h"

namespace drawing {

class DatabaseManager {
 public:
  explicit DatabaseManager(const std::string& user_id);
  void OpenBoard(const std::string& board_id);
  void InsertSegment(const Segment& segment);
 private:
  mongocxx::client client_;
  std::string user_id_;
  std::string board_id_;
};

}  // namespace drawing

#endif  // FINALPROJECT_DATABASE_MANAGER_H
