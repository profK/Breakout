#pragma once
#include "Box2D.h"
#include "SFML/Graphics.hpp"
#include <string>

using namespace sf;

/// <summary>
/// This is an enum used to identify what kind of object an object
/// collided with.
/// </summary>
enum ObjectType {
	BallType, WallType, BrickType,PaddleType,ExitType
};



/// <summary>
/// This is a base class for all objects that have to either move with forces
/// and/or detect collisions with other objects.  It uyses a rectangular
/// bounding box as the physics body for collision and force application
/// </summary>
class PhysicsObject
{
	
public:
	b2World& world; // This is a ref to the world of Box2D objects
	b2Body* body; // This is a pointer to a body object that defines this object's
	              // physical properties 
	ObjectType objType; // this is the type of this object as per the above enum

	/// <summary>
	/// This is the constructor for a PhysicsObject
	/// </summary>
	/// <param name="world">A reference to the Box2D simulation world this object belongs to</param>
	/// <param name="otype">The type of the object as per the above enum</param>
	/// <param name="centerPosition">The center of the rectangular bounding box the body represents</param>
	/// <param name="size">The wdith and height of the bounding box</param>
	PhysicsObject(b2World& world, ObjectType otype, Vector2f centerPosition, Vector2f size);
	/// <summary>
	/// A getter for the object type
	/// </summary>
	/// <returns>The object type set at construction</returns>
	ObjectType GetObjType();
	/// <summary>
	/// A useful debug that prints the textual name of this
	/// physics object's object type.  E.g.  "BallType"
	/// </summary>
	void PrintObjectTypeName();
	/// <summary>
	/// When a collision occurs with another PhysicsObject, this
	/// method gets called on both objects, with the other object
	/// passed as its one parameter
	/// 
	/// This is a virtual method intended to be over-ridden by
	/// a child class with object specific behavior
	/// </summary>
	/// <param name="otherObject"></param>
	virtual void CollidedWith(PhysicsObject& otherObject);
	/// <summary>
	/// Box2D has a coordinate system that is generally incompatible with a
	/// pixel coordinate system as its scale is 1.0 = 1m.  To get anything but
	/// very slow movement, the positions must be scaled to something where 1.0 is
	/// much smaller.  This function returns the position of the physics body appropriately
	/// scaled down
	/// </summary>
	/// <returns> A position for the center of the physics body scaled for pixel coordinates</returns>
	Vector2f GetScaledCenterPosition();
	/// <summary>
	/// This is the reverse of GetScaledPosition.  It sets the physics bodies position
	/// to an identically scaled up version of the pixel position
	/// </summary>
	/// <param name="pos">The pixel position of the center of the scaled body</param>
	void SetScaledCenterPosition(Vector2f pos);
	/// <summary>
	///  This returns a normalized vector that represents the current direction of motion of
	///  the phsyics body.
	/// </summary>
	/// <returns> A normalized vector indicating the current direction of motion</returns>
	Vector2f GetMotionDirection();
	/// <summary>
	/// This applies a force to the physics body at the same scale as the set and get scaled
	/// position calls
	/// </summary>
	/// <param name="forceVector">The force to apply scaled in pixel coordinates</param>
	void ApplyScaledForce(Vector2f forceVector);

};

