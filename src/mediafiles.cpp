#include <headers/mediaFiles.h>
#include <headers/exception.h>

//SDL_Renderer* MediaFiles::renderer = nullptr;

MediaFiles::MediaFiles()
{ 
    LimitY = 0;
    screenWidth = 0;
    lastFrames.second = false;
    renderer = nullptr;
};

MediaFiles::~MediaFiles(){};

SDL_Renderer* MediaFiles::GetRenderer(){return renderer;}

void MediaFiles::SetRenderer(SDL_Renderer* value){renderer = value;}

void MediaFiles::SetLimitY(int value){LimitY = value;}

int MediaFiles::GetLimitY(){return LimitY;}

void MediaFiles::SetScreenWidth(int value){screenWidth = value;}

Map* MediaFiles::GetLevels(){return &Levels;}

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

void MediaFiles::DrawPJ(SDL_Texture* PJtexture, SDL_Rect& source, SDL_Rect& destiny, int& state, const bool& IsRight, bool& IsJumping, bool& IsFixed)
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
            if(lastFrames.first.size() == 0 && state > 1) state = -1;
        }
        else if(state == -1) source.y = 0; //static
        else if(state == 1) source.y = 44; //running
    }
     
    //Direccion.
    if (IsRight == true) SDL_RenderCopyEx(renderer, PJtexture, &source, &destiny, 0, NULL, SDL_FLIP_NONE);
    else SDL_RenderCopyEx(renderer, PJtexture, &source, &destiny, 0, NULL,SDL_FLIP_HORIZONTAL);
}

void MediaFiles::DrawPJ(Player& PJ)
{
    if(PJ.GetJump() == true)
    {
        //Si salta comenzara a subir hasta un cierto limite (LimitY/2)
        //Cuando llegue a ese limite, jump sera falso

        PJ.SetSourceY(308); //jump

        if(PJ.GetUpdateTexture()->y >= LimitY/2) PJ.SetUpdateY(PJ.GetUpdateTexture()->y - 6);
        else PJ.SetJump(false);
    }
    else if(PJ.GetJump() == false)
    {
        if(PJ.GetUpdateTexture()->y < LimitY)
        {
            //Si el personaje acaba de saltar
            //Con este if se asegura que vuelva a bajar

            PJ.SetSourceY(351);  //jump
            PJ.SetSourceX(0);
            PJ.SetUpdateY((PJ.GetUpdateTexture())->y + 6);
        }
        else if(*PJ.GetIsFixed() == true) 
        {
            switch (PJ.GetState())
            {
                case 2:
                    PJ.SetSourceY(PJ.GetSourceTexture()->h * 2);
                    DoFixedAnimation(3,9,6,3,*(PJ.GetSourceTexture()),*(PJ.GetIsFixed()));
                break;

                case 3:
                    PJ.SetSourceY(PJ.GetSourceTexture()->h * 12);
                    DoFixedAnimation(6,7,6,3,*(PJ.GetSourceTexture()),*(PJ.GetIsFixed()));
                break;
            }
            if(lastFrames.first.size() == 0 && PJ.GetState() > 1) PJ.SetState(-1);
        }
        else if(PJ.GetState() == -1) PJ.SetSourceY(0); //static
        else if(PJ.GetState() == 1) PJ.SetSourceY(44); //running
    }
     
    //Direccion.
    if (PJ.GetIsRight() == true) SDL_RenderCopyEx(renderer, PJ.GetTexture(), PJ.GetSourceTexture(), PJ.GetUpdateTexture(), 0, NULL, SDL_FLIP_NONE);
    else SDL_RenderCopyEx(renderer, PJ.GetTexture(), PJ.GetSourceTexture(), PJ.GetUpdateTexture(), 0, NULL,SDL_FLIP_HORIZONTAL);
}

void MediaFiles::DoFixedAnimation(const int& start, const int& numFrames, const int& framesPerRow, const int& duration, SDL_Rect& source, bool& IsFixed)
{
    source.y = source.y + ((lastFrames.first.size()/duration + (start - 1)) / framesPerRow) * source.h;

    if(lastFrames.second == true)
    {
        source.x = lastFrames.first.top();
        lastFrames.first.pop();

        if(lastFrames.first.empty()) 
        {
            lastFrames.second = false;
            IsFixed = false;
        }
    }
    else
    {
        int _sourceX = ((lastFrames.first.size()/duration % framesPerRow) + (start - 1)) * source.w;

        if(lastFrames.first.size()/duration >= framesPerRow - (start - 1))
        { 
            _sourceX = ((lastFrames.first.size()/duration - (framesPerRow - (start - 1))) % framesPerRow) * source.w;
        }

        source.x = _sourceX;
        lastFrames.first.push(source.x);

        if(numFrames * duration == lastFrames.first.size())
        {
            lastFrames.second = true;
            for(int i = 0; i < duration; ++i) lastFrames.first.pop();
        } 
    }
}

void MediaFiles::DrawMap()
{
    int type;

    for(int row = 0; row< 22; ++row){
        for (int column = 0; column < 70; ++column)
        {
            type = Levels.GetPosMap(row,column);

            Levels.SetDestinyX(column * 32);
            Levels.SetDestinyY(row * 32);

            switch (type)
            {
            //Dirt left
                case 1:
                //std::cout<<"Case1Dirt"<<std::endl;
                    Levels.SetSourceX(48);
                    //std::cout<<Levels.GetDestiny()->y<<std::endl;
                    SDL_RenderCopy(renderer, Levels.GetTileset(), Levels.GetSource(), Levels.GetDestiny());
                break;

            //Dirt Center
                case 2:
                //std::cout<<"Case2Dirt"<<std::endl;
                    Levels.SetSourceX(0);
                    Levels.SetSourceY(0);
                    SDL_RenderCopy(renderer, Levels.GetTileset(), Levels.GetSource(), Levels.GetDestiny());
                break;

            //Dirt Right.
                case 3:
                //std::cout<<"Case3Dirt"<<std::endl;
                    Levels.SetSourceX(72);
                    SDL_RenderCopy(renderer, Levels.GetTileset(), Levels.GetSource(), Levels.GetDestiny());
                break;
            }
        }
    }
}
