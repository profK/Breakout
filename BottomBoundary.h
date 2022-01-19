#pragma once
#include "Boundary.h"



/// <summary>
/// A sub class of boundary the is ised to remove the ball when it
/// collides with it.
/// The ball actually knows how to handle this, it just needs to
/// know that this is the kidn of boundary it hit.
/// </summary>
/// <param name="world">See Boundary.h</param>
/// <param name="color">See Boundary.h</param>
/// <param name="position">See Boundary.h</param>
/// <param name="size">See Boundary.h</param
class BottomBoundary :
    public Boundary
{
public:
    /// <summary>
    /// A constructor for BottomBoundary
    /// </summary>
    /// <param name="world">See Boundary.h</param>
    /// <param name="color">See Boundary.h</param>
    /// <param name="position">See Boundary.h</param>
    /// <param name="size">See Boundary.h</param>
    BottomBoundary(b2World& world, Color color, Vector2f position, Vector2f size);
};

