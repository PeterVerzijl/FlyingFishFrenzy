/*
	Player Two is the second player that is drawn on the screen.
	A player is a baseball bat image that is derived from ofxBox2DRect
	The player position is changed in ofApp.cpp since it follows an OpenCV blob.
*/

#include "PlayerTwo.h"

PlayerTwo::PlayerTwo(void)
{
	image.loadImage("BatRed.png");
	setPosition(ofGetScreenWidth()*0.75, ofGetScreenHeight()*0.5);

}


PlayerTwo::~PlayerTwo(void)
{
}

void PlayerTwo::draw()
{

	ofPushStyle();
	ofFill();
	ofSetColor(250,250,250);
	ofPushMatrix();
	ofTranslate(getPosition().x, getPosition().y);
	image.draw(-95,-11,190,21);
	ofPopMatrix();
	ofPopStyle();
}