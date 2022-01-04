#pragma once
#include <Box2D.h>

class CollisionHandler :
    public b2ContactListener
{
public:
    CollisionHandler(b2World& world);
    void BeginContact(b2Contact* contact); // overridden from parent
};

