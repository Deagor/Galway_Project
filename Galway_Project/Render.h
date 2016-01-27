#pragma once
#ifndef Render_H
#define Render_H
#include "stdafx.h"
class Render {

private:
	SDL_Renderer *ren;
	SDL_Window* win; 
	void* font;
	std::vector<SDL_Texture*> textures;
	std::vector<SDL_Rect> dstRects;
	std::vector<SDL_Rect> srcRects;

	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	Render();
	~Render();

public:

	static Render * GetInstance();

	void Update(const std::string &messageText);

	std::pair<SDL_Rect *, int> AddSurfaceToRenderer(SDL_Surface * bmp, float x, float y);

	void RemoveTexture(int);

	SDL_Rect * GetSrcRect(SDL_Rect * rec);

	void renderText(const std::string & messageText);

	void fill_circle(SDL_Surface * surface, int cx, int cy, int radius, Uint32 pixel);

	void logSDLError(const std::string & msg);

	int QuitWithError(const std::string & msg);

};
#endif