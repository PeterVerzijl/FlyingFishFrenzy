#pragma once
#include "boid.h"
class FishOne : public Boid
{
public:
    // constructor with given parameters for the position
    FishOne(int x, int y);
	// Destructor
	~FishOne(void);
	void draw();

private:
	ofImage image;
	int life;
	float angle;
	float targetAngle;
};