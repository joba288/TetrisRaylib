#include <ParticleSystem.h>
#include <raylib.h>
#include <raymath.h>

namespace Core
{
	void ParticleSystem::addParticle(const Particle& p)
	{
		m_Particles.push_back(p);
	}

	void ParticleSystem::drawParticles()
	{
		for (const auto& p : m_Particles)
		{
			float t = p.age / p.lifetime;
			Color c = ColorLerp(p.colorStart, p.colorEnd, t);
			Vector2 size = Vector2Lerp(p.sizeStart, p.sizeEnd, t);
			float rot = Lerp(p.rotationStart, p.rotationEnd, t);

			Rectangle rect = { p.pos.x, p.pos.y, size.x, size.y };
			Vector2 origin = { size.x * 0.5f, size.y * 0.5f };

			DrawRectanglePro(rect, origin, rot, c);
		}
	}

	void ParticleSystem::onUpdate(float ts)
	{
		for (auto& p : m_Particles)
		{
			p.pos.x += p.velocity.x * ts;
			p.pos.y += p.velocity.y * ts;

			if (p.age <= p.lifetime)
				p.age += ts;
			else
				m_Particles.erase(
					std::remove_if(m_Particles.begin(), m_Particles.end(),
						[](const Particle& p) { return p.age > p.lifetime; }),
					m_Particles.end());
		}
	}

}