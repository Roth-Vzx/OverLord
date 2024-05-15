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
                void SetJump(bool jump);
                void SetState(int state);
                void SetIsRight(bool isRight);
                void SetIsFixed(bool isFixed);

                void SetHeal(int state);
                void SetArmor(int state);

                int GetState();
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
        bool isRight;
        bool jump;
        bool isFixed;
};