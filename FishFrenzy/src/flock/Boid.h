#ifndef BOID_H
#define BOID_H

#include "ofxBox2d.h"
#include "ofMain.h"

//superclass Boid for the agents
class Boid : public ofxBox2dRect
{
public:
    //constructor
    Boid();
    //constructor with given parameters for the position
    Boid(int x, int y);

    //methods
    void updateBoid(vector<ofPtr<Boid>> boids);         //updates the postion of the Boid boids
    void draw();                                    //draws the boids
    void seek(ofVec2f target, float force);                      //function for searching the other Boid boids target
    void avoid(ofVec2f target, float force);                     //function for avoiding an enemy
    void arrive(ofVec2f target);                    //function for arrival to the target

    void flock(vector<ofPtr<Boid>> boids);          //function for flocking
	void UpdateLife();

    ofVec2f steer(ofVec2f target, bool slowdown);   //2D vector which give the direction
    ofVec2f separate(vector<ofPtr<Boid>> boids);    //2D vector for separation between boids
    ofVec2f align(vector<ofPtr<Boid>> boids);       //2D vector for aligning to the properties of the other boids
    ofVec2f cohesion(vector<ofPtr<Boid>> boids);    //2D vector for the solidarity of the boids swarm
    ofVec2f acc;									//2D vector variables for the location, velocity and acceleration
	
    float maxforce;
    float maxspeed;

	int age;
	int maxAge;
	bool isDead;

	ofVec2f size;
};

#endif
