#include "stdafx.h"
#include "Render.h"

static Render* instance = NULL;

Render* Render::GetInstance()
{
	if (instance == NULL)
	{
		instance = new Render();
	}
	return instance;
}

//updating the renderer and drawing what is within it
void Render::Update(const std::string &messageText) {
	//clear the screen
	SDL_RenderClear(ren);

	//copy the textures to the renderer and give them a destination
	int numberTextures = textures.size();
	for (int i = 0; i < numberTextures; i++) {
		if (dstRects[i].x > -1000)
			SDL_RenderCopy(ren, textures[i], &srcRects[i], &dstRects[i]);
	}
	const char* error;
	std::string FontLocation = "arial.ttf";
	TTF_Font *Sans = TTF_OpenFont(FontLocation.c_str(), 10);
	if (Sans == nullptr) {
		cout << "No fonts allowed..." << endl;
		error = TTF_GetError();
	}
	else { 
		SDL_Color White = { 255, 255, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

		const char* msgText = messageText.c_str();

		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, msgText, White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

		SDL_Texture* Message = SDL_CreateTextureFromSurface(ren, surfaceMessage); //now you can convert it into a texture

		SDL_Rect Message_rect; //create a rect
		Message_rect.x = 20;  //controls the rect's x coordinate 
		Message_rect.y = 0; // controls the rect's y coordinte
		Message_rect.w = 100; // controls the width of the rect
		Message_rect.h = 30; // controls the height of the rect

		SDL_RenderCopy(ren, Message, NULL, &Message_rect);
	}
	//updaet the screen with rendering operations
	TTF_CloseFont(Sans);
	Sans = NULL;
	SDL_RenderPresent(ren);
}

//adding texture to the renderer with the position
std::pair<SDL_Rect *, int> Render::AddSurfaceToRenderer(SDL_Surface *bmp, float x, float y) {
	//getting the width / height from the texture
	SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (texture == nullptr) {
		QuitWithError("SDL_CreateTextureFromSurface Error: ");
	}
	int iW, iH;
	SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);

	SDL_Rect dstRect;
	SDL_Rect srcRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = iW;
	dstRect.h = iH;
	srcRect = dstRect;
	srcRect.x = 0;
	srcRect.y = 0;

	int rectPos = dstRects.size();
	dstRects.push_back(dstRect);
	srcRects.push_back(srcRect);
	textures.push_back(texture);

	return std::pair<SDL_Rect *, int>(&dstRects[rectPos], rectPos);
}

void Render::RemoveTexture(int i)
{
	dstRects.erase(dstRects.begin() + i);
	srcRects.erase(srcRects.begin() + i);
	textures.erase(textures.begin() + i);
}

SDL_Rect* Render::GetSrcRect(SDL_Rect* rec)
{
	std::vector<SDL_Rect>::iterator it = dstRects.begin();
	std::vector<SDL_Rect>::iterator it2 = srcRects.begin();
	while (it != dstRects.end()) {
		if ((*it).h == rec->h && (*it).w == rec->w && (*it).x == rec->x && (*it).y == rec->y)
		{
			return &(*it2);
		}
		it++;
		it2++;
	}
}

//rendering texture
void Render::renderText(const std::string &messageText)
{

}

void Render::fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel)
{
	// Note that there is more to altering the bitrate of this 
	// method than just changing this value.  See how pixels are
	// altered at the following web page for tips:
	//   http://www.libsdl.org/intro.en/usingvideo.html
	static const int BPP = 4;

	double r = (double)radius;

	for (double dy = 1; dy <= r; dy += 1.0)
	{
		// This loop is unrolled a bit, only iterating through half of the
		// height of the circle.  The result is used to draw a scan line and
		// its mirror image below it.

		// The following formula has been simplified from our original.  We
		// are using half of the width of the circle because we are provided
		// with a center and we need left/right coordinates.

		double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
		int x = cx - dx;

		// Grab a pointer to the left-most pixel for each half of the circle
		Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
		Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;

		for (; x <= cx + dx; x++)
		{
			*(Uint32 *)target_pixel_a = pixel;
			*(Uint32 *)target_pixel_b = pixel;
			target_pixel_a += BPP;
			target_pixel_b += BPP;
		}
	}
}


void Render::logSDLError(const std::string &msg) {
	//std::cout << msg << " error: " << SDL_GetError() << std::endl;

}

int Render::QuitWithError(const std::string &msg) {
	//std::cout << msg << " error: " << SDL_GetError() << std::endl;
	SDL_Delay(1000); //give user a chance to read error
	SDL_Quit();
	return 1;
}

Render::Render() {
	win = SDL_CreateWindow("Group A", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	dstRects.reserve(10000);
	srcRects.reserve(10000);
	textures.reserve(10000);
	//creating a renderer that is linked to the render class 
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == nullptr) {
		SDL_DestroyWindow(win);
		QuitWithError("SDL_CreateRenderer Error: ");
	}
	//set background color
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
}

Render::~Render()
{
	delete win;
}