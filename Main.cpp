#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"
#include "Box2D.h"
#include <chrono>S
#include <thread>
#include "Boundary.h"
#include "CollisionHandler.h"
#include "Score.h"
#include "BottomBoundary.h"

using namespace sf;
using namespace std;

const int brick_width = 60;
const int brick_height = 30;
const int hSpace = 5;
const int vSpace = 5;



const Vector2f BallStart(400, 525);
const float BallSpeed =0.1;

const int32 velocityIterations = 6;
const int32 positionIterations = 2;
const int32 frameMinMS = 1000 / 30; // 1/60th of a sec in ms



void AddWall(b2World& world, Score &score, list<Brick*>& actors) {
    Vector2f brickSize(brick_width, brick_height);
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 10; x++) {
            Vector2f pos(
                75 + (x * (brick_width + hSpace)),
                50 + (y * (brick_height + vSpace))
                );
            actors.push_back(new Brick(world, score, Color::Green, pos,brickSize));
        }
    }
}

/* Dino code
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
}*/



float rand0to1() {
    return ((float)rand()) / RAND_MAX;
}

int main()
{
    RenderWindow window(VideoMode(800, 600), "SFML works!");

    // set up physics world
    b2Vec2 gravity(0.0f, 0.0f); // no gravity
    b2World world(gravity);
    // adde collision logic
    CollisionHandler collisionHandler(world);
    // add collision bounds at edges of screen
    Boundary top = Boundary(world, Color::Green, Vector2f( 0, 0), Vector2f(800, 6)); //top
    BottomBoundary bottom = BottomBoundary(world, Color::Green, Vector2f(0, 594),Vector2f( 800, 6)); // bottom
    Boundary left(world,Color::Green,Vector2f( 0, 0), Vector2f( 6, 600)); //left
    Boundary right(world, Color::Green, Vector2f(794, 0), Vector2f( 6, 600)); // right
    
    // add bricks
    list<Brick*> bricks;
    list<Brick*> removalList;
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error: Could not load font" << endl;
        exit(1);
    }
    Score score(Vector2f(400, 10), font, 30);
    AddWall(world,score, bricks);

    Paddle paddle(world,Color::White,Vector2f(400,550),Vector2f(60,20));
    Ball ball(world,8, BallStart);
 
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
            elapsedTimeMS = (currentTime.asMilliseconds() - lastTime.asMilliseconds());
        }
        lastTime = currentTime;
        world.Step(((float32)frameMinMS) / 1000.0, velocityIterations, positionIterations);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // game state update
        // update paddle
        paddle.Update(elapsedTimeMS);
        // tick physics
        ball.Update(); // update visible ball posituon from physics
        removalList.clear(); // empty the removal list
        // looP and let bricks add themselves rto removal list
      
        for(auto bPtr : bricks){
            bPtr->Update(removalList);
        }
        // remove bricks that need removal
        for (auto bPtr : removalList) {
            bricks.remove(bPtr);
        }

        // game state render
        window.clear();
        for (auto bPtr : bricks) {
            window.draw(*bPtr);
        }
        window.draw(top);
        window.draw(bottom);
        window.draw(left);
        window.draw(right);
        window.draw(paddle);
        if (ball.IsVisible()) {
            window.draw(ball);
        }
       
        window.draw(score);
        window.display();
        
    }

    return 0;
}