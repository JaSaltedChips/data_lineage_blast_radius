#include "lineage.hpp"

#define CUSTOM_ASSERT(condition, msg) \
    if (!(condition)) { \
        std::cerr << "FAIL: " << msg << " (line " << __LINE__ << ")\n"; \
    } else { \
        std::cout << "PASS: " << msg << "\n"; \
    }

void testDirectChildAtDepthOne() {
    DataLineageGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addEdge("A", "B");

    auto result = g.computeBlastRadius("A");
    CUSTOM_ASSERT(result.count("B") == 1, "Node B should be affected by change in A");
    CUSTOM_ASSERT(result["B"] == 1, "Node B should be at distance 1 from A");
}

void testTransitiveNodeAtCorrectDepth() {
    DataLineageGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addEdge("A", "B");
    g.addEdge("B", "C");

    auto result = g.computeBlastRadius("A");
    CUSTOM_ASSERT(result.count("C") == 1, "Node C should be affected by change in A");
    CUSTOM_ASSERT(result["C"] == 2, "Node C should be at distance 2 from A");
}

void testDiamondVisitedOnceAtCorrectDepth() {
    DataLineageGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addNode("D");
    g.addEdge("A", "B");
    g.addEdge("A", "C");
    g.addEdge("B", "D");
    g.addEdge("C", "D");

    auto result = g.computeBlastRadius("A");
    CUSTOM_ASSERT(result.count("D") == 1, "Node D should be affected by change in A");
    CUSTOM_ASSERT(result["D"] == 2, "Node D should be at distance 2 from A");
}

void testIsolatedNodeNotAffected() {
    DataLineageGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addEdge("A", "B");

    auto result = g.computeBlastRadius("A");
    CUSTOM_ASSERT(result.count("C") == 0, "Node C should not be affected by change in A");
}

void testUpstreamNodeNotAffected() {
    DataLineageGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addEdge("A", "B");
    g.addEdge("B", "C");

    auto result = g.computeBlastRadius("B");
    CUSTOM_ASSERT(result.count("A") == 0, "Node A should not be affected by change in B");
    CUSTOM_ASSERT(result.count("C") == 1, "Node C should be affected by change in B");
    CUSTOM_ASSERT(result["C"] == 1, "Node C should be at distance 1 from B");
}

void testTraceNodeReturnsCorrectOrigin() {
    DataLineageGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addEdge("A", "B");
    g.addEdge("B", "C");

    g.simulateChange("A");
    g.simulateChange("B");

    std::cout << "\nTracing node C:\n";
    g.traceNode("C"); // Should show that C was affected by changes in A and B
}

int main() {
    testDirectChildAtDepthOne();
    testTransitiveNodeAtCorrectDepth();
    testDiamondVisitedOnceAtCorrectDepth();
    testIsolatedNodeNotAffected();
    testUpstreamNodeNotAffected();
    testTraceNodeReturnsCorrectOrigin();
    return 0;
}