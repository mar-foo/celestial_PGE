#include "olcPixelGameEngine.h"

#include <vector>
#include <functional>

#include "VectorOp.h"

#pragma once

typedef std::function < void(float,
                             olc::vd2d &,
                             olc::vd2d &,
                             std::function<std::array<olc::vd2d, 2> (float, olc::vd2d, olc::vd2d)>)> MovementFunction;

void euler(float fElapsedTime, olc::vd2d& position, olc::vd2d& speed, std::function<std::array<olc::vd2d, 2> (float, olc::vd2d, olc::vd2d)> fun);
void rk4(float fElapsedTime, olc::vd2d& position, olc::vd2d& speed, std::function<std::array<olc::vd2d, 2> (float, olc::vd2d, olc::vd2d)> fun);
