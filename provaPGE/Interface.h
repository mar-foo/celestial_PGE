#include "MovementEngine.h"
#include "olcPixelGameEngine.h"

#include "Balls.h"

#ifndef __INTERFACE__
#define __INTERFACE__

enum Integrators {
	EULER = 1,
	RK4,
	CELESTIAL,
};

class Celestial_Simulation : public olc::PixelGameEngine
{
protected:
	GravityBall* ball;
	enum Integrators mode = EULER;
	MovementFunction engine;

public:
	Celestial_Simulation()
	{
		ball = new GravityBall(ScreenWidth() / 2., ScreenHeight() / 2.);
		sAppName = "Proviamo";
	}

        ~Celestial_Simulation() {
		if (ball)
			delete(ball);
	};

public:
	//creation
	bool OnUserCreate() override;
	//frame update
	bool OnUserUpdate(float fElapsedTime) override;
};

#endif
