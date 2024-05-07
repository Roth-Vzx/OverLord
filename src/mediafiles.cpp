#include <headers/mediaFiles.h>
#include <headers/exception.h>

MediaFiles::MediaFiles()
{
    renderer = nullptr;
};

MediaFiles::~MediaFiles(){};

SDL_Renderer* MediaFiles::GetRenderer(){return renderer;}

void MediaFiles::SetRenderer(SDL_Renderer* value){renderer = value;}

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

void MediaFiles::DrawPJ(SDL_Texture* PJtexture, SDL_Rect& source, SDL_Rect& destiny, const int& state)
{
    if(state == -1) //static
    {
        source.y = 0;
        source.w = 69;
        source.h = 44;
    }

    if(state == 0) //rigth
    {
        source.y = 44;
        source.w = 69;
        source.h = 44;
    }

    if(state == 1) //left
    {
        source.y = 44;
        source.w = 69;
        source.h = 44;
    }

    SDL_RenderCopy(renderer, PJtexture, &source, &destiny);
    
    SDL_RenderPresent(renderer);
}