#include "lineage.hpp"
#include "utility.hpp"

void DataLineageGraph::addNode(const std::string& node) {
    if (_graph.find(node) == _graph.end()) {
        _graph[node] = std::vector<std::string>();
    }
}

void DataLineageGraph::addEdge(const std::string& from, const std::string& to) {
    _graph[from].push_back(to);
}

std::unordered_map<std::string, int> DataLineageGraph::computeBlastRadius(const std::string& origin)
{
    std::unordered_map<std::string, int> affected;
    affected[origin] = 0; // origin is distance 0 from itself
    std::queue<std::string> frontier;
    for (const auto& child: _graph.at(origin)) {
        frontier.push(child);
        affected[child] = 1; // direct child
    }

    while(!frontier.empty()) {
        std::string current = frontier.front();
        frontier.pop();

        for (const auto& child: _graph[current]) {
            if (affected.find(child) == affected.end()) { // not visited already
                affected[child] = affected[current] + 1; // indirect child
                frontier.push(child);
            }
        }
    }
    return affected;
}

void DataLineageGraph::simulateChange(const std::string& origin) {
    auto affected = computeBlastRadius(origin);
    _auditLog.push_back({origin, current_timestamp(), affected});
    
    std::size_t event_index = _auditLog.size() - 1;
    for (const auto& [node, depth] : affected) {
        _nodeIndex[node].push_back(event_index);
    }
    wait();
}

void DataLineageGraph::printAuditLog() {
std::cout << "\n=== AUDIT LOG ===\n";
if (_auditLog.empty()) {
    std::cout << "No events recorded.\n";
    return;
}
for (const auto& event : _auditLog) {
    std::cout << "[" << event.timestamp << "]  "
            << event.origin << " changed  ->  "
            << event.affectedNodes.size() << " nodes affected\n";
}
}

//   void trace_node(const std::string& node) {
//       std::cout << "\n=== TRACE: which events affected '" << node << "'? ===\n";
//       bool found = false;
//       for (const auto& event : _auditLog) {
//           if (event.affectedNodes.find(node) != event.affectedNodes.end()) {
//               std::cout << "[" << event.timestamp << "]  caused by change at '"
//                         << event.origin << "'  (depth "
//                         << event.affectedNodes.at(node) << ")\n";
//               found = true;
//           }
//       }
//       if (!found) std::cout << "No recorded events affected '" << node << "'.\n";
//   }

void DataLineageGraph::traceNode(const std::string& node) {
    std::cout << "\n=== TRACE: which events affected '" << node << "'? ===\n";
    if (_nodeIndex.find(node) == _nodeIndex.end()) {
            std::cout << "No recorded events affected '" << node << "'.\n";
            return;
    }
    for (const auto& event_index: _nodeIndex[node]) {
        const auto& event = _auditLog[event_index];
        std::cout << "Change to: " << event.origin << " at " << event.timestamp 
                    << " (distance: " << event.affectedNodes.at(node) << ")" << std::endl;
    }
}