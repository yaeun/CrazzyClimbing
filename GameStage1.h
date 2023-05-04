#pragma once

#include "SDL.h"



class Stage1 : public PhaseInterface
{
public:
	Stage1();
	~Stage1();

	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

	Uint32 timerStart = 0;
	bool timerStarted = false;
	const Uint32 timerDuration = 3000;
	


private:
	
	SDL_Rect g_bg_source_rect;
	SDL_Rect g_bg_destination_rect;
	SDL_Texture* g_bg_texture;

	SDL_Texture* g_ryu_sheet_texture;
	SDL_Rect g_source_rect;
	SDL_Rect g_destination_rect;

	SDL_Texture* g_char_texture;
	SDL_Rect g_char_pos;
	SDL_Rect g_destination_pos;

	
	Mix_Chunk* g_gun_sound;

	std::vector<std::pair<int, int>> g_XY;

	SDL_Texture* g_title_en;
	SDL_Rect g_title_en_rect;

	SDL_Texture* g_title_cn;
	SDL_Rect g_title_cn_rect;

	SDL_Texture* g_title_sc;
	SDL_Rect g_title_sc_rect;
	

};


