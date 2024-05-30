#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Map{

    public:
        Map();
        ~Map();

        void LoadMap(int arr[24][64]);

        SDL_Rect* GetSourceLand();
        SDL_Rect* GetDestinyLand();
        SDL_Texture* GetTileset();
        void SetTileset(SDL_Texture* value);

        SDL_Rect* GetDestinyBackground();
        std::vector<SDL_Texture*>* GetBackground();

        int GetPosMap(const int& row, const int& column);
        int GetNumHeigth();
        int GetNumWidth();

    private:
        SDL_Rect srcLand;
        SDL_Rect destLand;
        SDL_Texture* tileset; 

        SDL_Rect destBackground;
        std::vector<SDL_Texture*> background;

        int map [24][64];
        int numBlocksHeigth;
        int numBlocksWidth;
};