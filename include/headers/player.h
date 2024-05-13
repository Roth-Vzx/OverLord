#pragma once
#include <headers/mediaFiles.h>

class Player
{
    public:
        //Constructor y Destructor
        Player(int scrnWidth, int scrnHeight );
        ~Player();

        //Getters y Setters
            //Texturas
                void SetTexture(SDL_Texture* value);
                void SetframeIndexTexture(int frameIndex);
                void SetSourceTexture(SDL_Rect sourceTexture);
                void SetUpdateTexture(SDL_Rect updateTexture);

                SDL_Texture* GetTexture();
                int GetframeIndexTexture();
                SDL_Rect GetSourceTexture();
                SDL_Rect GetUpdateTexture();

            //state for pj 
                void SetJump(bool jump);
                void SetState(int state);
                void SetIsRight(bool isRight);

                void SetHeal(int state);
                void SetArmor(int state);

                int GetState();
                bool GetIsRight();
                bool GetJump();

                int GetHeal();
                int GetArmor();

        //Funciones
            //Acciones
            void PJattack();
            void PJump();

            //update.
            void PjUpdate();

            //Render.
            void PjRender(MediaFiles &media);

    private:
        //Texturas
        MediaFiles tmpMedia;
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
};