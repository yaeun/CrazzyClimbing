#include "Game.h"
#include "GameIntro.h"

Intro::Intro() {

	// BackGround
	SDL_Surface* bg_surface = IMG_Load("../../Resources/amu.jpg");
	g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);

	g_bg_source_rect.x = 0;	
	g_bg_source_rect.y = 0;
	g_bg_source_rect.w = 500;
	g_bg_source_rect.h = 500;

	g_bg_destination_rect.x = 0;
	g_bg_destination_rect.y = 0;
	g_bg_destination_rect.w = 500;
	g_bg_destination_rect.h = 500;
	
}

Intro::~Intro() {
	SDL_DestroyTexture(g_bg_texture);
}

void Intro::Update()
{

}

void Intro::Render() {
	// Background
	SDL_RenderCopy(g_renderer, g_bg_texture, &g_bg_source_rect, &g_bg_destination_rect);
	SDL_RenderPresent(g_renderer);

}

void Intro::HandleEvents() {

}