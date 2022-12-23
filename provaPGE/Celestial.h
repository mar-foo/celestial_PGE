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
                olc::vd2d m_gravity;

	public:
		Celestial(double x, double y, double mass) : Ball(x, y), m_mass(mass) {}
		Celestial(olc::vd2d pos, olc::vd2d vel, double mass) : Ball(pos, vel), m_mass(mass) {}

		void ChangePos(olc::PixelGameEngine* game, float fElapsedTime, MovementFunction engine);
		olc::vd2d Gravity() const { return m_gravity; }
		void SetGravity(olc::vd2d g) { m_gravity = g; };
                void SetGravity(double x, double y) {
			SetGravity(olc::vd2d(x, y));
		}
		olc::vd2d FieldOn(Celestial celestial);
		std::array<olc::vd2d, 2> Equation(float fElapsedTime, olc::vd2d position, olc::vd2d speed) const;

		std::vector<olc::vd2d> Choords() const override;
	};
}
