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

public:
    void load(const std::string &filePath);

    [[nodiscard]] const Graph<std::string> &getGraph() const;
};


#endif //WORDLADDER_DICTIONARY_H
