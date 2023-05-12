//GameMode2.cpp
#include "Game.h"
#include "GameMode2.h"
#include <vector>
#include <cstdlib>

using namespace std;

// bg
SDL_Surface* bg_surface;
SDL_Texture* bg_texture;
SDL_Rect bg_rect;
SDL_Rect bg_dest_rect;

// wall
SDL_Surface* wall_surface;
SDL_Texture* wall_texture;
SDL_Rect wall_rect;
SDL_Rect wall_dest_rect;

// hold
vector<string> hold_paths = { "../src/redHold.png", "../src/greenHold.png", "../src/blueHold.png" };
vector<SDL_Surface*> hold_surfaces;
vector<SDL_Texture*> hold_textures;
vector<SDL_Rect> hold_rects;
vector<SDL_Rect> hold_dest_rects;
int leftHoldY = 475;
int rightHoldY = 400;

// leftUser
SDL_Surface* leftUser_surface;
SDL_Texture* leftUser_texture;
SDL_Rect leftUser_rect;
SDL_Rect leftUser_dest_rect;

// rightUser
SDL_Surface* rightUser_surface;
SDL_Texture* rightUser_texture;
SDL_Rect rightUser_rect;
SDL_Rect rightUser_dest_rect;


Mode2::Mode2() {
	g_flag_running = true;

	// 배경 이미지 로드
	bg_surface = IMG_Load("../src/bg_mode2.png");
	bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface); // GPU로 옮기기 
	SDL_FreeSurface(bg_surface);
	bg_rect = { 0, 0, 800, 600 };
	bg_dest_rect = { 0, 0, 800, 600 };

	// wall 이미지 로드
	wall_surface = IMG_Load("../src/wall.png");
	wall_texture = SDL_CreateTextureFromSurface(g_renderer, wall_surface); // GPU로 옮기기 
	SDL_FreeSurface(wall_surface);
	wall_rect = { 0, 0, 400, 600 };
	wall_dest_rect = { 200, 0, 400, 600 };

	srand((unsigned)time(NULL)); // srand는 한 번만 호출해야 합니다.
	for (int i = 0; i < 40; i++) {
		int random_hold_idx = rand() % 3; // 0~2 중 하나의 인덱스를 무작위로 선택
		string hold_path = hold_paths[random_hold_idx];
		SDL_Surface* hold_surface = IMG_Load(hold_path.c_str());
		SDL_Texture* hold_texture = SDL_CreateTextureFromSurface(g_renderer, hold_surface);
		SDL_FreeSurface(hold_surface);
		hold_surfaces.push_back(hold_surface);
		hold_textures.push_back(hold_texture);
		SDL_Rect hold_rect = { 0, 0, hold_surface->w, hold_surface->h };
		hold_rects.push_back(hold_rect);
		if (i % 2 == 0) {
			SDL_Rect hold_dest_rect = { 270, leftHoldY , hold_surface->w, hold_surface->h };
			hold_dest_rects.push_back(hold_dest_rect);
			leftHoldY -= 150;
		}
		else {
			SDL_Rect hold_dest_rect = { 470, rightHoldY , hold_surface->w, hold_surface->h };
			hold_dest_rects.push_back(hold_dest_rect);
			rightHoldY -= 150;
		}
	}

	// leftUser
	leftUser_surface = IMG_Load("../src/leftUser.png");
	leftUser_texture = SDL_CreateTextureFromSurface(g_renderer, leftUser_surface);
	SDL_FreeSurface(leftUser_surface);
	leftUser_rect = { 0, 0, leftUser_surface->w, leftUser_surface->h };
	leftUser_dest_rect = { 240, 427, leftUser_surface->w, leftUser_surface->h };

	// rightUser
	rightUser_surface = IMG_Load("../src/rightUser.png");
	rightUser_texture = SDL_CreateTextureFromSurface(g_renderer, rightUser_surface);
	SDL_FreeSurface(rightUser_surface);
	rightUser_rect = { 0, 0, rightUser_surface->w, rightUser_surface->h };
	rightUser_dest_rect = { 240, 427, rightUser_surface->w, rightUser_surface->h };
}

Mode2::~Mode2() {
	SDL_DestroyTexture(bg_texture);
	SDL_DestroyTexture(wall_texture);

	for (SDL_Texture* texture : hold_textures) {
		SDL_DestroyTexture(texture);
	}
	for (SDL_Texture* texture : hold_textures) {
		SDL_DestroyTexture(texture);
	}
	SDL_DestroyTexture(leftUser_texture);
	SDL_DestroyTexture(rightUser_texture);
}

void Mode2::Update()
{

}

void Mode2 ::Render() {
	SDL_RenderClear(g_renderer);
	SDL_RenderCopy(g_renderer, bg_texture, &bg_rect, &bg_dest_rect);
	SDL_RenderCopy(g_renderer, wall_texture, &wall_rect, &wall_dest_rect);

	for (size_t i = 0; i < hold_textures.size(); i++) {
		SDL_RenderCopy(g_renderer, hold_textures[i], &hold_rects[i], &hold_dest_rects[i]);
	}

	for (size_t i = 0; i < hold_textures.size(); i++) {
		SDL_RenderCopy(g_renderer, hold_textures[i], &hold_rects[i], &hold_dest_rects[i]);
	}

	SDL_RenderCopy(g_renderer, leftUser_texture, &leftUser_rect, &leftUser_dest_rect);

	SDL_RenderPresent(g_renderer);
}

bool isLeftUser = true;

void Mode2 :: userMove() {
	wall_dest_rect.y += 30;
	bg_dest_rect.y += 5;

	//왼쪽유저일때 오른쪽유저로 바꾸기
	if (isLeftUser) {
		leftUser_dest_rect.x += 200;
		rightUser_dest_rect.x -= 200;
	}
	//오른쪽유저일때 왼쪽유저로 바꾸기
	else {
		leftUser_dest_rect.x -= 200;
		rightUser_dest_rect.x += 200;
	}

	SDL_Surface* tempSurface = leftUser_surface;
	leftUser_surface = rightUser_surface;
	rightUser_surface = tempSurface;

	SDL_Texture* tempTexture = leftUser_texture;
	leftUser_texture = rightUser_texture;
	rightUser_texture = tempTexture;

	isLeftUser = !isLeftUser;
}

void Mode2::holdMove() {
	for (SDL_Rect& hold_dest_rect : hold_dest_rects) {
		hold_dest_rect.y += 75;
	}
}

void Mode2::HandleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_r) {
				//if(다음홀드 == SDLK_r){
				userMove();
				holdMove();
				//}
				//else { 게임오버 }
			}

			else if (event.key.keysym.sym == SDLK_g) {
				userMove();
				holdMove();
			}

			else if (event.key.keysym.sym == SDLK_b) {
				userMove();
				holdMove();
			}
		default:
			break;
		}
	}
}