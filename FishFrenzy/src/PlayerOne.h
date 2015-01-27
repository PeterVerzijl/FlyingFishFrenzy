#pragma once
#include "ofxbox2drect.h"
class PlayerOne :public ofxBox2dRect
{
public:
	PlayerOne(void);
	~PlayerOne(void);
	void draw();

protected:
	ofImage image;
};

