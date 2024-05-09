#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class MediaFiles
{
    public:
        //Constructor y Destructor
        MediaFiles();
        ~MediaFiles();

        //Getters y Setters
        SDL_Renderer* GetRenderer();
        void SetRenderer(SDL_Renderer* value);
        void SetScreenWidth(int Width);
        void SetLimitY(int Heigth);
        int GetLimitY();
        
        //Funciones
        SDL_Texture* CreateTexture(const char* path);
        void LoadTextures(const std::vector<char*>& paths, std::vector<SDL_Texture*>& textures);
        void CopyFullTextures(std::vector<SDL_Texture*> textures);
        void DrawPJ(SDL_Texture* PJtexture, SDL_Rect& source, SDL_Rect& destiny, const int& state,const bool& isLeft, bool& jump);

    private:
        SDL_Renderer* renderer; //renderizador
        int screenWidth;        
        int LimitY;             //Limite para dibujar en el eje Y; en otras palabras, "El Suelo"
};