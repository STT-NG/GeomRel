#pragma once

#include <functional>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <grnode.h>

namespace GeomRel {

class GRBuilder {
public:
    explicit GRBuilder() {}

    void build(int order, double tolerance,
               std::function<void(void)> progressCallback = [](){},
               std::function<void(int,int,int)> addedCallback = [](int, int, int){})
    {
        for (const auto &[id, node] : _nodes) {
            for (const auto &[o_id, other] : _nodes) {
                if (o_id != id) {
                    if(node->adjacentTo(other, tolerance)) {
                        node->addNeighbour(o_id, 1);
                        addedCallback(id, o_id, 1);
                    }
                }
            }

            progressCallback();
        }

        if (order > 1) {
            std::map<int, std::map<int, std::set<int>>> augmentPerNode;
            for (const auto &[id, node] : _nodes) {
                auto augmentMap = computeAugment(id, order);
                augmentPerNode.insert(std::make_pair(id, augmentMap));
            }

            for (const auto &[node_id, map] : augmentPerNode) {
                auto node_it = _nodes.find(node_id);
                if(node_it != _nodes.end()) {
                    GRNode *node = node_it->second;
                    for (const auto &[ord, augment] : map) {
                        for (int id : augment) {
                            auto other_it = _nodes.find(id);
                            if (other_it != _nodes.end()) {
                                node->addNeighbour(id, ord);
                                addedCallback(node_id, id, ord);
                            }
                        }
                    }
                }

                progressCallback();
            }
        }
    }

    void setNodes(const std::vector<GRNode *> &nodes) {
        _nodes.clear();
        for (const auto node : nodes) {
            _nodes.insert(std::make_pair(node->id(), node));
        }
    }

private:

    std::map<int, std::set<int>> computeAugment(int node_id, int order) {

        auto it = _nodes.find(node_id);
        if (it == _nodes.end()) return {};

        auto node = it->second;

        std::map<int, std::set<int>> augmentMap;
        std::set<int> neighbours = node->neighbours(1);
        std::set<int> augment = neighbours;

        for (int i = 2; i <= order; ++i) {
            auto copy = std::set<int>(augment);
            for (int id : copy) {
                auto it = _nodes.find(id);
                if (it == _nodes.end()) continue;
                GRNode *node = it->second;
                auto related = node->neighbours(1);

                for (int rel : related) {
                    augment.insert(rel);
                }
            }


            std::set<int> computed = augment;
            if (augmentMap.empty()) {
                for (int id : neighbours) {
                    computed.erase(id);
                }
                computed.erase(node_id);
            } else {
                for (int j = i - 1; j > 0; --j) {
                    auto it = augmentMap.find(j);
                    if (it != augmentMap.end()) {
                        for (int id : augmentMap.at(j)) {
                            computed.erase(id);
                        }
                    }
                }
                for (int id : neighbours) {
                    computed.erase(id);
                }
                computed.erase(node_id);
            }
            augmentMap.insert(std::make_pair(i, computed));
        }

        return augmentMap;
    }

    std::map<int, GRNode *> _nodes;
};

}
