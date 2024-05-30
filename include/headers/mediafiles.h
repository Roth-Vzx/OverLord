#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <headers/map.h>
#include <headers/player.h>
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

        void SetScreenWidth(int value);
        void SetScreenHeigth(int value);

        std::vector<SDL_Texture*>* GetMapBackground();
        void SetBackground(const std::vector<char*>& paths);

        SDL_Texture* GetLandTexture();
        Map* GetLevels();

        //Funciones
        SDL_Texture* CreateTexture(const char* path);
        void LoadTextures(const std::vector<char*>& paths, std::vector<SDL_Texture*>& textures);
        void CopyFullTextures(std::vector<SDL_Texture*> textures);
        
        void DrawPJ(SDL_Texture* PJtexture, SDL_Rect& source, SDL_Rect& destiny, int& state,const bool& IsLeft, bool& IsJumping, bool& IsFixed);
        void DrawPJ(Player& PJ);
        void DrawEnemy(Player& PJ);
        void DoFixedAnimation(const int& start, const int& numFrames, const int& framesPerRow, const int& duration, SDL_Rect& source, bool& IsFixed, std::pair<std::stack<int>,bool>& uniqueStackAnimation);

        //Map
        void DrawDoubleFrame(SDL_Texture* texture, SDL_Rect& destiny, const int& movement);
        void DrawDoubleFrame(SDL_Texture* texture, SDL_Rect& destiny, int& movement);
        void DrawDoubleFrame(SDL_Texture* texture, SDL_Rect& source, SDL_Rect& destiny, int& movement);
        void DrawMap(int& movement);
        void DrawBackground(int& movement);
        void DrawLevel(Player& PJ, Player& enemy, int& movement);

    private:

        int screenWidth;        
        int screenHeigth;
        Map Levels;
        SDL_Renderer* renderer;

        int ApplyMovement(const int& movement);
};