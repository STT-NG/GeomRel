#pragma once

#include "grvector.h"
#include <math.h>

class GRLineSegment3D
{
    using GRVector3 = GeomRel::GRVector3;
public:
  GRLineSegment3D(GRVector3 point, GRVector3 direction);

  double distanceTo(const GRLineSegment3D& line) const;

  const GRVector3 start;
  const GRVector3 end;

  inline friend bool operator==(const GRLineSegment3D& lhs, const GRLineSegment3D& rhs) {
      return lhs.start == rhs.start && lhs.end == rhs.end;
  }

  inline friend bool operator!=(const GRLineSegment3D& lhs, const GRLineSegment3D& rhs) {
      return !(lhs == rhs);
  }
};

