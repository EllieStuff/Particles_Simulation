#pragma once
#include <glm\glm.hpp>


namespace LilSpheres {
	extern const int maxParticles;
	extern int firstParticleIdx;
	extern int particleCount;
	extern void updateParticles(int startIdx, int count, float* array_data);
}

struct Particle {
	glm::vec3 prevPos;
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

	int maxParticles = 400;
	Particle* particles;
	glm::vec3* auxPosArr;
	float bounceCoef = 0.2f;
	float fricCoef = 0.6f;
	float mass = 1.f;
	glm::vec3 gravity = glm::vec3(0, -9.81f * mass, 0);

	//glm::vec3* positions;
	//float* age;

	glm::vec3 boxVertex[8] = {
		glm::vec3(-4.f,  1.f, -4.f),
		glm::vec3(4.f,  1.f, -4.f),
		glm::vec3(4.f,  1.f,  5.f),
		glm::vec3(-4.f,  1.f,  5.f),
		glm::vec3(-4.f, 10.f, -4.f),
		glm::vec3(4.f, 10.f, -4.f),
		glm::vec3(4.f, 10.f,  5.f),
		glm::vec3(-4.f, 10.f,  5.f)
	};

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

	glm::vec3 CalculatePlaneNormal(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3);

	bool HasCollided(glm::vec3 prevParticlePos, glm::vec3 particlePos, glm::vec3 normal, float distance);

};