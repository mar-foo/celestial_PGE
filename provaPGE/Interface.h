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
	GravityBalls ball{ this };
	enum Integrators mode = EULER;
	bool mode_changed = false;
	MovementEngine* engine;

public:
	//constructor
	Celestial_Simulation()
	{
		sAppName = "Proviamo";
	}

	~Celestial_Simulation() { if (engine) free(engine); };

public:
	//creation
	bool OnUserCreate() override;
	//frame update
	bool OnUserUpdate(float fElapsedTime) override;


};

#endif
