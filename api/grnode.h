#pragma once

#include <set>
#include <map>


namespace GeomRel {

class GRNode
{
public:
    explicit GRNode(int id);
    virtual ~GRNode() = default;

    int id() const { return _id; }

    std::set<int> neighbours(int order) const {
        auto it = _neighbours.find(order);
        if (it != _neighbours.end()) {
            return it->second;
        }
        return {};
    }

    void addNeighbour(int id, int order);
    void removeNeighbour(int id);

    virtual bool adjacentTo(const GRNode *other, double tolerance) const = 0;

    double posX() const { return positionScale * _posX(); }
    double posY() const { return positionScale * _posY(); }
    double posZ() const { return positionScale * _posZ(); }
    double sizeX() const { return sizeScale * _sizeX(); }
    double sizeY() const { return sizeScale * _sizeY(); }

    double getSpacing() const;
    void setSpacing(double value);

    double getNodeScale() const;
    void setNodeScale(double value);

    int maxOrder() const {return _neighbours.size();}

protected:
    virtual double _posX() const = 0;
    virtual double _posY() const = 0;
    virtual double _posZ() const = 0;

    virtual double _sizeX() const = 0;
    virtual double _sizeY() const = 0;

private:
    int _id;

    std::map<int, std::set<int>> _neighbours;

    double positionScale = 1;
    double sizeScale = 1;
};

}
