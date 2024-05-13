#pragma once
#include<headers/overlord.h>
#include <headers/mediafiles.h>

class Map{
    public:
    Map();
    ~Map();

    void LoadMap(int arr[10][35]);
    void Draw();

    private:

    SDL_Rect src, dest;
    SDL_Texture* tileset; 

    int map [10][35];
};