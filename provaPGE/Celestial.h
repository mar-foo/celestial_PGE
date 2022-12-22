#pragma once
#include "Balls.h"
#include "MovementEngine.h"

#include <vector>

namespace Celestial {
	constexpr double G = 6.67e-11;

	class Celestial : public Ball
	{
	protected:
		const double m_mass{ 1. };

	public:
		Celestial(double x, double y) : Ball(x, y) {}
		Celestial(olc::vd2d pos, olc::vd2d vel, double mass) : Ball(pos, vel), m_mass(mass) {}

		void ChangePos(olc::PixelGameEngine* game, float fElapsedTime);

		std::vector<olc::vd2d> Choords() const override;
	};
}
