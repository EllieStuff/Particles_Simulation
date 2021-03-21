#pragma once
#include <glm\glm.hpp>


namespace LilSpheres {
	extern const int maxParticles;
	extern int firstParticleIdx;
	extern int particleCount;
	extern void updateParticles(int startIdx, int count, float* array_data);
}

struct Particle {
	glm::vec3 pos;
	glm::vec3 speed;
	glm::vec3 acc;
	float age;
	Particle() {};

};


class ParticleSystem {
private:
	//std::vector<Particle> particles;
	//int margin = 10;

	int maxParticles = 200;
	Particle* particles;
	glm::vec3* auxPosArr;
	float bounceCoef = 0.6f;
	float fricCoef = 0.6f;
	glm::vec3 gravity = glm::vec3(0, -9.81f, 0);

	//glm::vec3* positions;
	//float* age;

public:
	int currParticles = 0;
	float emissionRate = 4;

	ParticleSystem() {};
	ParticleSystem(int _numParticles, glm::vec3 _pos = glm::vec3(0, 0, 0));

	void UpdateParticle(int idx, glm::vec3 newPos, glm::vec3 newVel);

	void updateLilSpheres();

	int GetMaxParticles();

	void spawnParticle(glm::vec3 _pos, glm::vec3 initVelocity);

	void updateAge(float dt);

	void destroyOldParticles(float maxAge);

	void UpdateSpeed(float dt);

};