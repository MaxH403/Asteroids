/** --------------------------------------------------------
* @project    Asteroids (game.cpp)
* @author  Maxwell Hermens
* @version 3.0
*
* Demonstrates:
*   Draws multiple asteroids, detects collision between ship and
* asteroids and creats a explosion effect.
* ------------------------------------------------------------ */

#include <SFML/Graphics.hpp>
#include <iostream>
#include "spaceObject.h"
#include "constants.h"

using namespace std;;

/*
 * gets a random location for the asteroids
 *
 */
Point getRandomLocation();

/*
* gets a random velocity for the asteroids
*
*/
Point getRandomVelocity();

/*
* detects colision between ship and asteroids
*
* returns true if objects collide, false if they dont.
*/
bool objectsIntersect(SpaceObject* object1, SpaceObject* object2);

int main()
{
    //create graphics window
    sf::RenderWindow window(
        sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
        "Asteroids",
        sf::Style::Titlebar | sf::Style::Close
    );
    window.setFramerateLimit(60);

    //create SpaceObjects

    SpaceObject* asteroids[MAX_ASTEROIDS] = { NULL };

    for (int x = 0; x < MAX_ASTEROIDS; x++) {

        asteroids[x] = new SpaceObject(ASTEROID, 20, getRandomLocation(), getRandomVelocity(), 90);
    }

    for (int x = 0; x < MAX_ASTEROIDS; x++) {

        asteroids[x]->drawAsteroid(window);
    }

    SpaceObject* ship = new SpaceObject(SHIP, 10, { 200, 200 }, 
        { 0,0 }, 0);

    srand(42);
    
    //game loop
    while (window.isOpen())
    {
        //handle user input (events and keyboard keys being pressed) ----
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            ship->changeAngle(4);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            ship->changeAngle(-4);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            ship->applyThrust();


        // update game objects ------------------------------------------
        for (int x = 0; x < 5; x++) {
            if (asteroids[x] != NULL) {
            asteroids[x]->updatePosition();
            }
        }
        ship->updatePosition();

        for (int index = 0; index < 5; index++) {
            if (asteroids[index] != NULL) {
                if (objectsIntersect(asteroids[index], ship)) {
                    ship->explode();
                }
            }
        }

        // draw new frame ------------------------------------------------
        window.clear();
        
        //drawing 5 asteroids
        for (int x = 0; x < 5; x++) {
            if (asteroids[x] != NULL) {
                asteroids[x]->draw(window);
            }
        }
        //drawing ship
        ship->draw(window);
        window.display();
    }

    return 0;
}

Point getRandomLocation() {
    Point randomLocation;

    randomLocation.x = (rand() % SCREEN_WIDTH + 1);
    randomLocation.y = (rand() % SCREEN_HEIGHT + 1);

    cout << randomLocation.x;
    cout << randomLocation.y;

    return randomLocation;
}

Point getRandomVelocity() {
    Point randomVelocity;
    double low = -1.0;
    double high = 1.0;
    int range = (high - low + 0.001) * 200;

    randomVelocity.x = (rand() % range + 0.001) / 200 + low;
    randomVelocity.y = (rand() % range + 0.001) / 200 + low;

    return randomVelocity;
}

bool objectsIntersect(SpaceObject* object1, SpaceObject* object2) {
    Point p1 = object1->getLocation();
    Point p2 = object2->getLocation();
    double radiusSum = object1->getRadius() + object2->getRadius();
    double distance = sqrt((pow(p1.x - p2.x, 2)) + (pow(p1.y - p2.y, 2)));

    if (distance < radiusSum)
        return true;
    else
        return false;
}
