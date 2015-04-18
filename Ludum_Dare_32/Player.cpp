#include "Player.h"
#include "GraphicsEngine.h"

Player::Player() : Movable()
{
	velocity = 64.0f;
	sprite = new Sprite(&GraphicsEngine::GetInstance());
	sprite->SetTexture("player.png");
	SDL_Rect r = SDL_Rect();
	r.x = (int)GetPosition().first;
	r.y = (int)GetPosition().second;
	r.w = 64;
	r.h = 64;
	sprite->SetBounds(r);
	sprite->SetPosition(r);
}

bool Player::HandleEvent(SDL_Event& e)
{
	bool consume = false;
	if (moveFinished && e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the target
		moveFinished = false;
		int x = GetPosition().first;
		int y = GetPosition().second;
		int xTarget = GetTarget().first;
		int yTarget = GetTarget().second;
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: SetTarget(x, y - Level::GRID_HEIGHT); break;
		case SDLK_DOWN: SetTarget(x, y + Level::GRID_HEIGHT); break;
		case SDLK_LEFT: SetTarget(x - Level::GRID_WIDTH, y); break;
		case SDLK_RIGHT: SetTarget(x + Level::GRID_WIDTH, y); break;
		default: moveFinished = true;
		}
		if (!moveFinished && pLevel != NULL)
		{
			int xTarget = GetTarget().first;
			int yTarget = GetTarget().second;
			int xx = (int)xTarget / Level::GRID_WIDTH;
			int yy = (int)yTarget / Level::GRID_HEIGHT;
			if (xx < 0 || xx > pLevel->width || yy < 0 || yy > pLevel->height)
			{
				SetTarget(x, y);
			}
			else
			{
				int value = pLevel->GetPosition(xx, yy);
				if (value != 0)
				{
					SetTarget(x, y);
				}
			}
		}
	}
	return consume;
}

