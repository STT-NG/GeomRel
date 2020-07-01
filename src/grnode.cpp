#include "grnode.h"
#include <vector>

using namespace GeomRel;

GRNode::GRNode(int id)
    : _id(id)
{}

void GRNode::addNeighbour(int id, int order)
{
    auto it = _neighbours.find(order);
    if (it != _neighbours.end()) {
        it->second.insert(id);
    } else {
        _neighbours.insert(std::make_pair(order, std::set{id}));
    }
}

void GRNode::removeNeighbour(int id)
{
    std::vector<int> remove;
    for (auto &[order, set] : _neighbours) {
        if (set.find(id) != set.end()) {
            set.erase(id);
        }

        if (set.empty()) {
            remove.push_back(order);
        }
    }

    for (int r : remove) {
        _neighbours.erase(r);
    }
}

double GRNode::getSpacing() const
{
    return positionScale;
}

void GRNode::setSpacing(double value)
{
    positionScale = value;
}

double GRNode::getNodeScale() const
{
    return sizeScale;
}

void GRNode::setNodeScale(double value)
{
    sizeScale = value;
}
