#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <stack>

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
        static SDL_Texture* CreateTexture(const char* path);
        void LoadTextures(const std::vector<char*>& paths, std::vector<SDL_Texture*>& textures);
        void CopyFullTextures(std::vector<SDL_Texture*> textures);
        void DrawPJ(SDL_Texture* PJtexture, SDL_Rect& source, SDL_Rect& destiny, int& state,const bool& IsLeft, bool& IsJumping, bool& IsFixed);
        void DoFixedAnimation(const int& start, const int& numFrames, const int& framesPerRow, SDL_Rect& source, bool& IsFixed);

        //Map
        static void DrawMap(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);

    private:
        int screenWidth;        
        int LimitY;             //Limite para dibujar en el eje Y; en otras palabras, "El Suelo"
        std::pair<std::stack<int>,bool> lastFrames;
};