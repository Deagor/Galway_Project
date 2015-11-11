#pragma once
#ifndef Render_H
#define Render_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

class Render {
private:
	SDL_Renderer *ren;
	SDL_Window* win;

	std::vector<SDL_Texture*> textures;
	std::vector<SDL_Rect> dstRects;
	std::vector<SDL_Rect> srcRects;

	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	Render* instance = NULL;

	Render() {
		win = SDL_CreateWindow("Group A", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		dstRects.reserve(100);
		srcRects.reserve(100);
		//creating a renderer that is linked to the render class 
		ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (ren == nullptr) {
			SDL_DestroyWindow(win);
			QuitWithError("SDL_CreateRenderer Error: ");
		}
		//set background color
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	}
	
	~Render()
	{
		delete win;
	}

public:

	Render* GetInstance()
	{
		if (instance != NULL)
		{
			return instance;
		}
		else
		{
			instance = new Render();
		}
	}

	//updating the renderer and drawing what is within it
	void Update() {
		//clear the screen
		SDL_RenderClear(ren);

		//copy the textures to the renderer and give them a destination
		int numberTextures = textures.size();
		for (int i = 0; i < numberTextures; i++) {
			SDL_RenderCopy(ren, textures[i], &srcRects[i], &dstRects[i]);
		}

		//updaet the screen with rendering operations
		SDL_RenderPresent(ren);
	}

	//adding texture to the renderer with the position
	SDL_Rect* AddSurfaceToRenderer(SDL_Surface *bmp, float x, float y) {
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

		return &dstRects[rectPos];
	}

	SDL_Rect* GetSrcRect(SDL_Rect* rec)
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
	SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
		SDL_Color color, int fontSize, SDL_Renderer *renderer)
	{
		//Open the font
		TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
		if (font == nullptr) {
			logSDLError("TTF_OpenFont");
			return nullptr;
		}
		//We need to first render to a surface as that's what TTF_RenderText
		//returns, then load that surface into a texture
		SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
		if (surf == nullptr) {
			TTF_CloseFont(font);
			logSDLError("TTF_RenderText");
			return nullptr;
		}
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
		if (texture == nullptr) {
			logSDLError("CreateTexture");
		}
		//Clean up the surface and font
		SDL_FreeSurface(surf);
		TTF_CloseFont(font);
		return texture;
	}

	void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel)
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


	void logSDLError(const std::string &msg) {
		//std::cout << msg << " error: " << SDL_GetError() << std::endl;

	}

	int QuitWithError(const std::string &msg) {
		//std::cout << msg << " error: " << SDL_GetError() << std::endl;
		SDL_Delay(1000); //give user a chance to read error
		SDL_Quit();
		return 1;
	}
};
#endif