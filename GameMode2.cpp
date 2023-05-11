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

// left hold
vector<string> leftHold_paths = { "../src/redHold.png", "../src/greenHold.png", "../src/blueHold.png" };
vector<SDL_Surface*> leftHold_surfaces;
vector<SDL_Texture*> leftHold_textures;
vector<SDL_Rect> leftHold_rects;
vector<SDL_Rect> leftHold_dest_rects;
int leftHoldY = 475;

// right hold
vector<string> rightHold_paths = { "../src/redHold.png", "../src/greenHold.png", "../src/blueHold.png" };
vector<SDL_Surface*> rightHold_surfaces;
vector<SDL_Texture*> rightHold_textures;
vector<SDL_Rect> rightHold_rects;
vector<SDL_Rect> rightHold_dest_rects;
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

	// left hold 이미지 로드
	srand((unsigned)time(NULL)); // srand는 한 번만 호출해야 합니다.
	for (int i = 0; i < 20; i++) {
		int random_hold_idx = rand() % 3; // 0~2 중 하나의 인덱스를 무작위로 선택
		string hold_path = leftHold_paths[random_hold_idx];
		SDL_Surface* hold_surface = IMG_Load(hold_path.c_str());
		SDL_Texture* hold_texture = SDL_CreateTextureFromSurface(g_renderer, hold_surface);
		SDL_FreeSurface(hold_surface);
		leftHold_surfaces.push_back(hold_surface);
		leftHold_textures.push_back(hold_texture);
		SDL_Rect hold_rect = { 0, 0, hold_surface->w, hold_surface->h };
		leftHold_rects.push_back(hold_rect);
		SDL_Rect hold_dest_rect = { 270, leftHoldY , hold_surface->w, hold_surface->h };
		leftHold_dest_rects.push_back(hold_dest_rect);
		leftHoldY -= 150;
	}
	// right hold 이미지
	for (int i = 0; i < 20; i++) {
		int random_hold_idx = rand() % 3; // 0~2 중 하나의 인덱스를 무작위로 선택
		string hold_path = rightHold_paths[random_hold_idx];
		SDL_Surface* hold_surface = IMG_Load(hold_path.c_str());
		SDL_Texture* hold_texture = SDL_CreateTextureFromSurface(g_renderer, hold_surface);
		SDL_FreeSurface(hold_surface);
		rightHold_surfaces.push_back(hold_surface);
		rightHold_textures.push_back(hold_texture);
		SDL_Rect hold_rect = { 0, 0, hold_surface->w, hold_surface->h };
		rightHold_rects.push_back(hold_rect);
		SDL_Rect hold_dest_rect = { 470, rightHoldY , hold_surface->w, hold_surface->h };
		rightHold_dest_rects.push_back(hold_dest_rect);
		rightHoldY -= 150;
	}

	// leftUser
	leftUser_surface = IMG_Load("../src/leftUser.png");
	leftUser_texture = SDL_CreateTextureFromSurface(g_renderer, leftUser_surface);
	SDL_FreeSurface(leftUser_surface);
	leftUser_rect = { 0, 0, leftUser_surface->w, leftUser_surface->h };
	leftUser_dest_rect = { 240, 400, leftUser_surface->w, leftUser_surface->h };

	// rightUser
	rightUser_surface = IMG_Load("../src/rightUser.png");
	rightUser_texture = SDL_CreateTextureFromSurface(g_renderer, rightUser_surface);
	SDL_FreeSurface(rightUser_surface);
	rightUser_rect = { 0, 0, rightUser_surface->w, rightUser_surface->h };
	rightUser_dest_rect = { 440, 400, rightUser_surface->w, rightUser_surface->h };
}

Mode2::~Mode2() {
	SDL_DestroyTexture(bg_texture);
	SDL_DestroyTexture(wall_texture);
	//SDL_DestroyTexture(hold_texture);
	for (SDL_Texture* texture : leftHold_textures) {
		SDL_DestroyTexture(texture);
	}
	for (SDL_Texture* texture : rightHold_textures) {
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

	SDL_RenderCopy(g_renderer, leftUser_texture, &leftUser_rect, &leftUser_dest_rect);
	SDL_RenderCopy(g_renderer, rightUser_texture, &rightUser_rect, &rightUser_dest_rect);
	// SDL_RenderCopy(g_renderer, hold_texture, &hold_rect, &hold_dest_rect);
	for (size_t i = 0; i < leftHold_textures.size(); i++) {
		SDL_RenderCopy(g_renderer, leftHold_textures[i], &leftHold_rects[i], &leftHold_dest_rects[i]);
	}

	for (size_t i = 0; i < rightHold_textures.size(); i++) {
		SDL_RenderCopy(g_renderer, rightHold_textures[i], &rightHold_rects[i], &rightHold_dest_rects[i]);
	}

	SDL_RenderPresent(g_renderer);
}

void Mode2::HandleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LEFT) {
				// 다음 돌이 leftHold일 때 hold, wall, bg 내려가기
				// 아닌경우 stun효과?
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				// 다음 돌이 rightHold일 때 hold, wall, bg 내려가기
				// 아닌경우 stun효과?
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				// 다음 돌이 upHold일 때 hold, wall, bg 내려가기
				// 아닌경우 stun효과?
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				// 다음 돌이 downHold일 때 hold, wall, bg 내려가기
				// 아닌경우 stun효과?
			}
			break;

		default:
			break;
		}
	}
}