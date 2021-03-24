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
		particles[i].prevPos = particles[i].pos;

		particles[i].acc = gravity;
		particles[i].speed += particles[i].acc * dt;
		particles[i].pos += particles[i].speed * dt;

		//Check collisions
		//Fem el cross product per trobar la normal
		//Floor
		glm::vec3 normal = glm::normalize(CalculatePlaneNormal(boxVertex[3], boxVertex[2], boxVertex[0]));
		float planeD = -(normal.x * boxVertex[3].x + normal.y * boxVertex[3].y + normal.z * boxVertex[3].z);
		float distance = (abs(normal.x + normal.y + normal.z + planeD))/sqrt(pow(normal.x, 2)+ pow(normal.y, 2)+ pow(normal.z, 2));
		if (HasCollided(particles[i].prevPos, particles[i].pos, normal, distance) && particles[i].age > 0)
		{
			particles[i].pos = particles[i].pos - (1 + bounceCoef) * (glm::dot(normal, particles[i].pos) + distance) * normal;
			particles[i].speed = particles[i].speed - (1 + bounceCoef) * (glm::dot(normal, particles[i].speed)) * normal;
			//printf("PrevPos: %f \n", particles[i].prevPos.y);
			//printf("Pos: %f \n", particles[i].pos.y);
		}
	}
}

glm::vec3 ParticleSystem::CalculatePlaneNormal(glm::vec3 initVertex, glm::vec3 finalVertex1, glm::vec3 finalVertex2)
{
	glm::vec3 vector1 = finalVertex1 - initVertex;
	glm::vec3 vector2 = finalVertex2 - initVertex;

	return glm::cross(vector1, vector2);
}

bool ParticleSystem::HasCollided(glm::vec3 prevParticlePos, glm::vec3 particlePos, glm::vec3 normal, float distance)
{
	normal = glm::normalize(normal);
	return ((glm::dot(normal, prevParticlePos) + distance) * (glm::dot(normal, particlePos) + distance)) <= 0;
}
