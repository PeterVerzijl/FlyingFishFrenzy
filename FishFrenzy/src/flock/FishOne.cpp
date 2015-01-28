/*
	Fish one is derived from the boid class and thus the ofxBox2DRect class.
	Fishes add graphics to the boids, namely an image of a fish.
	The fish rotates (with linear interpolation) towards it's moving direction.
*/

#include "FishOne.h"

FishOne::FishOne(int x, int y) 
{
	image.loadImage("fishone.png");         // load the image for Fishone

	setPosition(x, y);						// sets starting location passed through value.
	size.set(22.5f, 45.0f);

	angle= 0;
	targetAngle = 0;
}


FishOne::~FishOne(void)
{
}



void FishOne::draw() 
{
	
	float a = (float)atan2(-getVelocity().y, getVelocity().x);
    float theta =  -1.0*a;
    float targetAngle = ofRadToDeg(theta)+90;
	angle = ofLerpDegrees(angle, targetAngle, 0.05f);				// Smooth rotation

    ofPushStyle();
		ofFill();
		ofPushMatrix();
			ofTranslate(getPosition().x, getPosition().y);
			ofRotateZ(angle);
			image.draw(0,0, size.x, size.y);						// draws the image on Fishone
		ofPopMatrix();	
    ofPopStyle();
}
