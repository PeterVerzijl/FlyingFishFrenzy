#ifndef PARTICLE_HEADER
#define PARTICLE_HEADER

#include "ofMain.h"

#pragma once
class Particle 
{
public:
	Particle();
	Particle(int x, int y);
	Particle(int x, int y, ofImage picture);
	~Particle();

	void update();
	void draw();
	void addForce(ofVec2f force);
	bool dead;

private:
	ofVec2f pos, vel, acc, gravity;
	float maxspeed;
	float angle;
	int life;
	ofImage image;
};

#endif