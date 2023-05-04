#include "Game.h"
#include "GameIntro.h"


Mix_Music* s_g_bg_mus;
Mix_Music* g_bg_mus;

Intro::Intro()
{
	
	//BGM
	s_g_bg_mus = Mix_LoadMUS("../../Resources/start_bgm.wav");
	g_bg_mus = Mix_LoadMUS("../../Resources/s1.wav");
	Mix_PlayMusic(s_g_bg_mus, -1);
	

	// BG
	SDL_Surface* bg_surface = IMG_Load("../../Resources/dream_TradingCard (19).jpg");
	g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);

	g_bg_source_rect.x = 0;
	g_bg_source_rect.y = 0;
	g_bg_source_rect.w = 960;
	g_bg_source_rect.h = 1568;

	g_bg_destination_rect.x = 0;
	g_bg_destination_rect.y = 0;
	g_bg_destination_rect.w = 600;
	g_bg_destination_rect.h = 900;

	

	//Text
	{
		TTF_Font* font1 = TTF_OpenFont("../../Resources/DNFBitBitTTF.ttf",80);
		SDL_Color C330033 = { 51, 0, 51, 0 };
		SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(font1, "Plane Game", C330033);

		g_title_en_rect.x = 0;
		g_title_en_rect.y = 0;
		g_title_en_rect.w = tmp_surface->w;
		g_title_en_rect.h = tmp_surface->h;


		g_title_en = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
		SDL_FreeSurface(tmp_surface);
		TTF_CloseFont(font1);
	}
	//Text
	{
		TTF_Font* font1 = TTF_OpenFont("../../Resources/DNFBitBitTTF.ttf", 82);
		SDL_Color white = { 255, 255, 255, 0 };
		SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(font1, "Plane Game", white);

		g_title_en2_rect.x = 0;
		g_title_en2_rect.y = 0;
		g_title_en2_rect.w = tmp_surface->w;
		g_title_en2_rect.h = tmp_surface->h;


		g_title_en2 = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
		SDL_FreeSurface(tmp_surface);
		TTF_CloseFont(font1);
	}

	// Start Button

	SDL_Surface* temp_surface = IMG_Load("../../Resources/KakaoTalk_20230427_132114955.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	destination_rectangle_.x = 210;
	destination_rectangle_.y = 500;
	source_rectangle_.x = 0;
	source_rectangle_.y = 0;

	destination_rectangle_.w = 180;
	destination_rectangle_.h = 70;

}

Intro::~Intro()
{
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(g_title_en);
	SDL_DestroyTexture(g_title_en2);
}

void Intro::Update()
{
}


void Intro::Render()
{
	// Background
	SDL_RenderCopy(g_renderer, g_bg_texture, &g_bg_source_rect, &g_bg_destination_rect);
	
	// Text
	{
		SDL_Rect tmp_r;
		tmp_r.x = 99;
		tmp_r.y = 303;
		tmp_r.w = g_title_en2_rect.w;
		tmp_r.h = g_title_en2_rect.h;
		SDL_RenderCopy(g_renderer, g_title_en2, &g_title_en2_rect, &tmp_r);
	}

	// Text
	{
		SDL_Rect tmp_r;
		tmp_r.x = 100;
		tmp_r.y = 300;
		tmp_r.w = g_title_en_rect.w;
		tmp_r.h = g_title_en_rect.h;
		SDL_RenderCopy(g_renderer, g_title_en, &g_title_en_rect, &tmp_r);
	}

	

	

	//SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Intro::HandleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
		
			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int mouseX = event.button.x;
				int mouseY = event.button.y;
				if (mouseX >= destination_rectangle_.x && mouseX < destination_rectangle_.x + destination_rectangle_.w
					&& mouseY >= destination_rectangle_.y && mouseY < destination_rectangle_.y + destination_rectangle_.h) {
					g_current_game_phase = PHASE_STAGE1;	
					Mix_PlayMusic(g_bg_mus, -1);
					
				}

			}
			break;

		default:
			break;
		}
	}
}
