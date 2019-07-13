#include <iostream>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#define inf (1'000'000'000)

struct Graph {
    size_t V = 0; // Number of vertices
    std::unordered_map<size_t, std::map<size_t, size_t>> E; // Weighted adjacency list
};

class min_heap {
private:
    std::deque<std::pair<size_t, size_t>> h;
    std::unordered_set<size_t> in_h;

    size_t left(size_t k) const {
        return 2 * (k + 1) - 1;
    }

    size_t right(size_t k) const {
        return 2 * (k + 1);
    }

    size_t parent(size_t k) const {
        return (k + 1) / 2 - 1;
    }

    void heapify_up(size_t k) {
        while (k > 0 && h[k].second < h[parent(k)].second) {
            std::swap(h[k], h[parent(k)]);
            k = parent(k);
        }
    }

    void heapify_down(size_t k) {
        size_t l = left(k);
        size_t r = right(k);
        if (r < h.size()) {
            size_t child;
            if (h[l].second < h[r].second)
                child = l;
            else
                child = r;
            if (h[k].second > h[child].second) {
                std::swap(h[k], h[child]);
                heapify_down(child);
            }
        } else if (l < h.size()) {
            if (h[l].second < h[k].second)
                std::swap(h[l], h[k]);
        }
    }

public:
    min_heap() = default;

    void resize(size_t n, size_t value) {
        h.resize(n, {0, value});
        for (size_t i = 0; i != h.size(); ++i) {
            h[i].first = i + 1;
            in_h.insert(i + 1);
        }
    }

    void insert(size_t name, size_t key) {
        h.emplace_back(name, key);
        heapify_up(h.size() - 1);
        in_h.insert(name);
    }

    size_t size() const {
        return h.size();
    }

    size_t top_value() const {
        return h[0].second;
    }

    bool empty() const {
        return h.empty();
    }

    std::pair<size_t, size_t> extract_min() {
        auto ans = h[0];
        std::swap(h[0], h[h.size() - 1]);
        h.pop_back();
        heapify_down(0);
        in_h.erase(ans.first);
        return ans;
    }

    void decrease_key(size_t k, size_t value) {
        for (size_t i = 0; i != h.size(); ++i) {
            if (h[i].first == k) {
                h[i].second = value;
                heapify_up(i);
                break;
            }
        }
    }

    bool is_in_heap(size_t name) const {
        return in_h.find(name) != in_h.end();
    }
};

size_t Prim(Graph& g) {
    std::vector<size_t> dist(g.V + 1, inf);
    size_t ans = 0;
    dist[1] = 0;
    min_heap Q;
    for (const auto& el : g.E[1]) {
        Q.insert(el.first, el.second);
        dist[el.first] = el.second;
    }
    while (!Q.empty()) {
        auto [cur_node, d] = Q.extract_min();
        ans += d;
        for (const auto& el : g.E[cur_node]) {
            if (!Q.is_in_heap(el.first)) {
                Q.insert(el.first, el.second);
                dist[el.first] = el.second;
            } else {
                if (el.second < dist[el.first]) {
                    Q.decrease_key(el.first, el.second);
                    dist[el.first] = el.second;
                }
            }
        }
    }
    return ans;
}
