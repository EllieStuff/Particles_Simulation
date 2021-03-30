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
float maxAge = 3.f;
float currTime = 0;
//float emissionRate = 4;

bool show_test_window = false;
void GUI() {
	bool show = true;
	ImGui::Begin("Physics Parameters", &show, 0);

	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate
		ImGui::InputFloat("Emission Rate", &ps.emissionRate, 1.f);
		Exemple_GUI();
	}

	ImGui::End();
}

void PhysicsInit() {
	//Exemple_PhysicsInit();

	renderParticles = true;
	ps = ParticleSystem(100);
	renderSphere = true;
	Sphere::setupSphere(glm::vec3(-2, 5, 0), 2.f);
	//Sphere::setupSphere(glm::vec3 pos, float radius);
}

void spawn(/*float dt,*/ glm::vec3 initPos = glm::vec3(0, 0, 0), glm::vec3 initVelocity = glm::vec3(0, 0, 0)) {
	/*float x = nextParticleIdx * cos(angle) / 20.f;
	float y = nextParticleIdx / 10.f;
	float z = nextParticleIdx * sin(angle) / 20.f;*/

	ps.UpdateParticle(nextParticleIdx, initPos, initVelocity);
	//angle += dt * ps.emissionRate;

	ps.spawnParticle(initPos, initVelocity);

	nextParticleIdx++;
}

void UpdateFountain(float dt) {
	ps.destroyOldParticles(maxAge);
	
	if (currTime >= 0.1f) {
		currTime = 0;
		if (nextParticleIdx < ps.GetMaxParticles()) {
			for (int i = 0; i < ps.emissionRate; i++)
			{
				spawn(glm::vec3(0, 0, 0), glm::vec3(Utils::Randomize(-5, 5), Utils::Randomize(-10, -15), Utils::Randomize(-5, 5)));
			}
		}
	}

	Sphere::updateSphere(glm::vec3(-2, 5, 0), 2.f);
	Sphere::drawSphere();
	ps.updateLilSpheres();
	ps.updateAge(dt);
	ps.UpdateSpeed(dt);
}

void UpdateCascade(float dt) {
	ps.destroyOldParticles(maxAge);

	if (nextParticleIdx < ps.GetMaxParticles()) {
		for (int i = 0; i < ps.emissionRate; i++)
		{
			spawn(glm::vec3(Utils::Randomize(-3, 1), 10.f, Utils::Randomize(-1, 1)), glm::vec3(Utils::Randomize(-1, 1), Utils::Randomize(0, 1), Utils::Randomize(-1, 1)));
		}
	}
	Sphere::updateSphere(glm::vec3(-2, 5, 0), 2.f);
	Sphere::drawSphere();
	ps.updateLilSpheres();
	ps.updateAge(dt);
	ps.UpdateSpeed(dt);
}

void PhysicsUpdate(float dt) {
	currTime += dt;

	UpdateFountain(dt);
	//UpdateCascade(dt);

	/*ps.destroyOldParticles(maxAge);

	if (nextParticleIdx < ps.GetMaxParticles()) {
		spawn(dt);
	}

	ps.updateLilSpheres();
	ps.updateAge(dt);
	ps.UpdateSpeed(dt);*/
}



void PhysicsCleanup() {
	//Exemple_PhysicsCleanup();



}