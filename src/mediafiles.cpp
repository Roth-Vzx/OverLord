#include <headers/mediaFiles.h>
#include <headers/exception.h>

//SDL_Renderer* MediaFiles::renderer = nullptr;

MediaFiles::MediaFiles()
{ 
    screenWidth = 0;
    screenHeigth = 0;
    renderer = nullptr;
};

MediaFiles::~MediaFiles(){};

SDL_Renderer* MediaFiles::GetRenderer(){return renderer;}

void MediaFiles::SetRenderer(SDL_Renderer* value){renderer = value;}

void MediaFiles::SetScreenWidth(int value)
{
    screenWidth = Levels.GetDestinyBackground()->w = value;
    Levels.GetDestinyLand()->w = screenWidth / Levels.GetNumWidth();
}

void MediaFiles::SetScreenHeigth(int value)
{
    screenHeigth = Levels.GetDestinyBackground()->h = value;
    Levels.GetDestinyLand()->h = screenHeigth / Levels.GetNumHeigth();
}

Map* MediaFiles::GetLevels(){return &Levels;}

std::vector<SDL_Texture*>* MediaFiles::GetMapBackground(){return Levels.GetBackground();}

SDL_Texture* MediaFiles::GetLandTexture(){return Levels.GetTileset();}

#pragma region BasicLoadTextures

SDL_Texture* MediaFiles::CreateTexture(const char* path)
{
    SDL_Texture* temporalTexture;

    temporalTexture = IMG_LoadTexture(renderer,path);

    if(temporalTexture == nullptr) throw SDL_Exception(SDL_GetError()); 

    return temporalTexture;
}

void MediaFiles::LoadTextures(const std::vector<char*>& paths, std::vector<SDL_Texture*>& textures)
{
    if(paths.size()==0) std::cout<<"Load Textures:\nThere is no Paths"<<std::endl;
    else
    {
        for(int i=0; i<paths.size(); ++i)
        {
            textures.push_back(CreateTexture(paths[i]));         
        }
    }
}

void MediaFiles::CopyFullTextures(std::vector<SDL_Texture*> textures)
{
    for(SDL_Texture* texture : textures)
    {
        SDL_RenderCopy(renderer, texture, NULL, NULL);
    }
}

void MediaFiles::SetBackground(const std::vector<char*>& paths)
{
    if(paths.size()==0) std::cout<<"Load Textures:\nThere is no Paths"<<std::endl;
    else
    {
        for(int i=0; i<paths.size(); ++i)
        {
            Levels.GetBackground()->push_back(CreateTexture(paths[i]));      
        }
    }
}

#pragma endregion

/*void MediaFiles::DrawPJ(SDL_Texture* PJtexture, SDL_Rect& source, SDL_Rect& destiny, int& state, const bool& IsRight, bool& IsJumping, bool& IsFixed)
{
    if(IsJumping == true)
    {
        //Si salta comenzara a subir hasta un cierto limite (LimitY/2)
        //Cuando llegue a ese limite, jump sera falso

        source.y = 308; //jump

        if(destiny.y >= LimitY/2) destiny.y = destiny.y - 6;
        else IsJumping = false;
    }
    else if(IsJumping == false)
    {
        if(destiny.y < LimitY)
        {
            //Si el personaje acaba de saltar
            //Con este if se asegura que vuelva a bajar

            source.y = 351; //jump
            source.x = 0;
            destiny.y = destiny.y + 6;
        }
        else if(IsFixed == true) 
        {
            switch (state)
            {
                case 2:
                    source.y = source.h * 2;
                    DoFixedAnimation(3,9,6,3,source,IsFixed);
                break;

                case 3:
                    source.y = source.h * 12;
                    DoFixedAnimation(6,7,6,3,source,IsFixed);
                break;
            }
            if(uniqueStackAnimation.first.size() == 0 && state > 1) state = -1;
        }
        else if(state == -1) source.y = 0; //static
        else if(state == 1) source.y = 44; //running
    }
     
    //Direccion.
    if (IsRight == true) SDL_RenderCopyEx(renderer, PJtexture, &source, &destiny, 0, NULL, SDL_FLIP_NONE);
    else SDL_RenderCopyEx(renderer, PJtexture, &source, &destiny, 0, NULL,SDL_FLIP_HORIZONTAL);
}*/

void MediaFiles::DrawPJ(Player& PJ)
{
    if(PJ.GetJump() == true)
    {
        //Si salta comenzara a subir hasta un cierto limite (LimitY/2)
        //Cuando llegue a ese limite, jump sera falso
 
        PJ.GetSource()->y = 308; //jump

        if(PJ.GetUpdate()->y >= PJ.GetLimitY()/2) PJ.GetUpdate()->y -= 6;
        else PJ.SetJump(false);
    }
    else if(PJ.GetJump() == false)
    {
        if(PJ.GetUpdate()->y < PJ.GetLimitY())
        {
            //Si el personaje acaba de saltar
            //Con este if se asegura que vuelva a bajar

            PJ.GetSource()->y = 351; //jump
            PJ.GetSource()->x = 0;
            PJ.GetUpdate()->y += 6;
        }
        else if(*(PJ.GetIsFixed()) == true) 
        {
            switch (PJ.GetState())
            {
                case 2:
                    PJ.GetSource()->y = PJ.GetSource()->h * 2;
                    DoFixedAnimation(3,9,6,3,*PJ.GetSource(),*PJ.GetIsFixed(),*PJ.GetAnimationHelper());
                break;

                case 3:
                    PJ.GetSource()->y = PJ.GetSource()->h * 12;
                    DoFixedAnimation(6,7,6,3,*PJ.GetSource(),*PJ.GetIsFixed(),*PJ.GetAnimationHelper());
                break;
            }
            if(PJ.GetAnimationHelper()->first.size() == 0 && PJ.GetState() > 1) PJ.SetState(-1);
        }
        else if(PJ.GetState() == -1) PJ.GetSource()->y = 0; //static
        else if(PJ.GetState() == 1) PJ.GetSource()->y = 44; //running
    }
     
    //Direccion.
    if (PJ.GetIsRight() == true) SDL_RenderCopyEx(renderer, PJ.GetTexture(), PJ.GetSource(), PJ.GetUpdate(), 0, NULL, SDL_FLIP_NONE);
    else SDL_RenderCopyEx(renderer, PJ.GetTexture(), PJ.GetSource(), PJ.GetUpdate(), 0, NULL,SDL_FLIP_HORIZONTAL);
}

void MediaFiles::DrawEnemy(Player& PJ)
{
    if(PJ.GetJump() == true)
    {
        //Si salta comenzara a subir hasta un cierto limite (LimitY/2)
        //Cuando llegue a ese limite, jump sera falso

        PJ.GetSource()->y = 308; //jump

        if(PJ.GetUpdate()->y >= PJ.GetLimitY()/2) PJ.GetUpdate()->y -= 6;
        else PJ.SetJump(false);
    }
    else if(PJ.GetJump() == false)
    {
        if(PJ.GetUpdate()->y < PJ.GetLimitY())
        {
            //Si el personaje acaba de saltar
            //Con este if se asegura que vuelva a bajar

            PJ.GetSource()->y = 351; //jump
            PJ.GetSource()->x = 0;
            PJ.GetUpdate()->y += 6;
        }
        else if(*(PJ.GetIsFixed()) == true) 
        {
            switch (PJ.GetState())
            {
                case 2:
                    PJ.GetSource()->y = PJ.GetSource()->h * 2;
                    DoFixedAnimation(1,5,8,7,*(PJ.GetSource()),*(PJ.GetIsFixed()),*PJ.GetAnimationHelper());
                break;

                case 3:
                    PJ.GetSource()->y = PJ.GetSource()->h * 2;
                    DoFixedAnimation(1,9,8,4,*(PJ.GetSource()),*(PJ.GetIsFixed()),*PJ.GetAnimationHelper());
                break;
            }
            if(PJ.GetAnimationHelper()->first.size() == 0 && PJ.GetState() > 1) PJ.SetState(1);
        }
        else if(PJ.GetState() == -1) PJ.GetSource()->y = 0; //static
        else if(PJ.GetState() == 1) PJ.GetSource()->y = PJ.GetSource()->h; //running
    }
     
    //Direccion.
    if (PJ.GetIsRight() == false) SDL_RenderCopyEx(renderer, PJ.GetTexture(), PJ.GetSource(), PJ.GetUpdate(), 0, NULL, SDL_FLIP_NONE);
    else SDL_RenderCopyEx(renderer, PJ.GetTexture(), PJ.GetSource(), PJ.GetUpdate(), 0, NULL,SDL_FLIP_HORIZONTAL);
}

void MediaFiles::DoFixedAnimation(const int& start, const int& numFrames, const int& framesPerRow, const int& duration, SDL_Rect& source, bool& IsFixed, std::pair<std::stack<int>,bool>& uniqueStackAnimation)
{
    source.y = source.y + ((uniqueStackAnimation.first.size()/duration + (start - 1)) / framesPerRow) * source.h;

    if(uniqueStackAnimation.second == true)
    {
        source.x = uniqueStackAnimation.first.top();
        uniqueStackAnimation.first.pop();

        if(uniqueStackAnimation.first.empty()) 
        {
            uniqueStackAnimation.second = false;
            IsFixed = false;
        }
    }
    else
    {
        int _sourceX = ((uniqueStackAnimation.first.size()/duration % framesPerRow) + (start - 1)) * source.w;

        if(uniqueStackAnimation.first.size()/duration >= framesPerRow - (start - 1))
        { 
            _sourceX = ((uniqueStackAnimation.first.size()/duration - (framesPerRow - (start - 1))) % framesPerRow) * source.w;
        }

        source.x = _sourceX;
        uniqueStackAnimation.first.push(source.x);

        if(numFrames * duration == uniqueStackAnimation.first.size())
        {
            uniqueStackAnimation.second = true;
            for(int i = 0; i < duration; ++i) uniqueStackAnimation.first.pop();
        } 
    }
}

int MediaFiles::ApplyMovement(const int& movement)
{
    if(movement<0) //PJ hacia la derecha
    {
        return screenWidth;
    }
    else if(movement>0) //PJ hacia la izquierda
    {
        return -screenWidth;
    }
    return movement;
}

void MediaFiles::DrawDoubleFrame(SDL_Texture* texture, SDL_Rect& destiny, const int& movement)
{
    destiny.x += movement;
    SDL_RenderCopy(renderer, texture, NULL, &destiny); 
    if(destiny.x != 0)
    {
        destiny.x += ApplyMovement(destiny.x);
        SDL_RenderCopy(renderer, texture, NULL, &destiny);
        destiny.x += ApplyMovement(destiny.x);
        if(destiny.x <= -screenWidth || destiny.x >= screenWidth) destiny.x = 0;
    }
}

void MediaFiles::DrawDoubleFrame(SDL_Texture* texture, SDL_Rect& destiny, int& movement)
{
    destiny.x = movement;
    SDL_RenderCopy(renderer, texture, NULL, &destiny); 
    if(destiny.x != 0)
    {
        destiny.x += ApplyMovement(destiny.x);
        SDL_RenderCopy(renderer, texture, NULL, &destiny);
        destiny.x += ApplyMovement(destiny.x);
    }
}

void MediaFiles::DrawDoubleFrame(SDL_Texture* texture, SDL_Rect& source, SDL_Rect& destiny, int& movement)
{
    destiny.x += movement;
    SDL_RenderCopy(renderer, texture, &source, &destiny); 
    if(destiny.x != 0)
    {
        destiny.x += ApplyMovement(destiny.x);
        SDL_RenderCopy(renderer, texture, &source, &destiny);
        destiny.x += ApplyMovement(destiny.x);
    }
}

void MediaFiles::DrawBackground(int& movement)
{
    for(SDL_Texture* texture : *GetMapBackground()) DrawDoubleFrame(texture,*Levels.GetDestinyBackground(),movement);
}

void MediaFiles::DrawMap(int& movement)
{
    int type;

    for(int i = 0; i < Levels.GetNumHeigth(); ++i){
        for (int j = 0; j < Levels.GetNumWidth(); ++j)
        {
            type = Levels.GetPosMap(i,j);

            Levels.GetDestinyLand()->x = j * Levels.GetDestinyLand()->w;
            Levels.GetDestinyLand()->y = i * Levels.GetDestinyLand()->h;

            switch (type)
            {
            //Dirt center
                case 1:
                    Levels.GetSourceLand()->x = 10;
                break;

            //Dirt Left
                case 2:
                    Levels.GetSourceLand()->x = 0;
                break;

            //Dirt Right.
                case 3:
                    Levels.GetSourceLand()->x = 80;
                break;
            }
            if(type != 0)
            {
                DrawDoubleFrame(Levels.GetTileset(),*Levels.GetSourceLand(),*Levels.GetDestinyLand(),movement);
            }
        }
    }
}

void MediaFiles::DrawLevel(Player& PJ, Player& enemy, int& movement)
{
    if(movement >= screenWidth || movement <= -screenWidth) movement = 0;
    DrawBackground(movement);
    DrawMap(movement);
    DrawEnemy(enemy);
    DrawPJ(PJ);
}
