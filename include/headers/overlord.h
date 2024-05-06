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
        
        SDL_Window* window;
        SDL_Renderer* renderer;
        //SDL_Rect rectOriginUser;
        //SDL_Rect rectSourceUser;
        SDL_Rect destinationBackground;
        SDL_Rect destinationMirrorBackground;
        std::vector<SDL_Texture*> mainBackground;
        SDL_Texture* background_init;

        //Update 
        int move;
        int running;
        bool jump;
        
        //Render
        //Animacion del personaje.
        int frameIndexPlayer;
        SDL_Rect sourceWarriorRect;
        SDL_Rect updateWarriorRect;

    

        void Init(const char* name, const int& posX, const int& posY, const int& width, const int& height, const uint32_t flags);
        void MenuInit();
        void GameLoop();
        void HandleEvents();
        void Update();
        void Render();
        void Close();
        SDL_Texture* CreateTexture(const char* path);
        void LoadTextures(const std::vector<char*>& paths, std::vector<SDL_Texture*>& textures);
        void BackgroundLoop(int& movement);
        void DrawPJ();
};