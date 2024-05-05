#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
        int move;
        SDL_Window* window;
        SDL_Renderer* renderer;
        //SDL_Rect rectOriginUser;
        //SDL_Rect rectSourceUser;
        SDL_Rect destinationBackground;
        SDL_Rect destinationMirrorBackground;
        std::vector<SDL_Texture*> mainBackground;
        SDL_Texture* background_init;
    

        void Init(const char* name, const int& posX, const int& posY, const int& width, const int& height, const uint32_t flags);
        void MenuInit();
        void GameLoop();
        void CheckInput();
        void HandleEvents();
        void Close();
        SDL_Texture* CreateTexture(const char* path);
        void LoadTextures(const std::vector<char*>& paths, std::vector<SDL_Texture*>& textures);
        void BackgroundLoop(int& movement);
};