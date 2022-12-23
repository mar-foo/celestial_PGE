#include "Celestial.h"

std::vector<olc::vd2d> Celestial::Celestial::Choords() const
{
	return std::vector<olc::vd2d>{m_pos, m_vel};
}

void Celestial::Celestial::ChangePos(olc::PixelGameEngine *game, float fElapsedTime, MovementFunction engine)
{
	engine(fElapsedTime, m_pos, m_vel, [this](float fElapsedTime, olc::vd2d position, olc::vd2d speed) {
		return this->Equation(fElapsedTime, position, speed);
	});
}

olc::vd2d Celestial::Celestial::FieldOn(Celestial object)
{
	olc::vd2d difference = this->m_pos - object.m_pos;
	double distance = difference.mag();
	return G * this->m_mass * difference / distance / distance / distance;
}

std::array<olc::vd2d, 2> Celestial::Celestial::Equation(float fElapsedTime,
                                                        olc::vd2d position,
                                                        olc::vd2d speed) const
{
	std::array<olc::vd2d, 2> res = {
		olc::vd2d {
			position.x + speed.x * fElapsedTime,
			position.y + speed.y * fElapsedTime,
		},
		olc::vd2d {
			speed.x + this->m_gravity.x * this->m_mass * fElapsedTime,
			speed.y + this->m_gravity.y * this->m_mass * fElapsedTime,
		}
	};
	return res;
}
