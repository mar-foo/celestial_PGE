#include "olcPixelGameEngine.h"

#include <vector>
#include <functional>

#include "VectorOp.h"

#pragma once

class MovementEngine
{
protected:
public:
	virtual void movement(float fElapsedTime, std::vector<olc::vd2d>& start, std::function< std::vector<olc::vd2d> (float, std::vector<olc::vd2d> )>) = 0;

};

class Euler : public MovementEngine
{
public:
	void movement(float fElapsedTime, std::vector<olc::vd2d>& start, std::function < std::vector<olc::vd2d>(float, std::vector<olc::vd2d>)>) override;
};

class RK4 : public MovementEngine
{
	void movement(float fElapsedTime, std::vector<olc::vd2d>& start, std::function < std::vector<olc::vd2d>(float, std::vector<olc::vd2d>)>) override;
};

