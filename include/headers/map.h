#pragma once
#include<headers/overlord.h>
#include <headers/mediafiles.h>

class Map{
    public:
    Map();
    ~Map();

    void LoadMap(int arr[22][70]);
    void Draw();

    private:

    SDL_Rect src, dest;
    SDL_Texture* tileset; 

    int map [22][70];
};