#include "olcPixelGameEngine.h"
#include "MovementEngine.h"

#include <vector>

#pragma once

class Ball
{
protected:
	olc::vd2d m_pos;
	olc::vd2d m_vel{ 50.f, 50.f };
	int32_t rad{ 7 };
	friend class MovementEngine;

public:
	Ball(double x, double y) : m_pos(olc::vd2d(x, y)), m_vel(olc::vd2d(0, 0)) {}
	Ball(olc::vd2d pos, olc::vd2d vel) : m_pos(pos), m_vel(vel) {}

	// Methods
	// Drawing
	void SelfDraw(olc::PixelGameEngine* game) const;
	void SelfDraw(olc::PixelGameEngine* game, olc::Pixel p) const;
	// Old Change Position
	void ChangePos(olc::PixelGameEngine* game, float fElapsedTime, MovementEngine* engine);
	// Reset to Initial Parameters
	void Reset(double x, double y);

	virtual std::vector<olc::vd2d> Choords() const= 0;
};

class GravityBall : public Ball
{
private:
	olc::vd2d m_gravity = { 0.0, 10.f };
	double m_attr = 0.00001;

public:
	// constructor
	GravityBall(double x, double y) : Ball(x, y){}

	// Methods
	// This change the position, it is implemented using Euler Integration.... Next Version will use Movement Engine
	void ChangePos(olc::PixelGameEngine* game, float fElapsedTime, MovementEngine* engine);
	// Print to screen the ball stats
	void DisplayStats(olc::PixelGameEngine* game) const;
	// Checks for collisions
	bool CheckFloorCollision(olc::PixelGameEngine* game) const;
	bool CheckLateralCollision(olc::PixelGameEngine* game) const;
	// Managing Collisions
	void ManageCollision(olc::PixelGameEngine* game, float fElapsedTime);
	std::array<olc::vd2d, 2> Equation(float fElapsedTime, olc::vd2d position, olc::vd2d speed) const;
	// Methods to group stats in a choordinates vector... next revision maybe will use array instead of vector
	std::vector<olc::vd2d> Choords() const override;
};
