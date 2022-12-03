#include "olcPixelGameEngine.h"

#include "Balls.h"

#ifndef __INTERFACE__
#define __INTERFACE__

class Interface : public olc::PixelGameEngine
{
protected:
	GravityBalls ball{ this };
	int mode = 1;

public:
	//constructor
	Interface()
	{
		sAppName = "Proviamo";
	}

public:
	//creation
	bool OnUserCreate() override;
	//frame update
	bool OnUserUpdate(float fElapsedTime) override;


};

#endif