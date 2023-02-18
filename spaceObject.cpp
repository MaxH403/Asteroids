/** --------------------------------------------------------
* @project    Asteroids (spaceObject.cpp)
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

SpaceObject::SpaceObject(SpaceObjType type, double radius,
	Point location, Point velocity, double angle) {

	this->type = type;
	if (setRadius(radius) == false) {
		radius = 20.0;
	}
	setLocation(location.x, location.y);
	setVelocity(velocity.x, velocity.y);
	setAngle(angle);
}

bool SpaceObject::setRadius(int radius) {
	//checks for bounds
	if (radius <= 0 || radius >=(0.5 * SCREEN_HEIGHT)) {
		return false;
	}
	else
		this->radius = radius;

	return true;
}

bool SpaceObject::setLocation(double x, double y) {
	//checks for bounds 
	while (x > SCREEN_WIDTH || x < 0) {
		if (x < 0) {
			x = x + SCREEN_WIDTH;
		}
		if (x > SCREEN_WIDTH) {
			x = x - SCREEN_WIDTH;
		}
	}
	while (y > SCREEN_HEIGHT || y < 0) {
		if (y < 0) {
			y = y + SCREEN_HEIGHT;
		}
		if (y > SCREEN_HEIGHT) {
			y = y - SCREEN_HEIGHT;
		}
	}
	location.x = x;
	location.y = y;

	return true;
}

bool SpaceObject::setVelocity(double velocityX, double velocityY) {
	velocity.x = velocityX;
	velocity.y = velocityY;

	if (velocity.x == velocityX && velocity.y == velocityY)
		return true;
    else
		return false;
}

bool SpaceObject::setAngle(double angDeg) {
	angleDeg = angDeg;

	while (angleDeg < 0 || angleDeg > 359) {
		if (angleDeg < 0)
			angleDeg = angleDeg + 359;
		if (angleDeg > 359)
			angleDeg = angleDeg - 359;
	}
	return true;
}

void SpaceObject::changeAngle(double deltaDeg) {
	//no changing direction while dead
	if (type != SHIP) return;
	angleDeg = angleDeg - deltaDeg;
}

double SpaceObject::getRadius() const {
	return radius;
}

Point SpaceObject::getLocation() const {
	return location;
}

Point SpaceObject::getVelocity() const {
	return velocity;
}

double SpaceObject::getAngle() const {
	return angleDeg;
}

void SpaceObject::updatePosition() {
	
	setLocation(velocity.x + location.x, velocity.y + location.y);
}

void SpaceObject::explode() {
	type = SHIP_EXPLODING;
	setVelocity(0, 0);
}

void SpaceObject::draw(sf::RenderWindow& win) {
	if (type == SHIP) {
		drawShip(win);
	}
	else if (type == ASTEROID) {
		drawAsteroid(win);
	}
	else if (type == SHIP_EXPLODING) {
		drawExplodingShip(win);
	}
	else if (type == SHIP_GONE){
		cout << "GAME OVER" << '\n';
	}
}

void SpaceObject::drawAsteroid(sf::RenderWindow& win) {
	//Configure a graphics object to be used for drawing our object
	//this code draws a simple pentagon.Feel free to modify it if you want.
	int points = 5;
	sf::CircleShape shape(radius, points); //radius from our SpaceObject

	sf::Vector2f midpoint(radius, radius);
	shape.setOrigin(midpoint);

	shape.setFillColor(sf::Color(200, 30, 18));
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color(200, 200, 200));
	
	//apply our object position to the graphics object and draw it
	shape.setPosition(location.x, location.y);
	shape.setRotation(angleDeg);

	win.draw(shape);

	//Note: if asteroid is near the edge (within a radius) then we should 
	//draw it again on the other side of the screen so the part off the edge 
	//shows up immediately on the other edge. Code to do that should be added
	//here.
	
}

void SpaceObject::drawShip(sf::RenderWindow& win) {
	// draw ship
	sf::ConvexShape shipShape;
	shipShape.setPointCount(4);
	shipShape.setPoint(0, sf::Vector2f(10, 0));
	shipShape.setPoint(1, sf::Vector2f(0, 25));
	shipShape.setPoint(2, sf::Vector2f(10, 20));
	shipShape.setPoint(3, sf::Vector2f(20, 25));

	sf::Vector2f midpoint(10, 12);
	shipShape.setOrigin(midpoint);

	shipShape.setFillColor(sf::Color(58, 58, 232));
	shipShape.setOutlineThickness(1);
	shipShape.setOutlineColor(sf::Color(255, 255, 255));

	shipShape.setPosition(location.x, location.y);
	shipShape.setRotation(angleDeg);
	win.draw(shipShape);
}

void SpaceObject::drawExplodingShip(sf::RenderWindow& win) {
	
	int points = 100;

	sf::CircleShape shape(radius, points);

	sf::Vector2f midpoint(radius, radius);
	shape.setOrigin(midpoint);

	shape.setFillColor(sf::Color(255, 0, 0));
	shape.setOutlineThickness(10);
	shape.setOutlineColor(sf::Color(255, 110, 0));

	shape.setPosition(location.x, location.y);
	shape.setRotation(angleDeg);

	win.draw(shape);
	radius = radius + 0.1;

	if (radius >= 5) {
		type = SHIP_GONE;
	}
}

void SpaceObject::applyThrust() {
	//no thrust if ship is dead
	if (type != SHIP) return;

	double engineThrust = 0.036;
	double forcex = cos((angleDeg - 90) * PI / 180) * engineThrust;
	double forcey = sin((angleDeg - 90) * PI / 180) * engineThrust;
	velocity.x = velocity.x + forcex;
	velocity.y = velocity.y + forcey;
}
