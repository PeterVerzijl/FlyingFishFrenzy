#pragma once
#include "boid.h"
class FishOne : public Boid
{
public:
    // constructor with given parameters for the position
    FishOne(int x, int y);
	// Destructor
	~FishOne(void);
	
	ofImage image;

	void draw();

	int life;

	float angle;
	float targetAngle;

protected:
private:
};