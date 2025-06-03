//
// Created by AleXutzZu on 22/05/2025.
//

#ifndef WORDLADDER_GRAPH_H
#define WORDLADDER_GRAPH_H

#include <vector>
#include <map>
#include <unordered_set>
#include <stdexcept>
#include <queue>

template<typename T>
class Graph {
private:
    unsigned int nodes = 0;
    std::vector<std::unordered_set<unsigned int>> adj;
    std::map<T, unsigned int> nodeIds;
    std::map<unsigned int, T> reverseNodeIds;
public:
    Graph() = default;

    bool addNode(const T &node) {
        if (nodeIds.count(node)) return false;
        nodeIds[node] = nodes;
        reverseNodeIds[nodes] = node;
        nodes++;
        return true;
    }

    void addEdge(const T &node1, const T &node2) {
        try {
            unsigned int id1 = nodeIds.at(node1);
            unsigned int id2 = nodeIds.at(node2);
            adj[id1].insert(id2);
            adj[id2].insert(id1);
        } catch (const std::out_of_range &e) {
            throw std::invalid_argument("At least one of the nodes does not exist prior to this operation");
        }
    }

    std::map<T, unsigned int> getDistances(const T &sourceNode) const {
        std::map<T, unsigned int> distances;
        if (nodeIds.count(sourceNode) == 0) throw std::invalid_argument("Source node does not exist in the graph!");

        unsigned int start = nodeIds.at(sourceNode);
        distances[sourceNode] = 0;

        std::queue<unsigned int> queue;
        queue.push(start);

        while (!queue.empty()) {
            auto top = queue.front();
            queue.pop();

            for (const auto &nextId: adj[top]) {
                T node = reverseNodeIds.at(nextId);
                if (distances.count(node)) continue;
                queue.push(nextId);
                distances[node] = distances[reverseNodeIds.at(top)] + 1;
            }
        }

        return distances;
    }
};

#endif //WORDLADDER_GRAPH_H
