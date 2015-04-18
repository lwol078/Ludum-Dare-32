#include "Player.h"
#include "GraphicsEngine.h"

Player::Player() : Movable()
{
	velocity = 64.0f;
	sprite = new Sprite(&GraphicsEngine::GetInstance());
	sprite->SetTexture("player.png");
	SDL_Rect r = SDL_Rect();
	r.x = (int)x;
	r.y = (int)y;
	r.w = 64;
	r.h = 64;
	sprite->SetBounds(r);
	sprite->SetPosition(r);
}

bool Player::HandleEvent(SDL_Event& e)
{
	bool consume = false;
	if (!lock && e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the target
		Lock(true);
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: yTarget = y - Level::GRID_HEIGHT; xTarget = x; break;
		case SDLK_DOWN: yTarget = y + Level::GRID_HEIGHT; xTarget = x; break;
		case SDLK_LEFT: xTarget = x - Level::GRID_WIDTH; yTarget = y; break;
		case SDLK_RIGHT: xTarget = x + Level::GRID_WIDTH; yTarget = y; break;
		default: (Lock(false));
		}
		if (lock && pLevel != NULL)
		{
			int xx = (int)xTarget / Level::GRID_WIDTH;
			int yy = (int)yTarget / Level::GRID_HEIGHT;
			if (xx < 0 || xx > pLevel->width || yy < 0 || yy > pLevel->height)
			{
				xTarget = x;
				yTarget = y;
				Lock(false);
			}
			else
			{
				int value = pLevel->GetPosition(xx, yy);
				if (value != 0)
				{
					xTarget = x;
					yTarget = y;
					Lock(false);
				}
			}
		}
	}
	return consume;
}

