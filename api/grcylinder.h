#pragma once

#include "grvector.h"
#include "grnode.h"
#include "grline.h"

namespace GeomRel {

class GRCylinder : public GRNode
{
public:
    explicit GRCylinder(int id, GRVector3 center, GRVector3 direction, double length, double radius);
    ~GRCylinder() override {}

    const GRVector3 center;
    const GRVector3 direction;
    const double length;
    const double halflength = length / 2.0;
    const double radius;
    const double diameter = 2.0 * radius;
    const GRLineSegment3D segment;

    double cylinderDistance(const GRCylinder *other, double max) const;

    bool adjacentTo(const GRNode *other, double tolerance) const override;

private:
    double _posX() const override { return center.x(); }
    double _posY() const override { return center.y(); }
    double _posZ() const override { return center.z(); }
    double _sizeX() const override { return diameter; }
    double _sizeY() const override { return diameter; }
};

}
