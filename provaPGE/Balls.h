#include "olcPixelGameEngine.h"
#include "MovementeEngine.h"

#include <vector>

#pragma once

class Balls
{
protected:
	olc::vd2d m_pos;
	olc::vd2d m_vel{ 50.f, 50.f };
	int32_t rad{ 7 };
	friend class MovementEngine;
	//virtual std::vector<olc::vd2d> operator() (float fElapsedTime, std::vector<olc::vd2d> choord) = 0;

public:
	// Constructor
	Balls(olc::PixelGameEngine* game) {
		m_pos.x = 360 /*game->ScreenWidth() / 2.f*/;
		m_pos.y = 240/*game->ScreenHeight() / 2.f*/;
	}

	Balls(olc::vd2d pos, olc::vd2d vel) : m_pos(pos), m_vel(vel) {}

	// Methods
	//Drawing 
	void SelfDraw(olc::PixelGameEngine* game) const;
	void SelfDraw(olc::PixelGameEngine* game, olc::Pixel p) const;
	//Old Change Position
	void ChangePos(olc::PixelGameEngine* game, float fElapsedTime, MovementEngine* engine);
	//reset to Initial Parameters
	void Reset(olc::PixelGameEngine* game);

	virtual std::vector<olc::vd2d> Choords() const= 0;

	//I don t remember what it does
	void Redo(olc::PixelGameEngine* game);
};

class GravityBalls : public Balls
{
private:
	olc::vd2d m_gravity = { 0.0, 10.f };
	olc::vd2d m_grav_vel = { 0.f, 0.f };
	double m_attr = 0.00001;

public:
	//constructor
	GravityBalls(olc::PixelGameEngine* game) : Balls(game) {}
	//Methods
	//This change the position, it is implemented using Euler Integration.... Next Version will use Movement Engine
	void ChangePos(olc::PixelGameEngine* game, float fElapsedTime, MovementEngine* engine);
	//Print to screen the ball stats
	void DisplayStats(olc::PixelGameEngine* game) const;
	//Checks for collisions
	bool CheckFloorCollision(olc::PixelGameEngine* game) const;
	bool CheckLateralCollision(olc::PixelGameEngine* game) const;
	//Managing Collisions
	void ManageCollision(olc::PixelGameEngine* game, float fElapsedTime);
	//Methods to group stats in a choordinates vector... next revision maybe will use array instead of vector
	std::vector<olc::vd2d> Choords() const override;
};

