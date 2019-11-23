#include "renderer.h"
#include "spaceship.h"
#include "missile.h"
#include "explosion.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <future>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

/**
 * Constructor for Renderer
 * After initializing SDL and creates SDL Window,
 * it creates textures for texts and images.
 */
Renderer::Renderer()
{
   if (SDL_Init(SDL_INIT_VIDEO) < 0)
   {
      std::cerr << "SDL could not initialize.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
   }

   window_ = SDL_CreateWindow("Asteroids",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  SCREEN_WIDTH,
                                  SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
   if (nullptr == window_)
   {
      std::cerr << "Window could not be created.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
   }
   
   InitializeTexts();
   InitializeImages();
}

/**
 * Initializes texts for dispaying game score and "gameover" 
 */
void Renderer::InitializeTexts()
{
   TTF_Init();
   
   score_font_ = TTF_OpenFont(SYSTEM_FONT_PATH, 30);
   game_over_font_ = TTF_OpenFont(SYSTEM_FONT_PATH, 30);
   
   if (!score_font_ || !game_over_font_)
   {
      std::cerr << "Font opening error!\n";
      std::cerr << TTF_GetError() << "\n";
   }  
}

/**
 * Initializes images for spaceship, enemies and explosions.
 */ 
void Renderer::InitializeImages()
{
   renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
   if (nullptr == renderer_)
   {
      std::cerr << "Renderer could not be created.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
   }

   int img_flag = IMG_INIT_PNG;
   if (IMG_Init(img_flag) && img_flag)
   {
      bg_sf_ = IMG_Load(BACKGROUND_IMG_PATH);
      if (!bg_sf_)
      {
         std::cerr << "IMG_Load for Background failed: " << IMG_GetError() << "\n";
      }
      else
      {
         bg_tx_ = SDL_CreateTextureFromSurface(renderer_, bg_sf_);
      }
      
      spaceship_sf_ = IMG_Load(SPACESHIP_IMG_PATH);
      if (!spaceship_sf_)
      {
         std::cerr << "IMG_Load for Spaceship failed: " << IMG_GetError() << "\n";
      }
      else
      {
         spaceship_tx_ = SDL_CreateTextureFromSurface(renderer_, spaceship_sf_);
      }

      enemy_sf_ = IMG_Load(ENEMY_IMG_PATH);
      if (!enemy_sf_)
      {
         std::cerr << "IMG_Load for Enemy failed: " << IMG_GetError() << "\n";
      }
      else
      {
         enemy_tx_ = SDL_CreateTextureFromSurface(renderer_, enemy_sf_);
      }

      enmy_exp_sf_ = IMG_Load(EXPLOSION1_IMG_PATH);
      if (!enmy_exp_sf_)
      {
         std::cerr << "IMG_Load for Enemy Explosion failed: " << IMG_GetError() << "\n";
      }
      else
      {
         enmy_exp_tx_ = SDL_CreateTextureFromSurface(renderer_, enmy_exp_sf_);
      }

      spsp_exp_sf_ = IMG_Load(EXPLOSION2_IMG_PATH);
      if (!spsp_exp_sf_)
      {
         std::cerr << "IMG_Load for Spaceship Explosion failed: " << IMG_GetError() << "\n";
      }
      else
      {
         spsp_exp_tx_ = SDL_CreateTextureFromSurface(renderer_, spsp_exp_sf_);
      }
   }
   else
   {
      std::cerr << "IMG_Init failed: " << IMG_GetError() << "\n";
   }
}

/**
 * Render the provided SDL Texture at the provided position
 */
void Renderer::RenderTexture(SDL_Texture *txt, Position pos)
{
   int w_bg, h_bg;
   SDL_QueryTexture(txt, NULL, NULL, &w_bg, &h_bg);
   SDL_Rect bg_dest = (SDL_Rect){(int) pos.x, (int) pos.y, w_bg, h_bg};
   SDL_RenderCopy(renderer_, txt, nullptr, &bg_dest);
}

/**
 * Render background, spaceship, enemies, missiles, score and explosions.
 */
void Renderer::Render(Spaceship const spaceship, std::deque<Enemy> const enemies, int score)
{
   // Render background
   RenderTexture(bg_tx_, (Position) {0, 0});
   
   // Render missiles
   std::for_each(spaceship.missiles_.begin(), spaceship.missiles_.end(), [this] (Missile m) {
      SDL_Rect missileRect = (SDL_Rect) {(int) m.GetTopLeftCornerPosition().x, (int) m.GetTopLeftCornerPosition().y, 10, 10};
      SDL_SetRenderDrawColor(renderer_, 255, 255, 0, 255);
      SDL_RenderFillRect(renderer_, &missileRect);
   });
   
   // Render enemies
   std::for_each(enemies.begin(), enemies.end(), [this] (Enemy e) {
      if (e.IsAlive())
      {
         int w_enemy, h_enemy;
         SDL_QueryTexture(enemy_tx_, NULL, NULL, &w_enemy, &h_enemy);
         SDL_Rect enemy_dest = (SDL_Rect) {(int) e.GetTopLeftCornerPosition().x, (int) e.GetTopLeftCornerPosition().y, w_enemy, h_enemy};
         
         SDL_RenderCopyEx(renderer_,
                          enemy_tx_,
                          nullptr,
                          &enemy_dest,
                          e.angle_,
                          nullptr,
                          SDL_FLIP_NONE);
      }
      else
      {
         // Render explosion if the enemy is no longer alive
         Explosion *exp = e.GetExplosion();
         SDL_SetTextureAlphaMod(enmy_exp_tx_, exp->alpha_);
         RenderTexture(enmy_exp_tx_, (Position) {exp->GetTopLeftCornerPosition().x, exp->GetTopLeftCornerPosition().y});
      }
   });

   // Render score
   RenderScore(score);

   // Render spaceship
   RenderTexture(spaceship_tx_, (Position) {spaceship.GetTopLeftCornerPosition().x, spaceship.GetTopLeftCornerPosition().y});

   // If spaceship is no longer alive then render explosion and game over text
   if (!spaceship.IsAlive())
   {
      RenderTexture(spsp_exp_tx_, (Position) {spaceship.GetTopLeftCornerPosition().x - 10, spaceship.GetTopLeftCornerPosition().y - 10});
      RenderGameOver();
   }

   SDL_RenderPresent(renderer_);
}

/**
 * Render "Game over" text
 */ 
void Renderer::RenderGameOver()
{
   SDL_Color red = {255, 255, 0};
   std::string game_over_str = "Game over...Press c to continue.";
   gameover_sf_ = TTF_RenderText_Solid(game_over_font_, game_over_str.c_str(), red);
   gameover_tx_ = SDL_CreateTextureFromSurface(renderer_, gameover_sf_);

   RenderTexture(gameover_tx_, (Position) {SCREEN_WIDTH/6, SCREEN_HEIGHT/2});
}

/**
 * Update the texture with the current score and render it
 */
void Renderer::RenderScore(int score)
{
   SDL_Color white = {255, 255, 255};
   std::string score_str = "Score: " + std::to_string(score);
   score_sf_ = TTF_RenderText_Solid(score_font_, score_str.c_str(), white);
   score_tx_ = SDL_CreateTextureFromSurface(renderer_, score_sf_);

   RenderTexture(score_tx_, (Position) {0, 0});
}

/**
 * Update window title
 */
void Renderer::UpdateWindowTitle()
{
   std::string title = "Spaceshooter";
   SDL_SetWindowTitle(window_, title.c_str());
}

/**
 * Destructor for Renderer
 */
Renderer::~Renderer()
{
   IMG_Quit();
   TTF_CloseFont(score_font_);
   TTF_Quit();

   SDL_FreeSurface(bg_sf_);
   SDL_DestroyTexture(score_tx_);

   SDL_FreeSurface(score_sf_);
   SDL_DestroyTexture(score_tx_);

   SDL_FreeSurface(spaceship_sf_);
   SDL_DestroyTexture(spaceship_tx_);
   
   SDL_FreeSurface(enemy_sf_);
   SDL_DestroyTexture(enemy_tx_);

   SDL_FreeSurface(enmy_exp_sf_);
   SDL_DestroyTexture(enmy_exp_tx_);
   SDL_FreeSurface(spsp_exp_sf_);
   SDL_DestroyTexture(spsp_exp_tx_);

   SDL_DestroyRenderer(renderer_);
   SDL_DestroyWindow(window_);
   SDL_Quit();
}