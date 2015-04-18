#include <SDL.h>
#include <string>

class GraphicsEngine;
class Sprite
{
public:
	Sprite(GraphicsEngine* pGE);
	~Sprite();
	bool SetSurface(std::string path);
	SDL_Surface* GetSurface();
private:
	GraphicsEngine* pGE;
	SDL_Surface* pSurface;
};