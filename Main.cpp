
// These are system libraries
#include <iostream>  // for cout
#include <chrono> // for Clock and Time
#include <thread> // for this_thread
#include <list> // for list<T>
// These are third party libraries
#include <SFML/Graphics.hpp>
#include "Box2D.h"
// these are application classes
#include "CollisionHandler.h" // this defines the behavior when objects collide
// each one of these below represents a kind of displayed object
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"
#include "Boundary.h"
#include "Score.h"
#include "BottomBoundary.h"
#include "ShootMessage.h"

using namespace sf;  // SFML namespace
using namespace std; // standard name space

// These constants define the size and layout of bricks
const int brick_width = 60;  //width of one brick
const int brick_height = 30; // height of one brick
const int hSpace = 5; // horizontal space between bricks
const int vSpace = 5; // vertical space between lines of bricks

// these constants define the starting position and speed of the ball
const Vector2f BallStart(400, 525);  // the location a new ball starts at
const float BallSpeed =0.1; // the linear velocity of a ball when it starts

// These two constants define parameters for setting up Box2D
// physics calculation
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

// This defines the frame rate of the game, in this case 1/30 of a second.
// It is very important that this be slower then the maximum calculation time of
// a frame or uneven movement will result
// This is because the physics and the frame update are all driven from the same thread.
// A more involved game might create a seperate threa for physics and interpolate physics
// results to find frame-time positions
const int32 frameMinMS = 1000 / 30; // 1/60th of a sec in ms



/// <summary>
/// Procedure AddWall
/// This procdure creates the grid of bricks at the start of the game.
/// Note that world, scoreand actors are all passed as references(&)
/// This is necessary because of the following :
///Using a copy of world when creating object wont properly update the
/// internal state of our physics world.
/// We will be updating score from bricks when they are collided with, so
/// all the bricks need a refernee to the real score object, not a temporary
/// copy of it.
/// We will be adding all the bricks to the actors list, which is used in the main
/// loop, so we need it not a copy of it or all additions will be lost
/// </summary>
/// <param name="world">A reference to the Box2D world that is in control of all of the game's physics</param>
/// <param name="score">A reference to the displayed Score object</param>
/// <param name="actors">A refernce to a list of all bricks created by this function</param>
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
// this code is old and not used in the current version.
// some times I will keep old code around this way in case I need to refer back to it
// or reuse some part of it
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




/// <summary>
/// This function returns a random floating value between 0 and 1 inclusive
///C++ only provides a random integer between 0 and RAND_MAX, but a normalized float
///is more mathematically useful.
/// </summary>
/// <returns> a random number between 0 an 1 inclusive</returns>
float rand0to1() {
    return ((float)rand()) / RAND_MAX;
}

/**
This is the main game loop.  It is where execution starts and it loops until the
window is closed.
**/

/// <summary>
/// This is the main game loop.  It is where execution starts and it loops until the
/// window is closed.
/// </summary>
/// <returns>an exit code</returns>
int main()
{
    // This creates an 800 x 600 pixel window for the game to play in
    RenderWindow window(VideoMode(800, 600), "Breakout!");

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
    list<Brick*> removalList; // needed for when they are hit, see below
    // this loads the arial font for text
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error: Could not load font" << endl;
        exit(1);
    }
    // The score and Shoot message objects are both Text objects.
    // See their individual files for details
    Score score(Vector2f(400, 10), font);
    ShootMessage shootMessage(font,800,600);

    // call the AddWall procedure to make the brick grid
    AddWall(world,score, bricks);

    // There is one paddle and one ball, each defined in their own files
    Paddle paddle(world,Color::White,Vector2f(400,550),Vector2f(60,20));
    Ball ball(world,8, BallStart);
 

    // Note, the next line is just a change in units from milliseconds to a fraction of a second
    // this is necessary because Box2D works in milliseconds but Clock reports time as 
    // fractions of a second
    float timeStep = frameMinMS / 1000; // frame time as fraction of a second

    // In order to keep an even frame rate we need to check the differentce beteen the
    // time of the last frame and this one, and wait if its less then 30ms for the
    //difference
    Clock clock;
    Time lastTime = clock.getElapsedTime();
    
    // The game loop
    while (window.isOpen())
    {
        sf::Event event; // used below to detect window close
        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        Time currentTime = clock.getElapsedTime();
        long elapsedTimeMS = (currentTime.asMilliseconds() - lastTime.asMilliseconds());
        //limit to 60fps
        if (elapsedTimeMS < frameMinMS){ // if ist been less then our min since last frame
            // this causes the program to wait for the passed in time
            // "sleeping" means the computer cna do other things while this program waits
            std::this_thread::sleep_for(std::chrono::milliseconds(frameMinMS - elapsedTimeMS));
            // its been the frame tiem nw.  Update the time variables for next frame
            currentTime = clock.getElapsedTime();
            elapsedTimeMS = (currentTime.asMilliseconds() - lastTime.asMilliseconds());
        }
        //whether we wait or not, we do need to store the current time as the "last time"
        // for next time around the loop (next frame)
        lastTime = currentTime;
        // this updates the Box2D physics engine and recalulates the positions and collisions
        // of objects it controls
        world.Step(((float32)frameMinMS) / 1000.0, velocityIterations, positionIterations);
        // the loop below reads all the events the system has sent us.
        // the only one we care about is window closing
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // This next code starts the ball movign when the
        // space bar is pressed.  It only works if the ball isnt currently being
        // displayed, otherwise you could cheat and reset the ball mid play!
        if (!ball.IsVisible() && Keyboard::isKeyPressed(Keyboard::Space)) {
            // this sets the position, angle of motion, and speed to start
            // the reset code sets both physics and graphics positions to keep them in-sync
            ball.Reset(BallStart, (rand0to1() * 90) + 225, BallSpeed); // -80 to 80
            // this makes the ball visible
            ball.Show(true);
        }

        // update paddle
        // This tells the paddle hwo much time has passed (in this case fixed at 1/30 of a second)
        // the paddle combines that with keyboard input and updates both its
        // drawn position and its physics position
        paddle.Update(elapsedTimeMS);
        // tick physics
        ball.Update(); // update visible ball posituon from physics

        //The next block updates the bricks.  bricks dont move but can be destroyed
        //and need to be removed from the playfield.
        // you cannot remove elements from a list in the midst of its traversal,
        // So we need to create a seperate list of blocks to be removed from the first
        removalList.clear(); // empty the removal list
        // loop and let bricks add themselves to removal list
        for(auto bPtr : bricks){
            bPtr->Update(removalList);
        }
        // remove bricks from the main actor list that are  on the removal list
        for (auto bPtr : removalList) {
            bricks.remove(bPtr); // note that we are looping on one list to remove its members from
        }                        // a different list

        // game state render
        // having updated bricks and ball, we now draw the new frame
        window.clear(); // remove the last frame from the frame buffer
        for (auto bPtr : bricks) { // draw the remaining bricks
            window.draw(*bPtr);
        }
        // draw the window borders
        window.draw(top);
        window.draw(bottom);
        window.draw(left);
        window.draw(right);
        window.draw(paddle);
        // IF the ball is in play then draw it
        if (ball.IsVisible()) {
            window.draw(ball);
        }
        else { // if there is no ball in play, display spacebar message instead
            window.draw(shootMessage);
        }
       
        window.draw(score); // draw the score at the top of the screen
        window.display();  // make all the draws visible
        
    }

    return 0; // no error
}