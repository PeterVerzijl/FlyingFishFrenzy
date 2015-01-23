#include "FishTwo.h"

FishTwo::FishTwo(int x, int y) : Boid(x, y)
{
	image.loadImage("fishtwo.png");         // load the image for Fishone

	setPosition(x, y);  // sets starting random location
	size.set(30, 60);

	angle= 0;
	targetAngle = 0;
}

FishTwo::~FishTwo(void)
{
}

void FishTwo::draw() 
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
			image.draw(0,0, size.x, size.y);       // draws the image on Fishone
		ofPopMatrix();
    ofPopStyle();
}