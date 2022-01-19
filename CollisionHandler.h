#pragma once
#include <Box2D.h>

/// <summary>
/// This class is installed into Box2D to handle all object collisions
/// All it really does is proxy the call off to the colliding objects'
/// CollidedWith procedures
/// </summary>
class CollisionHandler :
    public b2ContactListener
{
public:
    /// <summary>
    /// The constructor
    /// </summary>
    /// <param name="world">A reference to the Box2D world to install this handler into</param>
    CollisionHandler(b2World& world);
    /// <summary>
    /// This is the collision function.  It fires once for any collision, in the first
    /// frame in which the object bodies overlap
    /// </summary>
    /// <param name="contact">Information from Box2D about the collision</param>
    void BeginContact(b2Contact* contact); // overridden from parent
};

