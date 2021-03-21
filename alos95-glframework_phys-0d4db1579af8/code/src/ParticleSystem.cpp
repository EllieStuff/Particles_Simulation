#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int _numParticles, glm::vec3 _pos)
{
	currParticles = _numParticles;
	if (currParticles > maxParticles) currParticles = maxParticles;
	particles = new Particle[maxParticles];
	auxPosArr = new glm::vec3[maxParticles];
	/*positions = new glm::vec3[maxParticles];
	age = new float[maxParticles];*/
}

void ParticleSystem::UpdateParticle(int idx, glm::vec3 newPos, glm::vec3 newVel)
{
	particles[idx].pos = newPos;
	particles[idx].speed = newVel;
	//positions[idx] = newPos;
}

void ParticleSystem::updateLilSpheres()
{
	LilSpheres::firstParticleIdx = 0;
	LilSpheres::particleCount = currParticles;
	//float* first_float = &(positions[0].x);

	for (int i = 0; i < maxParticles; i++) {
		auxPosArr[i] = particles[i].pos;
	}
	float* first_float = &(auxPosArr[0].x);

	LilSpheres::updateParticles(0, currParticles, first_float);
}

int ParticleSystem::GetMaxParticles()
{
	return maxParticles;
}

void ParticleSystem::spawnParticle(glm::vec3 _pos, glm::vec3 initVelocity = glm::vec3(0, 0, 0))
{
	if (currParticles < maxParticles) {
		UpdateParticle(currParticles, _pos, initVelocity);
		particles[currParticles].age = 0;

		currParticles++;
	}
}

void ParticleSystem::updateAge(float dt)
{
	for (int i = 0; i < currParticles; i++) {
		particles[i].age += dt;
	}
}

template <typename T>
void shiftLeft(int count, T* arr, int positionToShift) {
	for (int i = 0; i < count - positionToShift; i++) {
		arr[i] = arr[i + positionToShift];
	}
}
//void shiftLeft(int count, Particle* arr, int positionToShift) {
//	for (int i = 0; i < count - positionToShift; i++) {
//		arr[i] = arr[i + positionToShift];
//	}
//}

void ParticleSystem::destroyOldParticles(float maxAge)
{
	int positionToShift = 0;
	int currentAge = particles[0].age;
	while (currentAge > maxAge && positionToShift <= currParticles) {
		positionToShift++;
		currentAge = particles[positionToShift].age;
	}

	shiftLeft(currParticles, particles, positionToShift);
	/*shiftLeft(currParticles, positions, positionToShift);
	shiftLeft(currParticles, age, positionToShift);*/

	currParticles -= positionToShift;

	for (int i = 0; i < currParticles; i++) {
		if (particles[i].age > maxAge) {
			float x = particles[i].pos.x;
			float z = particles[i].pos.z;

			UpdateParticle(i, glm::vec3(x, 0.1f, z), glm::vec3(0, 0, 0));
		}
	}
}

void ParticleSystem::UpdateSpeed(float dt)
{
	for (int i = 0; i < maxParticles; i++) {
		particles[i].acc = gravity;
		particles[i].speed += particles[i].acc * dt;
		particles[i].pos += particles[i].speed * dt + (particles[i].acc * (float)pow(dt, 2)) / 2.f;
	}
}
