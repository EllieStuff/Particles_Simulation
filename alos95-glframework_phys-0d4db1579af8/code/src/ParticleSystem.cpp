#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int _numParticles, glm::vec3 _pos)
{
	currParticles = _numParticles;
	if (currParticles > maxParticles) currParticles = maxParticles;
	positions = new glm::vec3[maxParticles];
	age = new float[maxParticles];
}

void ParticleSystem::UpdateParticle(int idx, glm::vec3 newPos)
{
	positions[idx] = newPos;
}

void ParticleSystem::updateLilSpheres()
{
	LilSpheres::firstParticleIdx = 0;
	LilSpheres::particleCount = currParticles;
	float* first_float = &(positions[0].x);

	LilSpheres::updateParticles(0, currParticles, first_float);
}

int ParticleSystem::GetMaxParticles()
{
	return maxParticles;
}

void ParticleSystem::spawnParticle(glm::vec3 _pos)
{
	if (currParticles < maxParticles) {
		UpdateParticle(currParticles, _pos);
		age[currParticles] = 0;

		currParticles++;
	}
}

void ParticleSystem::updateAge(float dt)
{
	for (int i = 0; i < currParticles; i++) {
		age[i] += dt;
	}
}

template <typename T>
void shiftLeft(int count, T* arr, int positionToShift) {
	for (int i = 0; i < count - positionToShift; i++) {
		arr[i] = arr[i + positionToShift];
	}
}

void ParticleSystem::destroyOldParticles(float maxAge)
{
	int positionToShift = 0;
	int currentAge = age[0];
	while (currentAge > maxAge && positionToShift <= currParticles) {
		positionToShift++;
		currentAge = age[positionToShift];
	}

	shiftLeft(currParticles, positions, positionToShift);
	shiftLeft(currParticles, age, positionToShift);

	currParticles -= positionToShift;

	for (int i = 0; i < currParticles; i++) {
		if (age[i] > maxAge) {
			float x = positions[i].x;
			float z = positions[i].z;

			UpdateParticle(i, glm::vec3(x, 0.1f, z));
		}
	}
}
