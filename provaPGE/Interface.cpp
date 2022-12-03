#include "Interface.h"

bool Interface::OnUserCreate()
{

	return true;
}

bool Interface::OnUserUpdate(float fElapsedTime)
{
	/* V1
		for (int i = 0; i < ScreenWidth(); i++)
		{
			for (int j = 0; j < ScreenHeight(); j++)
			{
				Draw(i, j, olc::Pixel(rand() % 256, rand() % 256, rand() % 256, rand() % 256));
			}
		}
	*/
	DrawLineDecal({ 0.f, ScreenHeight() / 2.f }, { (float)ScreenWidth(), ScreenHeight() / 2.f });
	DrawLineDecal({ ScreenWidth() / 2.f, 0.f }, { ScreenWidth() / 2.f, ScreenHeight() * 1.f });

	if (GetKey(olc::Key::K1).bPressed) mode = 1;
	if (GetKey(olc::Key::K2).bPressed) mode = 2;
	if (GetKey(olc::Key::K3).bPressed) mode = 3;


	switch (mode)
	{
	case 1:
		DrawStringDecal({ 5., 25. }, "Mode " + std::to_string(mode) + ":\tEuler", olc::GREEN);
		Clear(olc::BLACK);
		ball.ChangePos(this, fElapsedTime);
		break;
	case 2:
		DrawStringDecal({ 5., 25. }, "Mode " + std::to_string(mode) + ":\tRK4", olc::GREEN);
		Clear(olc::DARK_BLUE);
		break;
	case 3:
		Clear(olc::WHITE);
		break;
	}

	ball.SelfDraw(this, olc::RED);
	ball.DisplayStats(this);

	/* V2
	ball.Redo(this);
*/

	if (GetKey(olc::Key::SPACE).bPressed) ball.Reset(this);

	if (GetKey(olc::Key::F4).bPressed) return false;

	return true;
}


