#include <headers/overlord.h>
#include <headers/exception.h>

OverLord::OverLord()
{
    gameName = SDL_strdup("OverLord");
    gameState = true;

    window = nullptr;
    renderer = nullptr;
    screenHeigth = 768;
    screenWidth = 1024;

    background_init = nullptr;
    destinationBackground.h = screenHeigth;
    destinationBackground.w = screenWidth;
    destinationBackground.y = 0;

    destinationMirrorBackground.h = screenHeigth;
    destinationMirrorBackground.w = screenWidth;
    destinationMirrorBackground.y = 0;
};

OverLord::~OverLord(){};

void OverLord::Run()
{
    std::cout<<"RUN"<<std::endl;
    Init(gameName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeigth, SDL_WINDOW_SHOWN);
    GameLoop();
}

void OverLord::Init(const char* name, const int& posX, const int& posY, const int& width, const int& height, const uint32_t flags)
{
    try
    {
        if(SDL_Init(SDL_INIT_VIDEO)<0) throw SDL_Exception(SDL_GetError());

        window = SDL_CreateWindow(name,posX,posY,width,height,flags);
        if(window == nullptr) throw SDL_Exception(SDL_GetError());

        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        if(renderer == nullptr) throw SDL_Exception(SDL_GetError());

        //HACK LINE PARA DEJAR ABIERTO LA VENTANA  //SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
        if(SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200)<0) throw SDL_Exception(SDL_GetError());

        int imgFlags = IMG_INIT_PNG;
        if(!(IMG_Init(imgFlags)&imgFlags)) throw SDL_Exception(SDL_GetError());

        background_init = CreateTexture("resources/img/Init.png");

        std::vector<char*> paths;
        paths.push_back(SDL_strdup("resources/img/background_layer_1.bmp"));
        paths.push_back(SDL_strdup("resources/img/background_layer_3.bmp"));
        LoadTextures(paths,mainBackground);      
    
        std::cout<<"FINISH INIT"<<std::endl;
    }
    catch(const SDL_Exception& exception)
    {
        std::cout<<"An Error has ocurred: "<<exception.message<<std::endl;
        gameState = false;
        Close();
    }
}

SDL_Texture* OverLord::CreateTexture(const char* path)
{
    SDL_Texture* temporalTexture;

    temporalTexture = IMG_LoadTexture(renderer,path);

    if(temporalTexture == nullptr) throw SDL_Exception(SDL_GetError()); 

    return temporalTexture;
}

void OverLord::LoadTextures(const std::vector<char*>& paths, std::vector<SDL_Texture*>& textures)
{
    if(paths.size()==0) std::cout<<"Load Textures:\nThere is no Paths"<<std::endl;
    else
    {
        try
        {
            for(int i=0; i<paths.size(); ++i)
            {
                textures.push_back(CreateTexture(paths[i]));         
            }
        }
        catch(const SDL_Exception& exception)
        {
            std::cout<<"An Error has ocurred: "<<exception.message<<std::endl;
            gameState = false;
            Close();
        }
    }
}

void OverLord::BackgroundLoop(int& movement)
{
    ++movement;

    destinationBackground.x = movement;
    destinationMirrorBackground.x = -screenWidth+movement;

    if(movement == screenWidth) movement = 0;

    SDL_RenderClear(renderer);
    
    for(SDL_Texture* texture : mainBackground)
    {
        SDL_RenderCopy(renderer, texture, NULL, &destinationBackground);
        SDL_RenderCopy(renderer, texture, NULL, &destinationMirrorBackground);
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(20);
}
void OverLord::MenuInit(){

    //Firts Frame of Background

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background_init, NULL, NULL);
    SDL_RenderPresent(renderer);

    ///////////////////////////

    //Second Frame of Background

    SDL_Event event;
    bool wait = true;
    while (wait == true)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_KEYUP:
        case SDL_MOUSEBUTTONUP:
            SDL_RenderClear(renderer);
    
            for (auto texture : mainBackground)
            {
                SDL_RenderCopy(renderer, texture, NULL, NULL);
            }
            SDL_RenderPresent(renderer);  

            wait = false;
            break;
        
        case SDL_QUIT:
            wait = false;
            gameState = false;
            std::cout<<"GAMESTATE FALSE"<<std::endl;
            Close();
            break;
        } 
    }
    ///////////////////////////
}

void OverLord::GameLoop()
{
    MenuInit();

    int x = 0;

    while(gameState == true)
    {
        HandleEvents();

        BackgroundLoop(x);
    } 
    std::cout<<"BREAK GAMELOOP"<<std::endl;
}

void OverLord::HandleEvents()
{
    SDL_Event event;
    
    while(SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
            case SDL_QUIT:
                gameState = false;
                std::cout<<"GAMESTATE FALSE"<<std::endl;
                Close();
                break;
        }
    }

}

void OverLord::Close()
{
    if(background_init != nullptr)
    {
        background_init = nullptr;
        SDL_DestroyTexture(background_init);
    }

    while(!mainBackground.empty())
    {
        for(auto iterator = mainBackground.rbegin(); iterator != mainBackground.rend(); ++iterator)
        {
            *iterator = nullptr;
            SDL_DestroyTexture(*iterator);
            mainBackground.pop_back();
        }
    }

    if(renderer != nullptr)
    {
        renderer = nullptr;
        SDL_DestroyRenderer(renderer);
    }

    if(window != nullptr)
    {
        window = nullptr;
        SDL_DestroyWindow(window);
    }
    
    IMG_Quit();
    SDL_Quit();
}