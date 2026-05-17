#include "lineage.hpp"

int main() {
    DataLineageGraph g;
    g.addNode("exchange_feed");
    g.addNode("normalized_prices");
    g.addNode("risk_model");
    g.addNode("price_history");
    g.addNode("client_report");
    g.addEdge("exchange_feed",     "normalized_prices");
    g.addEdge("normalized_prices", "risk_model");
    g.addEdge("normalized_prices", "price_history");
    g.addEdge("risk_model",        "client_report");

    // Simulate some changes
    g.simulateChange("normalized_prices");
    g.simulateChange("exchange_feed");
    g.simulateChange("client_report");

    // Print audit log and trace a node
    g.printAuditLog();
    g.traceNode("client_report");

    return 0;
}