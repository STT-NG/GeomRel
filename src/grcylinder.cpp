#include "grcylinder.h"

using namespace GeomRel;

GRCylinder::GRCylinder(int id, GRVector3 center, GRVector3 direction, double length, double radius)
    : GRNode(id),
      center(center),
      direction(direction),
      length(length),
      radius(radius),
      segment(center - (halflength * direction), center + (halflength * direction))
{

}

double GRCylinder::cylinderDistance(const GRCylinder *other, double max) const
{
    double radii = radius + other->radius;
    double segment_distance = segment.distanceTo(other->segment);
    if(segment_distance - radii >= max) {
        return segment_distance - radii;
    }
    return segment_distance - radii;
}

bool GRCylinder::adjacentTo(const GRNode *other, double tolerance) const
{
    const GRCylinder *cylinder = static_cast<const GRCylinder *>(other);
    if (cylinder) {
        return cylinderDistance(cylinder, 10) <= tolerance;
    }

    return false;
}
