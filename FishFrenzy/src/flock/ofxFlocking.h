/*
 *  Flock.h
 *
 *  Created by Jeffrey Crouse on 3/30/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *  Modified by Rick Companje
 *  Programming with Structures Project : Hauke Sandhaus & Karolina Niechwiadowicz
 */

#pragma once

#include "ofMain.h"
#include "Boid.h"

class ofxFlocking
{
public:
    //methods
    void update();
    void draw();
    void addBoid();
    void addBoid(int x, int y);

	vector<ofPtr<Boid>> boids;
};
