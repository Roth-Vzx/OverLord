#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <headers/mediafiles.h>
#include <headers/player.h>
#include <vector>

class OverLord
{
    public:
        //Constructor y Destructor
        OverLord();
        ~OverLord();

        //Funciones Publicas
        void Run();
        
    private:
        //Atributos
        bool gameState;
        char* gameName;
        int screenWidth;
        int screenHeigth;
        SDL_Window* window;
        MediaFiles media;
        
        //SDL_Texture* background_init;
        SDL_Texture* name_Init;
        SDL_Texture* pressToStar;
        SDL_Texture* sky;
        SDL_Texture* cloud_Dark;
        SDL_Texture* cloud_Light;

        Player mainPJ;
        Player enemy;

        //Update 
        int movePlayer;
        
        //Render
        //Animacion del personaje.
        int frameIndexPlayer;

        //Funciones Privadas
        void Init(const char* name, const int& posX, const int& posY, const int& width, const int& height, const uint32_t flags);
        void MenuInit();
        void GameLoop();
        void HandleEvents();
        void Update();
        void Render();
        void DestroyTexture(SDL_Texture*& texture);
        void Close();
        void GenerateDelay(const double& start, const int& msPerframe);
};