#include "Balls.h"

void Balls::SelfDraw(olc::PixelGameEngine* game) const
{
	olc::Pixel color(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
	game->DrawCircle(m_pos, rad, color);
}

void Balls::SelfDraw(olc::PixelGameEngine* game, olc::Pixel p) const
{
	game->DrawCircle(m_pos, rad, p);
}

void Balls::Redo(olc::PixelGameEngine* game)
{
	m_pos = { (float)rand() / RAND_MAX * game->ScreenWidth(), (float)rand() / RAND_MAX * game->ScreenWidth() };
	rad = rand() % 5 + 1;
}

void Balls::ChangePos(olc::PixelGameEngine* game, float fElapsedTime)
{
	if (game->GetKey(olc::Key::W).bHeld || game->GetKey(olc::Key::UP).bHeld) m_pos.y -= m_vel.y * fElapsedTime;
	if (game->GetKey(olc::Key::A).bHeld || game->GetKey(olc::Key::LEFT).bHeld) m_pos.x -= m_vel.x * fElapsedTime;
	if (game->GetKey(olc::Key::S).bHeld || game->GetKey(olc::Key::DOWN).bHeld) m_pos.y += m_vel.y * fElapsedTime;
	if (game->GetKey(olc::Key::D).bHeld || game->GetKey(olc::Key::RIGHT).bHeld) m_pos.x += m_vel.x * fElapsedTime;
}

void Balls::Reset(olc::PixelGameEngine* game)
{
	m_pos.x = game->ScreenWidth() / 2.f;
	m_pos.y = game->ScreenHeight() / 2.f;
}

void GravityBalls::ChangePos(olc::PixelGameEngine* game, float fElapsedTime)
{
	if (game->GetKey(olc::Key::W).bHeld || game->GetKey(olc::Key::UP).bHeld)
	{
		m_pos.y -= m_vel.y * fElapsedTime;
		m_grav_vel = { 0, -m_vel.y };
	}
	if (game->GetKey(olc::Key::A).bHeld || game->GetKey(olc::Key::LEFT).bHeld)
	{
		m_pos.x -= m_vel.x * fElapsedTime;
		m_grav_vel = { -m_vel.x, 0. };
	}
	if (game->GetKey(olc::Key::D).bHeld || game->GetKey(olc::Key::RIGHT).bHeld)
	{
		m_pos.x += m_vel.x * fElapsedTime;
		m_grav_vel = { +m_vel.x, 0 };
	}
	if (game->GetKey(olc::Key::S).bHeld || game->GetKey(olc::Key::DOWN).bHeld)
	{
		m_pos.y += m_vel.y * fElapsedTime;
		m_grav_vel = { 0, -5.f };
	}
	else
	{

		m_pos += m_grav_vel * fElapsedTime;
		ManageCollision(game, fElapsedTime);
	}



}

void GravityBalls::DisplayStats(olc::PixelGameEngine* game) const 
{
	game->DrawStringDecal({ 5.,5. }, "Position " + m_pos.str());
	game->DrawStringDecal({ 5. , 15. }, "Velocity " + m_grav_vel.str());
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
		m_grav_vel = olc::vd2d(m_grav_vel.x, -m_grav_vel.y);
	}
	if (CheckLateralCollision(game))
	{
		m_grav_vel = olc::vd2d(-m_grav_vel.x, m_grav_vel.y);
	}
	else
	{
		m_grav_vel += m_gravity * fElapsedTime - m_attr * m_grav_vel;
	}
}

std::vector<olc::vd2d> GravityBalls::Choords() const
{
	return std::vector<olc::vd2d> { m_pos, m_grav_vel };
}