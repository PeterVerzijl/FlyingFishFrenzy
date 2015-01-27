#pragma once
#include "ofMain.h"
#include "Boid.h"

class FishTwo :	public Boid
{
public:
	// Constructor with given parameters for position
	FishTwo(int x, int y);
	// Destructor
	~FishTwo(void);
	void draw();

private:
	ofImage image;
	float angle;
	float targetAngle;
};

