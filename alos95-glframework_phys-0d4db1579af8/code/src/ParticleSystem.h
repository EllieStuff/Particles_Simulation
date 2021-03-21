#pragma once
#include <glm\glm.hpp>


namespace LilSpheres {
	extern const int maxParticles;
	extern int firstParticleIdx;
	extern int particleCount;
	extern void updateParticles(int startIdx, int count, float* array_data);
}


class ParticleSystem {
private:
	//std::vector<Particle> particles;
	//int margin = 10;
	glm::vec3* positions;
	int maxParticles = 200;
	float* age;

public:
	int currParticles = 0;
	float emissionRate = 4;

	ParticleSystem() {};
	ParticleSystem(int _numParticles, glm::vec3 _pos = glm::vec3(0, 0, 0));

	void UpdateParticle(int idx, glm::vec3 newPos);

	void updateLilSpheres();

	int GetMaxParticles();

	void spawnParticle(glm::vec3 _pos);

	void updateAge(float dt);

	void destroyOldParticles(float maxAge);
};