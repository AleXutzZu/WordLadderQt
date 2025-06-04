//
// Created by AleXutzZu on 22/05/2025.
//

#include "Dictionary.h"
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <random>

void Dictionary::load(const std::string &filePath) {
    QFile input(QString::fromStdString(filePath));
    if (!input.open(QIODeviceBase::ReadOnly)) throw std::runtime_error("Could not open dictionary file: " + filePath);

    std::string word;
    QTextStream in(&input);
    while (!in.atEnd()) {
        word = in.readLine().toStdString();
        if (word.size() < 100) {
            auto res = graph.addNode(word);
            if (!res) continue;
            nonEmptyBuckets.insert(word.size());
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
            for (int j = i + 1; j < words.size(); ++j) {
                graph.addEdge(words[i], words[j]);
            }
        }
    }
}

const Graph<std::string> &Dictionary::getGraph() const {
    return graph;
}

std::pair<std::string, std::string> Dictionary::getRandomPair() const {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distribution1(0, nonEmptyBuckets.size() - 1);

    std::vector<int> bucketIndices(nonEmptyBuckets.begin(), nonEmptyBuckets.end());

    int bucket = bucketIndices[distribution1(engine)];

    std::uniform_int_distribution<int> distribution2(0, buckets[bucket].size() - 1);
    int word1 = distribution2(engine);
    int word2 = distribution2(engine);
    return {buckets[bucket][word1], buckets[bucket][word2]};
}
