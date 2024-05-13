#include <headers/mediaFiles.h>
#include <headers/exception.h>
#include <headers/overlord.h>

MediaFiles::MediaFiles()
{
   
    LimitY = 0;
    screenWidth = 0;
    lastFrames.second = false;
};

MediaFiles::~MediaFiles(){};

SDL_Renderer* MediaFiles::GetRenderer(){return OverLord::renderer;}

void MediaFiles::SetRenderer(SDL_Renderer* value){OverLord::renderer = value;}

void MediaFiles::SetLimitY(int value){LimitY = value;}

int MediaFiles::GetLimitY(){return LimitY;}

void MediaFiles::SetScreenWidth(int value){screenWidth = value;}

SDL_Texture* MediaFiles::CreateTexture(const char* path)
{
    SDL_Texture* temporalTexture;

    temporalTexture = IMG_LoadTexture(OverLord::renderer,path);

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
        SDL_RenderCopy(OverLord::renderer, texture, NULL, NULL);
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
                    DoFixedAnimation(3,9,6,source,IsFixed);
                break;
            }
            if(lastFrames.first.size() == 0) state = -1;
        }
        else if(state == -1) source.y = 0; //static
        else if(state == 1) source.y = 44; //running
    }
     
    //Direccion.
    if (IsRight == true) SDL_RenderCopyEx(OverLord::renderer, PJtexture, &source, &destiny, 0, NULL, SDL_FLIP_NONE);
    else SDL_RenderCopyEx(OverLord::renderer, PJtexture, &source, &destiny, 0, NULL,SDL_FLIP_HORIZONTAL);
    
    //SDL_RenderPresent(renderer);
}

void MediaFiles::DoFixedAnimation(const int& start, const int& numFrames, const int& framesPerRow, SDL_Rect& source, bool& IsFixed)
{
    source.y = source.y + ((lastFrames.first.size() + 1) / framesPerRow) * source.h;
    if(lastFrames.second == true)
    {
        source.x = lastFrames.first.top();
        lastFrames.first.pop();
        std::cout<<"X: "<<source.x<<"   Y: "<<source.y<<std::endl;
        if(lastFrames.first.empty()) 
        {
            lastFrames.second = false;
            IsFixed = false;
        }
    }
    else
    {
        int _sourceX = ((lastFrames.first.size() % framesPerRow) + (start - 1)) * source.w;

        if(lastFrames.first.size() >= framesPerRow - (start - 1))
        { 
            _sourceX = ((lastFrames.first.size() - (framesPerRow - (start - 1))) % framesPerRow) * source.w;
        }

        source.x = _sourceX;
        lastFrames.first.push(source.x);
        std::cout<<"X: "<<source.x<<"   Y: "<<source.y<<std::endl;
        if(numFrames == lastFrames.first.size())
        {
            lastFrames.second = true;
            lastFrames.first.pop();
        } 
    }
}

void DrawMap(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest){
    SDL_RenderCopy(OverLord::renderer, tex, &src, &dest);
}
