#include <headers/mediaFiles.h>
#include <headers/exception.h>

MediaFiles::MediaFiles()
{
    renderer = nullptr;
    LimitY = 0;
    screenWidth = 0;
};

MediaFiles::~MediaFiles(){};

SDL_Renderer* MediaFiles::GetRenderer(){return renderer;}

void MediaFiles::SetRenderer(SDL_Renderer* value){renderer = value;}

void MediaFiles::SetLimitY(int value){LimitY = value;}

int MediaFiles::GetLimitY(){return LimitY;}

void MediaFiles::SetScreenWidth(int value){screenWidth = value;}

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

void MediaFiles::DrawPJ(SDL_Texture* PJtexture, SDL_Rect& source, SDL_Rect& destiny, const int& state, const bool& isRight, bool& jump)
{
    if(jump == true)
    {
        //Si salta comenzara a subir hasta un cierto limite (LimitY/2)
        //Cuando llegue a ese limite, jump sera falso

        source.y = 308; //jump

        if(destiny.y >= LimitY/2) destiny.y = destiny.y - 6;
        else jump = false;
    }
    else
    {
        if(destiny.y < LimitY && jump == false)
        {
            //Si el personaje acaba de saltar
            //Con este if se asegura que vuelva a bajar

            source.y = 308; //jump
            destiny.y = destiny.y + 6;
        } 
        else if(state == -1) source.y = 0; //static
        else if(state == 1) source.y = 44; //running
    }
     
    //source.w = 69;
    //source.h = 44;

    //Direccion.
    if (isRight == true) SDL_RenderCopyEx(renderer, PJtexture, &source, &destiny, 0, NULL, SDL_FLIP_NONE);
    else SDL_RenderCopyEx(renderer, PJtexture, &source, &destiny, 0, NULL,SDL_FLIP_HORIZONTAL);
    
    //SDL_RenderPresent(renderer);
}