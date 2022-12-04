#include "olcPixelGameEngine.h"
#include "MovementEngine.h"


void Euler::movement(float fElapsedTime, olc::vd2d& position, olc::vd2d& speed, std::function<std::array<olc::vd2d, 2> (float, olc::vd2d, olc::vd2d)> fun)
{
	std::array<olc::vd2d, 2> res = fun(fElapsedTime, position, speed);
	position = res[0];
	speed = res[1];
}

void RK4::movement(float fElapsedTime, olc::vd2d& position, olc::vd2d& speed, std::function<std::array<olc::vd2d, 2> (float, olc::vd2d, olc::vd2d)> fun)
{
	std::array<olc::vd2d, 2> k_1 = fun(0., position, speed);
	std::array<olc::vd2d, 2> k_2 = fun(fElapsedTime/2.f, position + fElapsedTime/2.f * k_1[0], speed + fElapsedTime/2.f * k_1[1]);
	std::array<olc::vd2d, 2> k_3 = fun(fElapsedTime/2.f, position + fElapsedTime/2.f * k_2[0], speed + fElapsedTime/2.f * k_2[1]);
	std::array<olc::vd2d, 2> k_4 = fun(fElapsedTime, position + fElapsedTime * k_3[0], speed + fElapsedTime * k_3[1]);
 	position =  (k_1[0] + k_2[0] * 2 + k_3[0] * 2. + k_4[0]) * (fElapsedTime / 6.);
	speed =  (k_1[1] + k_2[1] * 2 + k_3[1] * 2. + k_4[1]) * (fElapsedTime / 6.);
}
