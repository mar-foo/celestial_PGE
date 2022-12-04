#include "MovementEngine.h"


void Euler::movement(float fElapsedTime, std::vector<olc::vd2d>& start, std::function< std::vector<olc::vd2d>(float, std::vector<olc::vd2d>)> fun)
{
	start = fun(fElapsedTime, start);
}

void RK4::movement(float fElapsedTime, std::vector<olc::vd2d>& start, std::function< std::vector<olc::vd2d>(float, std::vector<olc::vd2d>)> fun)
{
	std::vector<olc::vd2d> k_1 = fun(0., start );
	std::vector<olc::vd2d> k_2 = fun(fElapsedTime/2.f, start + fElapsedTime/2.f * k_1);
	std::vector<olc::vd2d> k_3 = fun(fElapsedTime/2.f, start + fElapsedTime/2.f * k_2);
	std::vector<olc::vd2d> k_4 = fun(fElapsedTime, start + fElapsedTime * k_3);
 	start =  (k_1 + k_2 * 2 + k_3 * 2. + k_4) * (fElapsedTime / 6.);
}
