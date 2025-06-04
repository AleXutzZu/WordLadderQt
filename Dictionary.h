//
// Created by AleXutzZu on 22/05/2025.
//

#ifndef WORDLADDER_DICTIONARY_H
#define WORDLADDER_DICTIONARY_H

#include "Graph.h"

class Dictionary {
private:
    Graph<std::string> graph;
    std::vector<std::string> buckets[100];
    std::unordered_set<int> nonEmptyBuckets;
public:
    void load(const std::string &filePath);

    [[nodiscard]] const Graph<std::string> &getGraph() const;

    std::pair<std::string, std::string> getRandomPair() const;
};


#endif //WORDLADDER_DICTIONARY_H
