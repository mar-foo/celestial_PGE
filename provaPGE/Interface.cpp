#include "Interface.h"
#include "MovementEngine.h"

bool Celestial_Simulation::OnUserCreate()
{
	switch (mode)
	{
	case EULER:
		this->engine = euler;
		break;
	case RK4:
		this->engine = rk4;
		break;
	}

	return true;
}

bool Celestial_Simulation::OnUserUpdate(float fElapsedTime)
{
	// Adding a Grid
	DrawLineDecal({ 0.f, ScreenHeight() / 2.f }, { (float)ScreenWidth(), ScreenHeight() / 2.f });
	DrawLineDecal({ ScreenWidth() / 2.f, 0.f }, { ScreenWidth() / 2.f, ScreenHeight() * 1.f });

        if (mode != EULER && GetKey(olc::Key::K1).bPressed)
	{
		/* Testing Euler Integration Methods */
		mode = EULER;
		engine = euler;
	}
        if (mode != RK4 && GetKey(olc::Key::K2).bPressed)
	{
		mode = RK4;
		engine = rk4;
	}
	if (GetKey(olc::Key::K3).bPressed)
	{
		mode = CELESTIAL;
	}

	switch (mode)
	{
	case EULER:
		DrawStringDecal({ 5., 25. }, "Mode " + std::to_string(mode) + ":\tEuler", olc::GREEN);
		Clear(olc::BLACK);
		break;
	case RK4:
		/* Testing Runge Kutta 4 Integration Methods */
		DrawStringDecal({ 5., 25. }, "Mode " + std::to_string(mode) + ":\tRK4", olc::GREEN);
		Clear(olc::DARK_BLUE);
		break;
	case CELESTIAL:
		/* Celestial Movement  WIP */
		Clear(olc::WHITE);
		break;
	}

	this->UpdateGravityFields();
	for (auto celestial : this->celestials) {
		celestial.ChangePos(this, fElapsedTime, this->engine);
		celestial.SelfDraw(this, olc::RED);
	}

	// Exit Button
	if (GetKey(olc::Key::F4).bPressed) return false;

	return true;
}

void Celestial_Simulation::UpdateGravityFields(void)
{
	int i, j;
	for (i = 0; i < this->celestials.size(); i++) {
		this->celestials[i].SetGravity(olc::vd2d(0., 0.));
		for (j = 0; j < this->celestials.size(); j++) {
			if (j == i) continue;
                        this->celestials[i].SetGravity(
                            this->celestials[i].Gravity() +
                            this->celestials[j].FieldOn(this->celestials[i]));
		}
	}
}
