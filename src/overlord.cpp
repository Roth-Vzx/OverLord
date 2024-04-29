#include <headers/overlord.h>

OverLord::OverLord()
{
    gameName = SDL_strdup("OverLord");
    gameState = true;
    window = nullptr;
    screenSurface = nullptr;
    backGround1 = nullptr;
    backGround2 = nullptr;
    renderer = nullptr;
    screenHeigth = 768;
    screenWidth = 1024;
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
    //SDL_Init(SDL_INIT_EVERYTHING);
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout<<"SDL could not initialize! SDL_Error: "<<SDL_GetError()<<std::endl;
    }
    else
    {
        window = SDL_CreateWindow(name, posX, posY, width, height, flags);
        if( window == NULL )
        {
            std::cout<<"Window could not be created! SDL_Error: "<<SDL_GetError()<<std::endl;
        }
        else
        {
            screenSurface = SDL_GetWindowSurface(window);
            //SDL_FillRect(screenSurface,NULL,SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            //SDL_UpdateWindowSurface(window);
            //HACK LINE PARA DEJAR ABIERTO LA VENTANA  //SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
            LoadMedia();      
        }
    }
    renderer = SDL_CreateRenderer(window,-1,0);
    std::cout<<"FINISH INIT"<<std::endl;
}

void OverLord::LoadMedia()
{
    /*SDL_Surface* optimized = nullptr;
    char* pathBackground = SDL_strdup("resources/img/background_layer_1.bmp");
    optimized = SDL_LoadBMP(pathBackground);
    if(optimized == nullptr)
    {
        std::cout<<"Unable to load image\nPath: "<<pathBackground<<std::endl<<"Error: "<<SDL_GetError()<<std::endl;
    }
    else
    {
        backGround = SDL_ConvertSurface(optimized,screenSurface->format,0);
        if(backGround == nullptr)
        {
            std::cout<<"Unable to optimize image SDL Error: "<<SDL_GetError()<<std::endl;
        }
        else
        {
            SDL_Rect stretchRect;
            stretchRect.x = 0;
            stretchRect.y = 0;
            stretchRect.w = screenWidth;
            stretchRect.h = screenHeigth;
            SDL_BlitScaled(backGround, NULL, screenSurface, &stretchRect);
            //SDL_BlitSurface(backGround, NULL, screenSurface, NULL);
            SDL_UpdateWindowSurface(window);
            SDL_FreeSurface(optimized);
        }
    }*/
    
    char* pathBackground = SDL_strdup("resources/img/background_layer_1.bmp");
    backGround1 = SDL_LoadBMP(pathBackground);
    if(backGround1 == nullptr)
    {
        std::cout<<"Unable to load image\nPath: "<<pathBackground<<std::endl<<"Error: "<<SDL_GetError()<<std::endl;
    }
    else
    {
        char* pathBackground2 = SDL_strdup("resources/img/background_layer_3.bmp");
        backGround2 = SDL_LoadBMP(pathBackground2);
        if(backGround2 == nullptr)
        {
            std::cout<<"Unable to load image\nPath: "<<pathBackground2<<std::endl<<"Error: "<<SDL_GetError()<<std::endl;
        }
        else
        {
            SDL_Rect stretchRect;
            stretchRect.x = 0;
            stretchRect.y = 0;
            stretchRect.w = screenWidth;
            stretchRect.h = screenHeigth;
            SDL_BlitScaled(backGround1, NULL, screenSurface, &stretchRect);
            SDL_BlitScaled(backGround2, NULL, screenSurface, &stretchRect);
            SDL_UpdateWindowSurface(window);
        }
    }
}

void OverLord::BackgroundLoop(int& x, int& y)
{
    SDL_Rect stretchRect;
    stretchRect.x = x;
    stretchRect.y = y;
    stretchRect.w = screenWidth;
    stretchRect.h = screenHeigth;
    SDL_BlitScaled(backGround1, NULL, screenSurface, &stretchRect);
    SDL_BlitScaled(backGround2, NULL, screenSurface, &stretchRect);
    SDL_UpdateWindowSurface(window);
}

void OverLord::GameLoop()
{
    int x = 0;
    int y = 0;
    while(gameState == true)
    {
        //++x;
        HandleEvents();
        //BackgroundLoop(x,y);
    } 
    std::cout<<"BREAK GAMELOOP"<<std::endl;
}

void OverLord::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT:
            gameState = false;
            std::cout<<"GAMESTATE FALSE"<<std::endl;
            Close();
            break;
    }
}

void OverLord::Close()
{
    SDL_FreeSurface(backGround1);
    SDL_FreeSurface(backGround2);
    backGround1 = nullptr;
    backGround2 = nullptr;
    SDL_DestroyWindow(window);
    SDL_Quit();
}