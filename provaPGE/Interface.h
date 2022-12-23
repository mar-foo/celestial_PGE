#include "MovementEngine.h"
#include "olcPixelGameEngine.h"

#include "Balls.h"
#include "Celestial.h"

#include <vector>

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
	std::vector<Celestial::Celestial> celestials = std::vector<Celestial::Celestial>();
	enum Integrators mode = EULER;
	MovementFunction engine;

public:
	Celestial_Simulation()
	{
                celestials.push_back(Celestial::Celestial(
                    olc::vd2d(ScreenWidth() / 2., ScreenHeight() / 2.),
		    olc::vd2d(0.0, 0.0),
                    10.));
                celestials.push_back(Celestial::Celestial(
                    olc::vd2d(ScreenWidth() / 4., ScreenHeight() / 3.),
		    olc::vd2d(15.0, 0.0),
		    15.));
		sAppName = "Proviamo";
	}

        ~Celestial_Simulation() {}

public:
	//creation
	bool OnUserCreate() override;
	//frame update
	bool OnUserUpdate(float fElapsedTime) override;
	void UpdateGravityFields(void);
};

#endif
