#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <headers/mediafiles.h>
#include <vector>

class OverLord
{
    public:
        //Constructor y Destructor
        OverLord();
        ~OverLord();

        //Funciones Publicas
        void Run();

        //static SDL_Renderer* renderer; //renderizador
        
    private:
        //Atributos
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
        SDL_Rect motion_Sky;
        SDL_Rect motionMirror_sky;
        SDL_Rect motion_CL;
        SDL_Rect motion_CD;
        SDL_Rect motionMirror_CL;
        SDL_Rect motionMirror_CD;
        SDL_Rect location_Name;
        SDL_Rect location_PressToStar;
        
        //SDL_Texture* background_init;
        SDL_Texture* name_Init;
        SDL_Texture* pressToStar;
        SDL_Texture* sky;
        SDL_Texture* cloud_Dark;
        SDL_Texture* cloud_Light;

        //Update 
        int move;
        int state;
        bool IsRight;
        bool IsJumping;
        bool IsFixed;
        
        //Render
        //Animacion del personaje.
        int frameIndexPlayer;
        SDL_Texture* PJ;
        SDL_Rect sourceWarriorRect;
        SDL_Rect updateWarriorRect;

        //Funciones Privadas
        void Init(const char* name, const int& posX, const int& posY, const int& width, const int& height, const uint32_t flags);
        void MenuInit();
        void GameLoop();
        void HandleEvents();
        void Update();
        void Render();
        void Close();
        void BackgroundLoop();
};