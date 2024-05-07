#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <headers/mediaFiles.h>
#include <vector>

class OverLord
{
    public:
        OverLord();
        ~OverLord();
        void Run();

    private:
        bool gameState;
        char* gameName;
        int screenWidth;
        int screenHeigth;
        
        SDL_Window* window;
        MediaFiles media;

        //Fondo In Game
        SDL_Rect destinationBackground;
        SDL_Rect destinationMirrorBackground;
        std::vector<SDL_Texture*> mainBackground;

        //Fondo Inicial
        SDL_Texture* background_init;

        //Update 
        int move;
        int running;
        bool jump;
        
        //Render
        //Animacion del personaje.
        int frameIndexPlayer;
        SDL_Texture* PJ;
        SDL_Rect sourceWarriorRect;
        SDL_Rect updateWarriorRect;

    
        void Init(const char* name, const int& posX, const int& posY, const int& width, const int& height, const uint32_t flags);
        void MenuInit();
        void GameLoop();
        void HandleEvents();
        void Update();
        void Render();
        void Close();
        void BackgroundLoop();
};