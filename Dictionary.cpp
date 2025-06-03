//
// Created by AleXutzZu on 22/05/2025.
//

#include "Dictionary.h"
#include <fstream>
#include <QFile>

void Dictionary::load(const std::string &filePath) {
    QFile input(QString::fromStdString(filePath));
    if (!input.open(QIODeviceBase::ReadOnly)) throw std::runtime_error("Could not open dictionary file: " + filePath);

    std::string word;
    while (input.canReadLine()) {
        word = input.readLine().toStdString();
        if (word.size() < 100) {
            auto res = graph.addNode(word);
            if (!res) continue;
            buckets[word.size()].push_back(std::move(word));
        }
    }

    std::map<std::string, std::vector<std::string>> masks;

    for (const auto &bucket: buckets) {
        if (bucket.empty()) continue;

        for (const auto &elem: bucket) {
            for (int i = 0; i < elem.size(); ++i) {
                std::string mask = elem;
                mask[i] = '*';
                masks[mask].push_back(elem);
            }
        }
    }

    for (const auto &[mask, words]: masks) {
        for (int i = 0; i < words.size(); ++i) {
            for (int j = i + 1; j < word.size(); ++j) {
                graph.addEdge(words[i], words[j]);
            }
        }
    }
}

const Graph<std::string> &Dictionary::getGraph() const {
    return graph;
}
