#pragma once
#include <vector>
#include <raylib.h>


namespace Core
{
	

	struct Particle
	{
		Vector2 pos;
		Vector2 velocity = {0,0};
		Vector2 sizeStart;
		Vector2 sizeEnd;
		Color colorStart = WHITE;
		Color colorEnd = WHITE;
		float age = 0.0f;
		float lifetime = 1.0f;
		float rotationStart = 0.f;
		float rotationEnd = 0.f;
	};

	constexpr int MAX_PARTICLE_COUNT = 100;
	class ParticleSystem
	{
		public:
			ParticleSystem()
			{
				m_Particles.reserve(MAX_PARTICLE_COUNT);
			}
			~ParticleSystem() = default;
			void OnUpdate(float ts);
			void DrawParticles();
			void AddParticle(const Particle& p);
		private:
			std::vector<Particle> m_Particles;
	};
}