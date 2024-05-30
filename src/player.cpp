#include <headers/mediaFiles.h>
#include <headers/player.h>

//Constructor.
Player::Player()
{
    //texturas.
    int frameIndexTexture = 0;
    const SDL_Texture* Texture = nullptr;
    SDL_Rect sourceTextureRect;
    SDL_Rect updateTextureRect;

    updateTextureRect.x = 0;
    updateTextureRect.y = 0;
    updateTextureRect.w = 0;
    updateTextureRect.h = 0;

    sourceTextureRect.x = 0;
    sourceTextureRect.y = 0;
    sourceTextureRect.w = 0;
    sourceTextureRect.h = 0;

    //estados.
    frameIndexTexture = 0;
    limitY = 0;
    state = -1;
    jump = false;
    isRight = true;
    isFixed = false;

    //stats.
     heal = 0;
     armor = 0;
};

//Destructor.
Player::~Player(){};

//Setters y Getters
    //state for pj 
    void Player::SetState(int value){state = value;}
    void Player::SetLimitY(int value){limitY = value;}
    void Player::SetIsRight(bool value){isRight = value;}
    void Player::SetJump(bool value){jump = value;}
    void Player::SetIsFixed(bool value){isFixed = value;}

    int Player::GetState(){return state;}
    int Player::GetLimitY(){return limitY;}
    bool Player::GetIsRight(){return isRight;}
    bool Player::GetJump(){return jump;}
    bool* Player::GetIsFixed(){return &isFixed;}

    //texturas.
    void Player::SetTexture(SDL_Texture* value){Texture = value;}

    void Player::SetframeIndexTexture(int value){frameIndexTexture = value;}
    void Player::SetSource(SDL_Rect value){sourceTextureRect = value;}
    void Player::SetUpdate(SDL_Rect value){updateTextureRect = value;}

    SDL_Texture* Player::GetTexture(){return Texture;}
    int Player::GetframeIndexTexture(){return frameIndexTexture;}
    SDL_Rect* Player::GetSource(){return &sourceTextureRect;}
    SDL_Rect* Player::GetUpdate(){return &updateTextureRect;}

    std::pair<std::stack<int>,bool>* Player::GetAnimationHelper(){return &fixedAnimation;}

//Funciones
//Acciones
void Player::PJattack(){}
void Player::PJump(){}

//update.
void Player::PjUpdate(){
    frameIndexTexture = (int(((SDL_GetTicks() / 100) % 10)));
    sourceTextureRect.x = (frameIndexTexture % 6) * 69;
}
