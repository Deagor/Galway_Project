#pragma once
#ifndef Render_H
#define Render_H

class Render {

private:
	SDL_Renderer *ren;
	SDL_Window* win;

	std::vector<SDL_Texture*> textures;
	std::vector<SDL_Rect> dstRects;
	std::vector<SDL_Rect> srcRects;

	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	Render();
	~Render();

public:


	static Render * GetInstance();

	void Update();

	SDL_Rect * AddSurfaceToRenderer(SDL_Surface * bmp, float x, float y);

	SDL_Rect * GetSrcRect(SDL_Rect * rec);

	SDL_Texture * renderText(const std::string & message, const std::string & fontFile, SDL_Color color, int fontSize, SDL_Renderer * renderer);

	void fill_circle(SDL_Surface * surface, int cx, int cy, int radius, Uint32 pixel);

	void logSDLError(const std::string & msg);

	int QuitWithError(const std::string & msg);

};
#endif