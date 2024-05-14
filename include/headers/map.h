#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Map{

    public:
        Map();
        ~Map();

        void LoadMap(int arr[22][70]);

        void SetSourceX(int value);
        void SetDestinyX(int value);
        void SetSourceY(int value);
        void SetDestinyY(int value);

        SDL_Rect* GetSource();
        SDL_Rect* GetDestiny();
        SDL_Texture* GetTileset();
        void SetTileset(SDL_Texture* value);

        int GetPosMap(const int& row, const int& column);

    private:
        SDL_Rect src, dest;
        SDL_Texture* tileset; 
        int map [22][70];
};