//Graphics engine for the game
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include <queue>
#include <vector>

class Sprite;
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	//Screen Limits
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	bool LoadMedia();

	void AddSprite(Sprite* spr);
	void RemoveSprite(Sprite* spr);
	SDL_Surface* LoadSurface(std::string path);

	void Draw();
private:
	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The surface contained by the window
	SDL_Surface* gScreenSurface = NULL;

	//Map of textures to draw
	std::map<std::string, SDL_Surface*> surfaceMap;

	//Queue of sprites to draw
	std::priority_queue<Sprite*> spriteQueue;

	//List of sprites
	std::vector<Sprite*> spriteList;

	//Current displayed PNG image
	SDL_Surface* gPNGSurface = NULL;
};