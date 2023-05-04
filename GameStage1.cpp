#include "Game.h"
#include "GameStage1.h"
#include <windows.h>
#include <sstream>
#include <string>
#include <atlstr.h>

int g_input;
int m_input;
int g_elapsed_time_ms;
int score;
int m_max;
int count;
int s_input;
#define MAX_DIGITS 10


Stage1::Stage1()
{
	g_input = 0;
	m_input = 0;
	g_flag_running = true;
	m_max = 10;
	count = 4;
	s_input = 0;
	
	std::vector<std::pair<int, int>> g_XY;

	

	//Text
	{
		TTF_Font* font1 = TTF_OpenFont("../../Resources/NeoDunggeunmoPro-Regular.ttf", 30);
		SDL_Color black = { 0, 0, 0, 0 };
		SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(font1, CW2A(L"점수 : ", CP_UTF8), black);

		g_title_en_rect.x = 0;
		g_title_en_rect.y = 0;
		g_title_en_rect.w = tmp_surface->w;
		g_title_en_rect.h = tmp_surface->h;


		g_title_en = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
		SDL_FreeSurface(tmp_surface);
		TTF_CloseFont(font1);
	}

	//Score
	{
		score = 0;

		TTF_Font* font2 = TTF_OpenFont("../../Resources/NeoDunggeunmoPro-Regular.ttf", 30);
		SDL_Color black = { 0, 0, 0, 0 };


		SDL_Surface* tmp_surface = TTF_RenderText_Blended(font2, std::to_string(score).c_str(), black);

		g_title_sc_rect.x = 0;
		g_title_sc_rect.y = 0;
		g_title_sc_rect.w = tmp_surface->w;
		g_title_sc_rect.h = tmp_surface->h;

		g_title_sc = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
		SDL_FreeSurface(tmp_surface);
		TTF_CloseFont(font2);
	}

	{
		//카운트
		TTF_Font* font3 = TTF_OpenFont("../../Resources/NeoDunggeunmoPro-Regular.ttf", 100);
		SDL_Color FF3300 = { 255, 51, 0, 0 };
		SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(font3, std::to_string(count).c_str(), FF3300);

		g_title_cn_rect.x = 0;
		g_title_cn_rect.y = 0;
		g_title_cn_rect.w = tmp_surface->w;
		g_title_cn_rect.h = tmp_surface->h;


		g_title_cn = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
		SDL_FreeSurface(tmp_surface);
		TTF_CloseFont(font3);
	}
	


	//BGM
	g_gun_sound = Mix_LoadWAV("../../Resources/missile_se.mp3");
	

	// BG
	SDL_Surface* bg_surface = IMG_Load("../../Resources/KakaoTalk_20230429_165548931.jpg");
	g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);

	g_bg_source_rect.x = 0;
	g_bg_source_rect.y = 0;
	g_bg_source_rect.w = 900;
	g_bg_source_rect.h = 1568;

	g_bg_destination_rect.x = 0;
	g_bg_destination_rect.y = 0;
	g_bg_destination_rect.w = 600;
	g_bg_destination_rect.h = 900;


	// Plane
	{
		SDL_Surface* ryu_sheet_surface = IMG_Load("../../Resources/KakaoTalk_20230427_154357315.png");
		g_ryu_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, ryu_sheet_surface);
		SDL_FreeSurface(ryu_sheet_surface);

		g_source_rect.x = 0;
		g_source_rect.y = 0;
		g_source_rect.w = 1430;
		g_source_rect.h = 1584;

		g_destination_rect.x = 240;
		g_destination_rect.y = 500;
		g_destination_rect.w = 100;
		g_destination_rect.h = 120;

	}
	
	//Missile
	{
		SDL_Surface* g_char_surface = IMG_Load("../../Resources/IMG_2904.PNG.png");
		g_char_texture = SDL_CreateTextureFromSurface(g_renderer, g_char_surface);
		SDL_FreeSurface(g_char_surface);

		g_char_pos.x = 0;
		g_char_pos.y = 0;
		g_char_pos.w = 500;
		g_char_pos.h = 1200;

		g_destination_pos.x = g_destination_rect.x + 35;
		g_destination_pos.y = g_destination_rect.y;
		g_destination_pos.w = 28;
		g_destination_pos.h = 64;
	}
	


	g_elapsed_time_ms = 0;
}

Stage1::~Stage1()
{
	s_input = 0;
	score = 0;
	SDL_DestroyTexture(g_ryu_sheet_texture);
	SDL_DestroyTexture(g_char_texture);
	SDL_DestroyTexture(g_title_en);
	SDL_DestroyTexture(g_title_sc);
	Mix_FreeChunk(g_gun_sound);
}

void Stage1::Update()
{
	// Update

	g_bg_destination_rect.y += 3;
	if (g_bg_destination_rect.y >= 900) {
		g_bg_destination_rect.y = 0;
	}

	if (g_input == 1) {
		g_destination_rect.x -= 10;
	}
	else if (g_input == 2) {
		g_destination_rect.x += 10;
	}
	else if (g_input == 3) {
		g_destination_rect.y -= 10;
	}
	else if (g_input == 4) {
		g_destination_rect.y += 10;
	}


	if (g_destination_rect.x > 480) {
		g_destination_rect.x -= 10;
	}
	else if (g_destination_rect.x < 0) {
		g_destination_rect.x += 10;
	}
	else if (g_destination_rect.y > 770) {
		g_destination_rect.y -= 10;
	}
	else if (g_destination_rect.y < 0) {
		g_destination_rect.y += 10;
	}



	if (m_input == 1) {

		for (int i = 0; i < g_XY.size(); i++) {
			g_XY[i].second -= 10;
		}


	}

	g_elapsed_time_ms += 33;

}


void Stage1::Render()
{
	// Background
	{
		SDL_Rect tmp_r;
		tmp_r.x = 0;
		tmp_r.y = g_bg_destination_rect.y-900;
		tmp_r.w = g_bg_destination_rect.w;
		tmp_r.h = g_bg_destination_rect.h;
		SDL_RenderCopy(g_renderer, g_bg_texture, NULL, &tmp_r);
		tmp_r.x = 0;
		tmp_r.y = g_bg_destination_rect.y;
		tmp_r.w = g_bg_destination_rect.w;
		tmp_r.h = g_bg_destination_rect.h;
		SDL_RenderCopy(g_renderer, g_bg_texture, NULL, &tmp_r);
	}


	
	// Character
	if (m_input == 0) {

	}
	else {
		for (int i = 0; i < g_XY.size(); i++) {
			//std::cout << g_XY[i].first << " " << g_XY[i].second << std::endl;
			SDL_Rect r = g_destination_pos;
			r.x = g_XY[i].first;
			r.y = g_XY[i].second;
			SDL_RenderCopy(g_renderer, g_char_texture, &g_char_pos, &r);
		}


	}
	// Text
	{
		SDL_Rect tmp_r;
		tmp_r.x = 10;
		tmp_r.y = 10;
		tmp_r.w = g_title_en_rect.w;
		tmp_r.h = g_title_en_rect.h;
		SDL_RenderCopy(g_renderer, g_title_en, &g_title_en_rect, &tmp_r);
	}
	
	//score
	{
		SDL_Rect tmp_r;
		tmp_r.x = 100;
		tmp_r.y = 10;
		tmp_r.w = g_title_sc_rect.w;
		tmp_r.h = g_title_sc_rect.h;
		SDL_RenderCopy(g_renderer, g_title_sc, &g_title_sc_rect, &tmp_r);
	}


	// g_ryu_sheet_texture
	SDL_RenderCopy(g_renderer, g_ryu_sheet_texture, &g_source_rect, &g_destination_rect);


	if (timerStarted && SDL_GetTicks() - timerStart > timerDuration) {
		g_current_game_phase = PHASE_ENDING;
		timerStarted = false;
		
		s_input = 0;
		score = 0;
		
	}


	if (s_input==1) {
		//Missile
		{
			m_input = 0;
			g_XY.clear();
			SDL_Surface* g_char_surface = IMG_Load("../../Resources/IMG_2904.PNG.png");
			g_char_texture = SDL_CreateTextureFromSurface(g_renderer, g_char_surface);
			SDL_FreeSurface(g_char_surface);

			g_char_pos.x = 0;
			g_char_pos.y = 0;
			g_char_pos.w = 500;
			g_char_pos.h = 1200;

			g_destination_pos.x = g_destination_rect.x + 35;
			g_destination_pos.y = g_destination_rect.y;
			g_destination_pos.w = 28;
			g_destination_pos.h = 64;
		}
		count--;
		{
			//카운트
			TTF_Font* font3 = TTF_OpenFont("../../Resources/NeoDunggeunmoPro-Regular.ttf", 130);
			SDL_Color FF3300 = { 204, 0, 102, 0 };
			SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(font3, std::to_string(count).c_str(), FF3300);

			g_title_cn_rect.x = 0;
			g_title_cn_rect.y = 0;
			g_title_cn_rect.w = tmp_surface->w;
			g_title_cn_rect.h = tmp_surface->h;


			g_title_cn = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
			SDL_FreeSurface(tmp_surface);
			TTF_CloseFont(font3);
		}
		// 카운트
		{
			SDL_Rect tmp_r;
			tmp_r.x = 260;
			tmp_r.y = 230;
			tmp_r.w = g_title_cn_rect.w;
			tmp_r.h = g_title_cn_rect.h;
			SDL_RenderCopy(g_renderer, g_title_cn, &g_title_cn_rect, &tmp_r);
		}
		
		if (count == 1) {
			//Plane
			{
				SDL_Surface* ryu_sheet_surface = IMG_Load("../../Resources/KakaoTalk_20230427_154357315.png");
				g_ryu_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, ryu_sheet_surface);
				SDL_FreeSurface(ryu_sheet_surface);

				g_source_rect.x = 0;
				g_source_rect.y = 0;
				g_source_rect.w = 1430;
				g_source_rect.h = 1584;

				g_destination_rect.x = 240;
				g_destination_rect.y = 500;
				g_destination_rect.w = 100;
				g_destination_rect.h = 120;

			}
			//Score
			{
				score = 0;

				TTF_Font* font2 = TTF_OpenFont("../../Resources/NeoDunggeunmoPro-Regular.ttf", 30);
				SDL_Color black = { 0, 0, 0, 0 };


				SDL_Surface* tmp_surface = TTF_RenderText_Blended(font2, std::to_string(score).c_str(), black);

				g_title_sc_rect.x = 0;
				g_title_sc_rect.y = 0;
				g_title_sc_rect.w = tmp_surface->w;
				g_title_sc_rect.h = tmp_surface->h;

				g_title_sc = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
				SDL_FreeSurface(tmp_surface);
				TTF_CloseFont(font2);
			}
		}
		
		
		SDL_RenderPresent(g_renderer);
		// 1초 대기
		SDL_Delay(1000);
		
	}
	
	
	SDL_RenderPresent(g_renderer);
}



void Stage1::HandleEvents()
{


	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;


		case SDL_KEYDOWN:
			if (keyboardState[SDL_SCANCODE_LEFT]) {
				g_input = 1;
			}
			if (keyboardState[SDL_SCANCODE_RIGHT]) {
				g_input = 2;
			}
			if (keyboardState[SDL_SCANCODE_UP]) {
				g_input = 3;
			}
			if (keyboardState[SDL_SCANCODE_DOWN]) {
				g_input = 4;
			}

			if (keyboardState[SDL_SCANCODE_SPACE]) {

				Mix_PlayChannel(-1, g_gun_sound, 0);
				Mix_Volume(-1, 100000);


				g_destination_pos.x = g_destination_rect.x + 35;
				g_destination_pos.y = g_destination_rect.y;
				g_XY.push_back(std::make_pair(g_destination_pos.x, g_destination_pos.y));

				m_input = 1;


				//Score
				{
					score += 10;

					TTF_Font* font2 = TTF_OpenFont("../../Resources/NeoDunggeunmoPro-Regular.ttf", 30);
					SDL_Color black = { 0, 0, 0, 0 };


					SDL_Surface* tmp_surface = TTF_RenderText_Blended(font2, std::to_string(score).c_str(), black);

					g_title_sc_rect.x = 0;
					g_title_sc_rect.y = 0;
					g_title_sc_rect.w = tmp_surface->w;
					g_title_sc_rect.h = tmp_surface->h;

					g_title_sc = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
					SDL_FreeSurface(tmp_surface);
					TTF_CloseFont(font2);
				}
			}
			break;

		case SDL_KEYUP:
			if (!keyboardState[SDL_SCANCODE_LEFT] && !keyboardState[SDL_SCANCODE_RIGHT] && !keyboardState[SDL_SCANCODE_UP] && !keyboardState[SDL_SCANCODE_DOWN]) {
				g_input = 0;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				timerStart = SDL_GetTicks();
				timerStarted = true;
				Mix_Music* s_g_bg_mus;
				s_g_bg_mus = Mix_LoadMUS("../../Resources/start_bgm.wav");
				Mix_PlayMusic(s_g_bg_mus, -1);

				if (count == 4) {
					s_input = 1;
				}
				else if (count != 4) {
					count = 4;
					s_input = 1;
					score = 0;
				}


			}
			break;

		default:
			break;
		}
	}


	
	
		

}
