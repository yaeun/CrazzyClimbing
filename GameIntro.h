#pragma once

#include "SDL.h"

class Intro : public PhaseInterface
{
public:
	Intro(); //Init_Intro()
	~Intro();  //Clear_Intro()
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:

	SDL_Rect g_bg_source_rect;
	SDL_Rect g_bg_destination_rect;
	SDL_Texture* g_bg_texture;

	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination

	SDL_Texture* g_title_en;
	SDL_Rect g_title_en_rect;

	SDL_Texture* g_title_en2;
	SDL_Rect g_title_en2_rect;


	
};


