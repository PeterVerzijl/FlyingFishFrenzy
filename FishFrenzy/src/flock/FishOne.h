#pragma once
#include "c:\users\user\of_v0.8.4_vs_release\apps\myapps\fishfrenzy\src\flock\boid.h"
class FishOne : public Boid
{
public:
	// constructor
    FishOne();
    // constructor with given parameters for the position
    FishOne(int x, int y);
	// Destructor
	~FishOne(void);
	
	ofImage image;

	void draw();

protected:
private:
};