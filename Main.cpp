#include <SFML/Graphics.hpp>
#include <list>
#include "Brick.h"
#include "Gun.h"
#include "Ball.h"
#include "Box2D.h"
#include <chrono>
#include <thread>

using namespace sf;
using namespace std;

const int brick_width = 45;
const int brick_height = 15;
const int hSpace = 5;
const int vSpace = 5;

const float movePPS = 0.5;

const Vector2f BallStart(400, 525);
const float BallSpeed = 1000;

const int32 velocityIterations = 6;
const int32 positionIterations = 2;
const int32 frameMinMS = 1000 / 60; // 1/60th of a sec in ms

void AddWall(list<Brick>& actors) {
    Vector2f brickSize(brick_width, brick_height);
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 10; x++) {
            Vector2f pos(
                150 + (x * (brick_width + hSpace)),
                100 + (y * (brick_height + vSpace))
                );
            actors.push_back(Brick(Color::Green, brickSize, pos));
        }
    }
}

void MakeBounds(b2World& world, float x, float y, float width, float height) {
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(x+(width/2), y+(height/2));
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape* groundBox = new b2PolygonShape();
    groundBox->SetAsBox(width, height);
    b2FixtureDef fixDef;
    fixDef.shape = groundBox;
    fixDef.friction = 0;
    b2Fixture* fixture = groundBody->CreateFixture(&fixDef);
}



float rand0to1() {
    return ((float)rand()) / RAND_MAX;
}

int main()
{
    RenderWindow window(VideoMode(800, 600), "SFML works!");

    // set up physics world
    b2Vec2 gravity(0.0f, 0.0f); // no gravity
    b2World world(gravity);
    // add collision bounds at edges of screen
    MakeBounds(world, 0, 0, 800, 6); //top
    MakeBounds(world, 0, 594, 800, 6); // bottom
    MakeBounds(world, 0, 0, 6, 600); //left
    MakeBounds(world, 794, 0, 6, 600); // right
    
    // add bricks
    list<Brick> bricks;

    AddWall(bricks);

    Gun gun(Vector2f(400, 590));
    Ball ball(world,2, BallStart);

    
    
    // start physics
    float timeStep = 1.0f / 60.0f;

    Clock clock;
    Time lastTime = clock.getElapsedTime();
    
    ball.Reset(BallStart, (rand0to1()*90)-45, BallSpeed); // -80 to 80
    while (window.isOpen())
    {
        sf::Event event;
        Time currentTime = clock.getElapsedTime();
        long elapsedTimeMS = (currentTime.asMilliseconds() - lastTime.asMilliseconds());
        //limit to 60fps
        if (elapsedTimeMS < frameMinMS){
            std::this_thread::sleep_for(std::chrono::milliseconds(frameMinMS - elapsedTimeMS));
            currentTime = clock.getElapsedTime();
        }
           
        lastTime = currentTime;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // game state update
        bool leftArrow = Keyboard::isKeyPressed(Keyboard::Left);
        bool rightArrow = Keyboard::isKeyPressed(Keyboard::Right);
        bool space = Keyboard::isKeyPressed(Keyboard::Space);
        if (leftArrow && !rightArrow) {
            gun.setPosition(gun.getPosition() + Vector2f(-movePPS * elapsedTimeMS, 0));
        }
        if (rightArrow && !leftArrow) {
            gun.setPosition(gun.getPosition() + Vector2f(movePPS * elapsedTimeMS, 0));
        }
        // tick physics
        world.Step(((float32)frameMinMS)/1000.0, velocityIterations, positionIterations);
        ball.Update(); // update visible ball posituon from physics
        // game state render
        window.clear();
        list <Brick> ::iterator it;
        for (it = bricks.begin(); it != bricks.end(); ++it) {
            window.draw(*it);
        }
        window.draw(gun);
        window.draw(ball);
        window.display();
        
    }

    return 0;
}