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
	//Background
	SDL_Rect g_bg_source_rect;
	SDL_Rect g_bg_destination_rect;
	SDL_Texture* g_bg_texture;

};