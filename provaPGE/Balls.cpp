#include "Balls.h"

// Draws the Ball, takes in input the game engine
// this version randomizes ball color
void Balls::SelfDraw(olc::PixelGameEngine* game) const
{
	olc::Pixel color(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
	game->DrawCircle(m_pos, rad, color);
}

// Draws the Ball, takes in input the game engine and a color
void Balls::SelfDraw(olc::PixelGameEngine* game, olc::Pixel p) const
{
	game->DrawCircle(m_pos, rad, p);
}


// create a ball of random radius in a random position
void Balls::Redo(olc::PixelGameEngine* game)
{
	m_pos = { (float)rand() / RAND_MAX * game->ScreenWidth(), (float)rand() / RAND_MAX * game->ScreenWidth() };
	rad = rand() % 5 + 1;
}

// Changes the ball position based on user input and the natural behaviour of the ball
void Balls::ChangePos(olc::PixelGameEngine* game, float fElapsedTime, MovementEngine* engine)
{
	if (game->GetKey(olc::Key::W).bHeld || game->GetKey(olc::Key::UP).bHeld) m_pos.y -= m_vel.y * fElapsedTime;
	if (game->GetKey(olc::Key::A).bHeld || game->GetKey(olc::Key::LEFT).bHeld) m_pos.x -= m_vel.x * fElapsedTime;
	if (game->GetKey(olc::Key::S).bHeld || game->GetKey(olc::Key::DOWN).bHeld) m_pos.y += m_vel.y * fElapsedTime;
	if (game->GetKey(olc::Key::D).bHeld || game->GetKey(olc::Key::RIGHT).bHeld) m_pos.x += m_vel.x * fElapsedTime;
}

// Reset the ball changing its position to the window center
void Balls::Reset(olc::PixelGameEngine* game)
{
	m_pos.x = game->ScreenWidth() / 2.f;
	m_pos.y = game->ScreenHeight() / 2.f;
}


// Changes the ball position based on user input and the natural behaviour of the ball
void GravityBalls::ChangePos(olc::PixelGameEngine* game, float fElapsedTime, MovementEngine* engine)
{
	if (game->GetKey(olc::Key::W).bHeld || game->GetKey(olc::Key::UP).bHeld)
	// Moves UP with a constant velocity -m_vel.y
	// At the end of User input changes the ball velocity to m_vel.y
	{
		m_pos.y -= m_vel.y * fElapsedTime;
		m_vel = { 0, -m_vel.y };
	}
	if (game->GetKey(olc::Key::A).bHeld || game->GetKey(olc::Key::LEFT).bHeld)
	// Moves to the left with constant velocity -m_vel.x
	{
		m_vel = { -m_vel.x, 0. };
	}

	if (game->GetKey(olc::Key::D).bHeld || game->GetKey(olc::Key::RIGHT).bHeld)
	// Moves to the right with +m_vel.x
	{
		m_pos.x += m_vel.x * fElapsedTime;
		m_vel = { +m_vel.x, 0 };
	}
	if (game->GetKey(olc::Key::S).bHeld || game->GetKey(olc::Key::DOWN).bHeld)
	{
	// Moves Down with constant velocity +m_vel.y
		m_pos.y += m_vel.y * fElapsedTime;
		m_vel = { 0, -5.f };
	}
	else
	//Natural ball movement
	{
		engine->movement(fElapsedTime, m_pos, m_vel, [this](float fElapsedTime, olc::vd2d position, olc::vd2d speed) {
			return this->Equation(fElapsedTime, position, speed);
		});
		ManageCollision(game, fElapsedTime);
	}
}

// Display current stats as position and velocity
void GravityBalls::DisplayStats(olc::PixelGameEngine* game) const
{
	game->DrawStringDecal({ 5.,5. }, "Position " + m_pos.str());
	game->DrawStringDecal({ 5. , 15. }, "Velocity " + m_vel.str());
}

bool GravityBalls::CheckFloorCollision(olc::PixelGameEngine* game) const
{
	return (m_pos.y + rad > game->ScreenHeight() || m_pos.y - rad < 0.f);
}

bool GravityBalls::CheckLateralCollision(olc::PixelGameEngine* game) const
{
	return m_pos.x + rad > game->ScreenWidth() || m_pos.x - rad < 0.f;
}

void GravityBalls::ManageCollision(olc::PixelGameEngine* game, float fElapsedTime)
{
	if (CheckFloorCollision(game))
	{
		m_vel = olc::vd2d(m_vel.x, -m_vel.y);
	}
	if (CheckLateralCollision(game))
	{
		m_vel = olc::vd2d(-m_vel.x, m_vel.y);
	}
	else
	{
		m_vel += m_gravity * fElapsedTime - m_attr * m_vel;
	}
}

std::vector<olc::vd2d> GravityBalls::Choords() const
{
	return std::vector<olc::vd2d> { m_pos, m_vel };
}

std::array<olc::vd2d, 2> GravityBalls::Equation(float fElapsedTime, olc::vd2d position, olc::vd2d speed) const
{
	std::array<olc::vd2d, 2> res = {
		olc::vd2d{
			position.x + speed.x * fElapsedTime,
			position.y + speed.y * fElapsedTime
		},
		olc::vd2d{
			speed.x + m_gravity.x * fElapsedTime,
			speed.y + m_gravity.y * fElapsedTime
		},
	};
	return res;
}
