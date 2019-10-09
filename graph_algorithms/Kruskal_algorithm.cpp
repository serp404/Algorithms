#include <iostream>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>
#define inf (1'000'000'000)

struct Graph {
    size_t V = 0; // Number of vertices
    std::unordered_map<size_t, std::map<size_t, size_t>> E; // Weighted adjacency list
}; // Vertices are numbered from 1

struct node {
    std::shared_ptr<node> parent;
    int value;
    int rank;

    node() : parent(nullptr), value(0), rank(0) {}
};

class Disjoint_Set {
private:
    std::vector<std::shared_ptr<node>> elements;
    int number_of_sets;

public:
    explicit Disjoint_Set(size_t n): elements(n + 1){
        for (int i = 1; i != n + 1; ++i) {
            node* temp = new node;
            temp->value = i;
            elements[i] = (std::shared_ptr<node>(temp));
        }
        number_of_sets = n;
    }

    int component(int k) {
        auto temp = elements[k];
        std::vector<int> temp_values;
        temp_values.reserve(20);
        while (temp->parent != nullptr) {
            temp_values.push_back(temp->value);
            temp = temp->parent;
        }
        for (const auto& el : temp_values)
            elements[el]->parent = temp;
        return temp->value;
    }

    void unite(int a, int b) {
        int root_a = component(a);
        int root_b = component(b);
        if (root_a != root_b) {
            if (elements[root_b]->rank > elements[root_a]->rank) {
                elements[root_a]->parent = elements[root_b];
            } else {
                elements[root_b]->parent = elements[root_a];
                if (elements[root_a]->rank == elements[root_b]->rank)
                    elements[root_a]->rank++;
            }
            number_of_sets--;
        }
    }

    bool all_joined() {
        return number_of_sets == 1;
    }
};

size_t Kruskal(Graph& g) {
    Disjoint_Set my_set(g.V);
    std::vector<std::pair<size_t, size_t>> edges;
    edges.reserve(g.V);
    for (const auto &u : g.E) {
        for (const auto &v : u.second)
            edges.emplace_back(u.first, v.first);
    }
    std::sort(edges.begin(), edges.end(), [&g](const auto& a, const auto& b)-> bool {
        return g.E[a.first][a.second] < g.E[b.first][b.second];
    });

    size_t ans = 0, i = 0;
    while (!my_set.all_joined()) {
        if (my_set.component(edges[i].first) != my_set.component(edges[i].second)) {
            ans += g.E[edges[i].first][edges[i].second];
            my_set.unite(edges[i].first, edges[i].second);
        }
        ++i;
    }
    return ans;
}
