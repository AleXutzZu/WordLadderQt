import networkx as nx
from collections import defaultdict
from itertools import combinations


def load_words(min_len=4, max_len=8):
    with open("words_alpha.txt") as f:
        words = set(w.strip().lower() for w in f if w.strip().isalpha())
    return [w for w in words if min_len <= len(w) <= max_len]


def is_one_letter_apart(a, b):
    if len(a) != len(b):
        return False
    diff = sum(c1 != c2 for c1, c2 in zip(a, b))
    return diff == 1


def build_graph(words):
    buckets = defaultdict(list)
    for word in words:
        for i in range(len(word)):
            key = word[:i] + "_" + word[i + 1:]
            buckets[key].append(word)

    G = nx.Graph()
    G.add_nodes_from(words)
    for bucket in buckets.values():
        for w1, w2 in combinations(bucket, 2):
            G.add_edge(w1, w2)
    return G


def save_largest_component(graph, filename="filtered_dictionary.txt"):
    largest_cc = max(nx.connected_components(graph), key=len)
    with open(filename, "w") as f:
        for word in sorted(largest_cc):
            f.write(word + "\n")
    print(f"Saved {len(largest_cc)} well-connected words to {filename}")


if __name__ == "__main__":
    # load_words(4, 8)
    words = load_words()
    print(f"Loaded {len(words)} words.")
    graph = build_graph(words)
    save_largest_component(graph)
