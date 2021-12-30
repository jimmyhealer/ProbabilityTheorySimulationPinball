#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <climits>
#include <cstring>
#include <ctime>
#include <iostream>
#include <random>

#include "../lib/SDL_FontCache.h"
using namespace std;
mt19937 gen(0x5EED);
int randint(int lb, int ub) {
  return uniform_int_distribution<int>(lb, ub)(gen);
}
const int WIDTH = 800;
const int HEIGHT = 600;
SDL_Renderer* renderer;
SDL_Window* window;

int main(int argv, char** args) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    return 1;
  }

  window = SDL_CreateWindow("00957125 機率論作業 HW5", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                            SDL_WINDOW_OPENGL);
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  SDL_SetRenderDrawColor(renderer, 32, 42, 67, 255);
  SDL_RenderClear(renderer);
  FC_Font* font = FC_CreateFont();
  FC_Font* h2 = FC_CreateFont();
  FC_Font* h3 = FC_CreateFont();
  FC_Font* p = FC_CreateFont();
  FC_LoadFont(font, renderer, "../sources/minu.ttf", 60, FC_MakeColor(0, 200, 0, 255),
              TTF_STYLE_NORMAL);
  FC_LoadFont(h2, renderer, "../sources/minu.ttf", 40, FC_MakeColor(255, 255, 255, 255),
              TTF_STYLE_NORMAL);
  FC_LoadFont(h3, renderer, "../sources/minu.ttf", 22, FC_MakeColor(255, 255, 255, 255),
              TTF_STYLE_NORMAL);
  FC_LoadFont(p, renderer, "../sources/minu.ttf", 16, FC_MakeColor(255, 255, 255, 255),
              TTF_STYLE_NORMAL);

  SDL_StartTextInput();
  string in;
  bool running = true;
  srand(time(0));
  float loadingTime = rand() % 4;

  while (running) {
    SDL_Event event;
    FC_DrawAlign(font, renderer, 400, 200, FC_ALIGN_CENTER, "機率論作業");
    FC_DrawAlign(h2, renderer, 400, 270, FC_ALIGN_CENTER,
                 "模擬彈珠台掉落機率分布");
    FC_DrawAlign(h3, renderer, 400, 350, FC_ALIGN_CENTER,
                 "指導教授：許玉平教授");
    // FC_DrawAlign(h3, renderer, 400, 450, FC_ALIGN_CENTER, "按任意繼續");
    float time = SDL_GetTicks() / 1000.0f;
    int rgb = (int)min(255, 255 - (int)(sin(time) * 127));
    char* msg = "按任意鍵繼續";
    if (time < loadingTime) msg = "Loading...";
    FC_DrawEffect(h3, renderer, 400, 450,
                  {FC_ALIGN_CENTER, {1, 1}, FC_MakeColor(rgb, rgb, rgb, 255)},
                  msg);
    FC_DrawAlign(p, renderer, 790, 540, FC_ALIGN_RIGHT,
                 "使用 C++ 語言 及 SDL2 製作，Fork From : DaiDiaSo\n Author : "
                 "jimmyhealer 00957125 簡蔚驊");
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    if (time > 60) running = false;
    while (time >= loadingTime && SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
        running = false;
      } else if (event.type == SDL_QUIT) {
        return 0;
      }
    }
  }

  SDL_StopTextInput();
  FC_FreeFont(font);

  running = 1;
  SDL_Event event;
  SDL_Rect a;
  a.h = 100;
  a.w = 4;
  a.x = 100;
  a.y = 100;
  int height[102] = {0};
  int timer = 30;
  int con = 0;
  int help = 0;
  int cnt = 0;
  int ran1;
  int screenshot = 0;
  float screenshot_timer = 0;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_r) {
          memset(height, 0, sizeof(height));
          cnt = 0;
        } else if (event.key.keysym.sym == SDLK_KP_PLUS) {
          timer = timer - 10 < 0 ? 0 : timer - 10;
        } else if (event.key.keysym.sym == SDLK_KP_MINUS) {
          timer = timer + 10 > 100 ? 100 : timer + 10;
        } else if (event.key.keysym.sym == SDLK_q) {
          return 0;
        } else if (event.key.keysym.sym == SDLK_p) {
          con = !con;
        } else if (event.key.keysym.sym == SDLK_h) {
          help = !help;
        } else if (event.key.keysym.sym == SDLK_s) {
          std::time_t result = std::time(nullptr);
          SDL_Surface* sshot =
              SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0x00ff0000, 0x0000ff00,
                                   0x000000ff, 0xff000000);
          SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888,
                               sshot->pixels, sshot->pitch);
          char buf[256];
          strftime(buf, sizeof(buf), "screenshot_%Y-%m-%d_%H-%M-%S.bmp",
                   localtime(&result));
          SDL_SaveBMP(sshot, buf);
          SDL_FreeSurface(sshot);
          screenshot = 1;
          screenshot_timer = SDL_GetTicks();
        }
      }
    }
    if(screenshot) {
      if(SDL_GetTicks() - screenshot_timer > 2000) {
        screenshot = 0;
      }
    }
    SDL_SetRenderDrawColor(renderer, 32, 42, 67, 255);
    SDL_RenderClear(renderer);
    FC_DrawAlign(h3, renderer, 10, 30, FC_ALIGN_LEFT, "目前數量為: %d", cnt);
    FC_DrawAlign(p, renderer, 100, 550, FC_ALIGN_CENTER, "%d", 0);
    FC_DrawAlign(p, renderer, 400, 550, FC_ALIGN_CENTER, "%d", 50);
    FC_DrawAlign(p, renderer, 700, 550, FC_ALIGN_CENTER, "%d", 100);
    FC_DrawAlign(h3, renderer, 640, 30, FC_ALIGN_RIGHT, "%s",
                 screenshot ? "已儲存截圖" : "");
    FC_DrawAlign(h3, renderer, 650, 30, FC_ALIGN_LEFT, "%s",
                 help ? "按 h 關閉幫助" : "按 h 開啟幫助");
    FC_DrawAlign(h3, renderer, 650, 60, FC_ALIGN_LEFT, "%s",
                 help ? "按 q 關閉程式\n按 p 暫停模擬\n按 r 重新模擬\n按 + "
                        "加速模擬\n按 - 減速模擬\n按 s 儲存截圖"
                      : "");
    SDL_SetRenderDrawColor(renderer, 232, 171, 208, 0);
    FC_DrawAlign(h3, renderer, 10, 60, FC_ALIGN_LEFT, "%s",
                 con ? "暫停中" : "模擬中");

    if (!con) {
      ++cnt;
      ran1 = (sqrt(2500 - randint(0, INT_MAX) % 2501));
      if (randint(0, INT_MAX) % 2) {
        ran1 = 99 - ran1;
      }
      height[ran1]++;
    }
    for (int i = 0; i < 102; ++i) {
      a.x = i * 6 + 100;
      a.h = height[i] * 5;
      a.y = 550 - a.h;
      if (i == ran1) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &a);
        SDL_SetRenderDrawColor(renderer, 232, 171, 208, 0);
        continue;
      }
      SDL_RenderFillRect(renderer, &a);
    }
    SDL_Delay(timer);
    SDL_RenderPresent(renderer);
  }
  return 0;
}
