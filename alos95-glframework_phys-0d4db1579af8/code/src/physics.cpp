#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include <glm\glm.hpp>
#include "ParticleSystem.h"
#include "Utils.h"

//Exemple
extern void Exemple_GUI();
extern void Exemple_PhysicsInit();
extern void Exemple_PhysicsUpdate(float dt);
extern void Exemple_PhysicsCleanup();


ParticleSystem ps;
float angle = 0, initialAngle = 0;
int nextParticleIdx = 0;
extern bool renderParticles;
extern bool renderSphere;
extern bool renderCapsule;
float maxAge = 30.f;
const int INIT_PARTICLES = 1000;
float currTime = 1.f / ps.emissionRate;
bool emissionType = true;

bool show_test_window = false;
void GUI() {
	bool show = true;
	ImGui::Begin("Physics Parameters", &show, 0);

	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate
		ImGui::SliderFloat("Emission Rate", &ps.emissionRate, 0.f, 10.f);
		ImGui::SliderFloat("Particles emmited per pulse", &ps.particlesForEachEmission, 1.f, 20.f);
		ImGui::Checkbox("Fountain <--On / Off--> Cascade", &emissionType);
		//Exemple_GUI();
	}

	ImGui::End();
}

void PhysicsInit() {
	//Exemple_PhysicsInit();

	renderParticles = true;
	ps = ParticleSystem(INIT_PARTICLES);
	renderSphere = renderCapsule = true;
	Sphere::setupSphere(glm::vec3(-2, 5, 0), 2.f);
	Capsule::setupCapsule(glm::vec3(3, 3, 0), glm::vec3(2, 8, 0), 1.5f);
}

void spawn( glm::vec3 initPos = glm::vec3(0, 0, 0), glm::vec3 initVelocity = glm::vec3(0, 0, 0)) {

	ps.UpdateParticle(nextParticleIdx, initPos, initVelocity);

	ps.spawnParticle(initPos, initVelocity);

	nextParticleIdx++;
}

void UpdateFountain(float dt) {
	if (currTime >= 1.f / ps.emissionRate) {
		currTime = 0;
		if (nextParticleIdx < ps.GetMaxParticles()) {
			for (int i = 0; i < ps.particlesForEachEmission; i++)
			{
				spawn(glm::vec3(0, 0, 0), glm::vec3(Utils::Randomize(-5, 5), Utils::Randomize(-10, -15), Utils::Randomize(-5, 5)));
			}
		}
	}
}

void UpdateCascade(float dt) {
	if (currTime >= 1.f / ps.emissionRate) {
		currTime = 0;
		if (nextParticleIdx < ps.GetMaxParticles()) {
			for (int i = 0; i < ps.particlesForEachEmission; i++)
			{
				spawn(glm::vec3(Utils::Randomize(-5, 5), 10.f, Utils::Randomize(-5, 5)), glm::vec3(Utils::Randomize(-1, 1), Utils::Randomize(0, 1), Utils::Randomize(-1, 1)));
			}
		}
	}
}

void PhysicsUpdate(float dt) {
	currTime += dt;
	ps.destroyOldParticles(maxAge);

	if (emissionType)
		UpdateFountain(dt);
	else if (!emissionType)
		UpdateCascade(dt);

	ps.updateLilSpheres();
	ps.updateAge(dt);
	ps.UpdateSpeed(dt);

	Sphere::updateSphere(glm::vec3(-2, 5, 0), 2.f);
	Sphere::drawSphere();
	Capsule::updateCapsule(glm::vec3(3, 3, 0), glm::vec3(3, 7, 0), 1.5f);
	Capsule::drawCapsule();
}



void PhysicsCleanup() {
	//Exemple_PhysicsCleanup();



}