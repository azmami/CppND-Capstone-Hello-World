#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
#include "spaceship.h"
#include "enemy.h"

/**
 * Renderer class.
 * This class initializes SDL library and renders the window and game objects.
 */ 
class Renderer
{
public:
   const char* BACKGROUND_IMG_PATH = "../asset/background.png";
   const char* SPACESHIP_IMG_PATH = "../asset/spaceship.png";
   const char* ENEMY_IMG_PATH = "../asset/asteroid.png";
   const char* EXPLOSION1_IMG_PATH = "../asset/explosion.png";
   const char* EXPLOSION2_IMG_PATH = "../asset/explosion2.png";
   const char* SYSTEM_FONT_PATH = "/Library/Fonts/Arial.ttf";

   Renderer();
   ~Renderer();

   void InitializeTexts();
   void InitializeImages();
   void Render(Spaceship const spaceship, std::deque<Enemy> const enemies, int score);
   void UpdateWindowTitle();
   void RenderScore(int score);
   void RenderGameOver();
   void RenderTexture(SDL_Texture *txt, Position pos);

   // window and renderer
   SDL_Window *window_;
   SDL_Renderer *renderer_;

   // Background
   SDL_Texture *bg_tx_;
   SDL_Surface *bg_sf_;

   // Spaceship
   SDL_Texture *spaceship_tx_;
   SDL_Surface *spaceship_sf_;
   
   // Enemy
   SDL_Texture *enemy_tx_;
   SDL_Surface *enemy_sf_;

   // Expolosion effect
   SDL_Texture *enmy_exp_tx_;
   SDL_Surface *enmy_exp_sf_;
   SDL_Texture *spsp_exp_tx_;
   SDL_Surface *spsp_exp_sf_;

   // Text
   TTF_Font *score_font_;
   TTF_Font *game_over_font_;
   SDL_Texture *score_tx_;
   SDL_Surface *score_sf_;
   SDL_Texture *gameover_tx_;
   SDL_Surface *gameover_sf_;
};

#endif