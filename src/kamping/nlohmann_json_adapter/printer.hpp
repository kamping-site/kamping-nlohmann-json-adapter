#pragma once
#include <kamping/measurements/aggregated_tree_node.hpp>
#include <kamping/measurements/measurement_aggregation_definitions.hpp>
#include <nlohmann/json.hpp>

namespace kamping::measurements {
template <typename Duration = double>
class NLohmannJsonPrinter {
private:
  nlohmann::json j;

public:
  [[nodiscard]] auto json() const -> nlohmann::json const& { return j; }

  void print(kamping::measurements::AggregatedTreeNode<Duration> const& node) {
    j = {};
    print_impl(node, j);
  }

  void print_impl(kamping::measurements::AggregatedTreeNode<Duration> const& node,
                  nlohmann::json& j) {
    auto& j_local = j[node.name()];
    for (auto const& [operation, aggregated_data] : node.aggregated_data()) {
      auto& op_data = j_local[kamping::measurements::get_string(operation)];
      // op_data = aggregated_data;
      for (auto const& data_item : aggregated_data) {
        std::visit([&](auto& elem) { op_data.push_back(elem); }, data_item);
      }
    }
    for (auto const& child : node.children()) {
      if (child) {
        print_impl(*child, j_local);
      }
    }
  }
};

}  // namespace kamping::measurements
