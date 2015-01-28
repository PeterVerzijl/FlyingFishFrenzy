/*
	Player One is the first player that is drawn on the screen.
	A player is a baseball bat image that is derived from ofxBox2DRect
	The player position is changed in ofApp.cpp since it follows an OpenCV blob.
*/

#include "PlayerOne.h"

PlayerOne::PlayerOne(void)
{
	image.loadImage("BatGreen.png");
	setPosition(ofGetScreenWidth()*0.25, ofGetScreenHeight()*0.5);
}

PlayerOne::~PlayerOne(void)
{
}

void PlayerOne::draw()
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