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

void MediaFiles::DrawPJ(SDL_Texture* PJtexture, SDL_Rect& source, SDL_Rect& destiny, const int& state, const bool& isRight, const bool& jump)
{
    if(state == -1) source.y = 0;//static
    if(state == 1)source.y = 44; //running
    if(jump == true) source.y = 308; //jump
    
    source.w = 69;
    source.h = 44;

    //Direccion.
    if (isRight == true) SDL_RenderCopyEx(renderer, PJtexture, &source, &destiny, 0, NULL, SDL_FLIP_NONE);
    else SDL_RenderCopyEx(renderer, PJtexture, &source, &destiny, 0, NULL,SDL_FLIP_HORIZONTAL);
    
    SDL_RenderPresent(renderer);
}