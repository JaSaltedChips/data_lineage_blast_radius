#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

/**
 * @brief Represents a single simulated change event in the lineage graph.
 */
struct ChangeEvent {
    /** @brief Node where the change originated. */
    std::string origin;
    /** @brief Human-readable timestamp when the event was recorded. */
    std::string timestamp;
    /** @brief Mapping of affected node name to shortest hop distance from origin. */
    std::unordered_map<std::string, int> affectedNodes;
};

/**
 * @brief Directed graph model for data lineage and impact analysis.
 *
 * Nodes represent datasets or processing stages. Directed edges represent
 * downstream dependencies. The class can simulate changes, record audit events,
 * and query which nodes are impacted by a given origin.
 */
class DataLineageGraph {
private:
    std::unordered_map<std::string, std::vector<std::string>> _graph;
    std::unordered_map<std::string, std::vector<std::size_t>> node_index;
    
    public:
    /**
     * @brief Chronological list of recorded change events.
     */
    std::vector<ChangeEvent> _auditLog;

    /**
     * @brief Adds a node to the lineage graph if it does not already exist.
     * @param node Unique node name.
     */
    void addNode(const std::string& node);

    /**
     * @brief Adds a directed dependency edge from one node to another.
     * @param from Upstream/source node.
     * @param to Downstream/dependent node.
     */
    void addEdge(const std::string& from, const std::string& to);

    /**
     * @brief Simulates a change at the origin node and records an audit event.
     * @param origin Node where the change starts.
     */
    void simulateChange(const std::string& origin);

    /**
     * @brief Prints a compact summary of all recorded audit events.
     */
    void printAuditLog();

    /**
     * @brief Prints all audit events that affected a specific node.
     * @param node Node to trace.
     */
    void traceNode(const std::string& node);

    /**
     * @brief Computes shortest downstream distance from origin to affected nodes.
     *
     * Uses breadth-first traversal of the dependency graph.
     * @param origin Start node for impact propagation.
     * @return Map of affected node name to shortest distance in hops.
     */
    std::unordered_map<std::string, int> computeBlastRadius(const std::string& origin);
};