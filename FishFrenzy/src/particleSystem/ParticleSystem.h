#ifndef PARTICLESYSTEM_HEADER
#define PARTICLESYSTEM_HEADER

#include "ofMain.h"
#include "Particle.h"

#pragma once
class ParticleSystem 
{
public:
	ParticleSystem();
	~ParticleSystem();
	void emit();
	void update();

	vector<ofPtr<Particle>> particles;
};

#endif