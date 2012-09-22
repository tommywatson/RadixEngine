#ifndef __SHOT_HPP
#define __SHOT_HPP

#include <GL/glut.h>
#include "Box.hpp"
#include "Portal.hpp"

struct Shot {
public:
	Shot() : active(false), x(0), y(0), z(0), xspeed(0), yspeed(0), zspeed(0) { }

	void shoot(int _id, float _x, float _y, float _z, float xrot, float yrot);
	void update(float dt);
	void draw(GLuint *textures, float xrot, float yrot);
	void placePortal(Box &box, Portal &portal);

	bool active;
	int id;
	float x,y,z;
	float xspeed, yspeed, zspeed;
};
#endif