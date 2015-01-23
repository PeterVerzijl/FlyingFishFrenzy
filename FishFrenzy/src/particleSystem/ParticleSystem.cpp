#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
}


ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::emit()
{
	for (int i = 0; i < particles.size(); i++)
	{
		ofVec2f direction = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
		particles.at(i)->addForce(direction * 20.0f);
	}
}

void ParticleSystem::update()
{
	ofPtr<Particle> p;
	for (int i = 0; i < particles.size(); i++)
	{
		p = particles.at(i);
		p->update();
		p->draw();
		if (p->dead)
			particles.erase(particles.begin() + i);
	}
}