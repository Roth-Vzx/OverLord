#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
        SDL_Renderer* renderer;
        SDL_Surface* screenSurface;
        SDL_Surface* backGround1;
        SDL_Surface* backGround2;

        void Init(const char* name, const int& posX, const int& posY, const int& width, const int& height, const uint32_t flags);
        void GameLoop();
        void HandleEvents();
        void Close();
        void LoadMedia();
        void BackgroundLoop(int& x,int& y);
};