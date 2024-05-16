#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Player
{
    public:
        //Constructor y Destructor
        Player();
        ~Player();

        //Getters y Setters
            //Texturas
                void SetTexture(SDL_Texture* value);
                void SetframeIndexTexture(int frameIndex);
                void SetSourceTexture(SDL_Rect sourceTexture);
                void SetUpdateTexture(SDL_Rect updateTexture);

                SDL_Texture* GetTexture();
                int GetframeIndexTexture();
                SDL_Rect* GetSourceTexture();
                SDL_Rect* GetUpdateTexture();

                void SetSourceX(int value);
                void SetSourceY(int value);

                void SetUpdateX(int value);
                void SetUpdateY(int value);

            //state for pj 
                void SetJump(bool value);
                void SetLimitY(int value);
                void SetState(int value);
                void SetIsRight(bool value);
                void SetIsFixed(bool value);

                void SetHeal(int value);
                void SetArmor(int value);

                int GetState();
                int GetLimitY();
                bool GetIsRight();
                bool GetJump();
                bool* GetIsFixed();

                int GetHeal();
                int GetArmor();

        //Funciones
            //Acciones
            void PJattack();
            void PJump();

            //update.
            void PjUpdate();

    private:
        //Texturas
        int frameIndexTexture;
        SDL_Texture* Texture;
        SDL_Rect sourceTextureRect, updateTextureRect;
        
        //stats
        int heal;
        int armor;

        //Estados.
        int state;
        int limitY;
        bool isRight;
        bool jump;
        bool isFixed;
};