#pragma once
#include "ofxbox2drect.h"
class PlayerTwo : public ofxBox2dRect
{
public:
	PlayerTwo(void);
	~PlayerTwo(void);
	void draw();

protected:
	ofImage image;

};

