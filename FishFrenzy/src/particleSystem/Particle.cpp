#include "Particle.h"

Particle::Particle()
{
	pos.set(0, 0);
	vel.set(0, 0);
	acc.set(0, 0);

	gravity.set(0, 3.0f);

	maxspeed = 10.0f;
	angle = 0.0f;

	life = 60 * 5;
	dead = false;
}

Particle::Particle(int x, int y)
{
	pos.set(x, y);
	vel.set(0, 0);
	acc.set(0, 0);

	gravity.set(0, 3.0f);

	maxspeed = 10.0f;
	angle = 0.0f;

	life = 60 * 5;
	dead = false;
}

Particle::Particle(int x, int y, ofImage picture)
{
	pos.set(x, y);
	vel.set(0, 0);
	acc.set(0, 0);

	gravity.set(0, 3.0f);

	maxspeed = 10.0f;
	angle = 0.0f;

	life = 60 * 1;
	dead = false;

	image = picture;
}

Particle::~Particle()
{
}

void Particle::update() 
{
	life--;											// Subtract life
	if (life <= 0)
		dead = true;

	addForce(gravity);
	if (pos.y > ofGetHeight() * 0.5f)
	{
		acc *= 0.2f;
		vel *= 0.4f;
	}

	vel += acc;                                     // Update velocity
    vel.x = ofClamp(vel.x, -maxspeed, maxspeed);    // Limit speed
    vel.y = ofClamp(vel.y, -maxspeed, maxspeed);    // Limit speed
    pos += vel;                                     // location of the boids
    acc.set(0,0);                                   // Reset accelertion to 0 each cycle
}

void Particle::draw()
{
    ofPushStyle();
		ofFill();
		ofPushMatrix();
			ofTranslate(pos.x, pos.y);
			ofRotateZ(angle);
			if (image.isAllocated()) 
			{
				ofSetColor(255, 255 - life);
				image.draw(0,0, 30, 30);						// Draws the image
			}
			else 
			{
				ofSetColor(255, 0, 0, life - 150);
				ofCircle(0, 0, 10);
			}
		ofPopMatrix();
    ofPopStyle();
}

void Particle::addForce(ofVec2f force)
{
	acc += force;
}

