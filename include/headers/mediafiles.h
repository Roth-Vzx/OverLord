#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class MediaFiles
{
    public:
        MediaFiles();
        ~MediaFiles();

        SDL_Renderer* GetRenderer();
        void SetRenderer(SDL_Renderer* value);
        
        SDL_Texture* CreateTexture(const char* path);
        void LoadTextures(const std::vector<char*>& paths, std::vector<SDL_Texture*>& textures);
        void CopyFullTextures(std::vector<SDL_Texture*> textures);
        void DrawPJ(SDL_Texture* PJtexture, SDL_Rect& source, SDL_Rect& destiny, const int& state,const bool& isLeft, const bool& jump);

    private:
        SDL_Renderer* renderer;   
};