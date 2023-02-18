/** --------------------------------------------------------
* @project    Asteroids (spaceObject.h)
* @author  Maxwell Hermens
* @version 3.0
*
* Demonstrates:
*   Draws multiple asteroids, detects collision between ship and
* asteroids and creats a explosion effect.
* ------------------------------------------------------------ */
#pragma once
#include <SFML/Graphics.hpp>

struct Point {
	double x;
	double y;
};

enum SpaceObjType { SHIP, ASTEROID, PHOTON_TORPEDO,
	SHIP_EXPLODING, SHIP_GONE};


class SpaceObject {

public:
	SpaceObject();

	/* 
	* Creates radius, location, velocity, and angle values for called upon
	* type of space object.
	* 
	* param@ type, radius, location, velocity, angle
	* return@ SHIP, ASTEROID, PHOTON_TORPEDO 
	*/
	SpaceObject(SpaceObjType type, double radius,
		Point location, Point velocity, double angle);
	//=============================================
	//mutators

	/*
	* Sets radius for object
	* (Checks bounds for negative # and number larger than half
	* the screen size)
	*
	* param@ radius
	* return@ true or false
	*/
	bool setRadius(int radius);

	/*
	* Sets location for object
	* (Checks if location is outside screen, puts object back on
	* screen if it moves out)
	*
	* param@ x, y
	* return@ true 
	*/
	bool setLocation(double x, double y);

	/*
	* Sets velocity for object
	*
	* param@ velocity for x and y cordinates
	* return@ true or false
	*/
	bool setVelocity(double velocityX, double velocityY);

	/*
	* Sets angle for object
	*
	* param@ degree of angle
	* return@ true or false
	*/
	bool setAngle(double angDeg);

	/*
	* change angle by given amount.
	*
	* param@ delta degree
	*/
	void changeAngle(double deltaDeg);

	//============================================
	//accessors

	/*
	* gets radius for object
	*
	*/
	double getRadius() const;

	/*
	* gets location for object
	*
	*/
	Point getLocation() const;

	/*
	* gets velocity for object
	*
	*/
	Point getVelocity() const;

	/*
	* gets angle for object
	*
	*/
	double getAngle() const;

	//============================================
	//others

	/*
	* Updates position for object
	*
	*/
	void updatePosition();

	/*
	* explodes ship
	*
	*/
	void explode();

	void dumpData() const; //prints objects data to cout (for testing)

	/** --------------------------------------------------------------------------
*   Draws the spaceobject on the given window
*
* 	@param win - the window on which we’ll draw the ship
---------------------------------------------------------------------------- */

	void draw(sf::RenderWindow& win);

	/*
	* Allows ship to move in the direction it is facing.
	*
	*/
	void applyThrust();

	/** --------------------------------------------------------------------------
*   Draws the spaceobject on the given window as an asteroid
*
* 	@param win - the window on which we’ll draw the ship
---------------------------------------------------------------------------- */
	void drawAsteroid(sf::RenderWindow& win);

	/** --------------------------------------------------------------------------
*   Draws the spaceobject on the given window as a ship
*
* 	@param win - the window on which we’ll draw the ship
---------------------------------------------------------------------------- */
	void drawShip(sf::RenderWindow& win);

	/** --------------------------------------------------------------------------
*   Draws the exploding ship animation
*
* 	@param win - the window on which we’ll draw the (dead) ship
---------------------------------------------------------------------------- */
	void drawExplodingShip(sf::RenderWindow& win);

private:
	SpaceObjType type;	  //type of object
	Point location;	      //current location (x,y)
	Point velocity;	      //current velocity (in pixels/frame)
	double angleDeg;	  //angle object is facing (in degrees)
	double radius;        //gross radius of object (for collision detection)
};
