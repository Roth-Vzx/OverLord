#include <headers/mediaFiles.h>
#include <headers/player.h>

//Constructor.
Player::Player(int screenWidth, int screenHeigth)
{
    //texturas.
    int frameIndexTexture = 0;
    const SDL_Texture* Texture = nullptr;
    SDL_Rect sourceTextureRect;
    SDL_Rect updateTextureRect;

    updateTextureRect.x = screenWidth/2 - screenWidth/25;
    updateTextureRect.y = screenHeigth/2 + screenHeigth/5;
    updateTextureRect.w = 180;
    updateTextureRect.h = 190;

    sourceTextureRect.x = 0;
    sourceTextureRect.y = 0;
    sourceTextureRect.w = 69;
    sourceTextureRect.h = 44;

    //estados.
    frameIndexTexture = 0;
    state = -1;
    jump = false;
    isRight = true;

    //stats.
     heal = 2;
     armor = 0;
};

//Destructor.
Player::~Player(){};

//Setters y Getters
    //state for pj 
    void Player::SetState(int value){state = value;}
    void Player::SetIsRight(bool value){jump = value;}
    void Player::SetJump(bool value){isRight = value;}

    int Player::GetState(){return state;}
    bool Player::GetIsRight(){return isRight;}
    bool Player::GetJump(){return jump;}

    //texturas.
    void Player::SetTexture(SDL_Texture* value){Texture = value;}

    void Player::SetframeIndexTexture(int value){frameIndexTexture = value;}
    void Player::SetSourceTexture(SDL_Rect value){sourceTextureRect = value;}
    void Player::SetUpdateTexture(SDL_Rect value){updateTextureRect = value;}

    SDL_Texture* Player::GetTexture(){return Texture;}
    int Player::GetframeIndexTexture(){return frameIndexTexture;}
    SDL_Rect Player::GetSourceTexture(){return sourceTextureRect;}
    SDL_Rect Player::GetUpdateTexture(){return updateTextureRect;}

//Funciones
//Acciones
void Player::PJattack(){}
void Player::PJump(){}

//update.
void Player::PjUpdate(){
    frameIndexTexture = (int(((SDL_GetTicks() / 100) % 10)));
    sourceTextureRect.x = (frameIndexTexture % 6) * 69;
}

//Render.
void Player::PjRender(MediaFiles &media ){
   // media.DrawPJ(Texture,sourceTextureRect,updateTextureRect,state,isRight,jump);
}
