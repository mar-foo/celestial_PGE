#include "olcPixelGameEngine.h"

#include <vector>
#include <functional>

#include "VectorOp.h"

#pragma once

class MovementEngine
{
public:
	virtual void movement(float fElapsedTime, olc::vd2d& position, olc::vd2d & speed, std::function<std::array<olc::vd2d, 2> (float, olc::vd2d, olc::vd2d)>) = 0;

};

class Euler : public MovementEngine
{
public:
	void movement(float fElapsedTime, olc::vd2d& position, olc::vd2d & speed, std::function<std::array<olc::vd2d, 2> (float, olc::vd2d, olc::vd2d)>) override;
};

class RK4 : public MovementEngine
{
public:
	void movement(float fElapsedTime, olc::vd2d& position, olc::vd2d& velocity, std::function<std::array<olc::vd2d, 2> (float, olc::vd2d, olc::vd2d)>) override;
};
