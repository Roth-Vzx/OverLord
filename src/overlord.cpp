#include <headers/overlord.h>
#include <headers/exception.h>

SDL_Renderer*OverLord::renderer = nullptr;
Map* map; 

OverLord::OverLord()
{
    gameName = SDL_strdup("OverLord");
    gameState = true;
    frameIndexPlayer = 0;
    move = 0;
    state = -1;
    IsJumping = false;
    IsRight = true;
    IsFixed = false;
    window = nullptr;
    screenHeigth = 720;
    screenWidth = 1280;

    renderer = nullptr;
    background_init = nullptr;

    destinationBackground.h = screenHeigth;
    destinationBackground.w = screenWidth;
    destinationBackground.y = 0;

    destinationMirrorBackground.h = screenHeigth;
    destinationMirrorBackground.w = screenWidth;
    destinationMirrorBackground.y = 0;

    updateWarriorRect.x = screenWidth/2 - screenWidth/25;
    updateWarriorRect.y = screenHeigth/2 + screenHeigth/5;
    updateWarriorRect.w = 180;
    updateWarriorRect.h = 180;

    sourceWarriorRect.x = 0;
    sourceWarriorRect.y = 0;
    sourceWarriorRect.w = 69;
    sourceWarriorRect.h = 44;

    media.SetLimitY(updateWarriorRect.y);
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

        media.SetRenderer(SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED));
        if(media.GetRenderer() == nullptr) throw SDL_Exception(SDL_GetError());

        if(SDL_SetRenderDrawColor(media.GetRenderer(), 200, 200, 200, 200)<0) throw SDL_Exception(SDL_GetError());

        int imgFlags = IMG_INIT_PNG;
        if(!(IMG_Init(imgFlags)&imgFlags)) throw SDL_Exception(SDL_GetError());

        background_init = media.CreateTexture("resources/img/Init.png");
        PJ = media.CreateTexture("resources/img/character/warrior.png");

        std::vector<char*> paths;
        paths.push_back(SDL_strdup("resources/img/background_layer_1.bmp"));
        paths.push_back(SDL_strdup("resources/img/background_layer_3.bmp"));
        media.LoadTextures(paths,mainBackground);

        map = new Map();

        std::cout<<"FINISH INIT"<<std::endl;
    }
    catch(const SDL_Exception& exception)
    {
        std::cout<<"An Error has ocurred: "<<exception.message<<std::endl;
        gameState = false;
        Close();
    }

   
}

void OverLord::GameLoop()
{
    MenuInit();
    while(true)
    {
        double start = SDL_GetTicks();

        HandleEvents(); if(gameState==false) break;
        Update();
        Render();

        const int msPerframe = 16;
        double end = SDL_GetTicks();
        auto delay = start + msPerframe - end;
        if(delay > 0) SDL_Delay(delay);
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
                Close();
                return;
            break;

            //Al presionar la tecla
            case SDL_KEYDOWN:
            if(IsFixed == false)
            {
                switch (event.key.keysym.sym){
                    case SDLK_a:
                        state = 1; //running
                        IsRight = false;
                        std::cout << state << std::endl;
                    break;

                    case SDLK_d:
                        state = 1; //running
                        IsRight = true; 
                        std::cout << state << std::endl;
                    break;

                    case SDLK_w:
                        if(updateWarriorRect.y == media.GetLimitY()) //LimitY = Piso
                        {
                            //Si salta, este evento no se volvera a leer hasta que:
                            //1) La persona deje de presionar el boton
                            //2) el personaje alcance su altura maxima de salto y vuelva a bajar
                            IsJumping = true; // jump
                            std::cout << "Jump TRUE" << std::endl;
                        } 
                    break;

                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:

                if(IsJumping == false)
                {
                    switch (event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                        state = 2; //swing
                        IsFixed = true; 
                        break;

                        case SDL_BUTTON_RIGHT:
                        state = 3; //swing 2
                        IsFixed = true; 
                    }
                } 
                break;
            
            //Al soltar la tecla
            case SDL_KEYUP:
            if(IsFixed == false)
            {
                switch (event.key.keysym.sym){
                    case SDLK_a:
                    case SDLK_d:
                        state = -1;
                        std::cout << state << std::endl;
                    break;

                    case SDLK_w:
                        IsJumping = false;
                        std::cout << "Jump FALSE" << std::endl;
                    break;
                }
            }
            break;
        }
    }
}

void OverLord::Update(){
    //Movimiento del personaje.

        if(state == -1); //estatico.
        else if(IsRight == false)
        {
            //izquierda.
            if(IsJumping == true) move += 8;
            else
            {
                if(state == 2) move += 5;
                else if(state == 3) move += 2;
                else move += 8;
            }
            
        } 
        else if(IsRight == true)
        {
            //derecha.
            if(IsJumping == true) move -= 8;
            else
            {
                if(state == 2) move -= 5;
                else if(state == 3) move -= 2;
                else move -= 8;
            }
        } 
        
    //Animaciones. 
        //Player
        
        frameIndexPlayer = int(((SDL_GetTicks() / 100) % 12));
        sourceWarriorRect.x = (frameIndexPlayer % 6) * 69;        
}

void OverLord::Render(){
    SDL_RenderClear(media.GetRenderer());
    BackgroundLoop();
    map->Draw();
    media.DrawPJ(PJ,sourceWarriorRect,updateWarriorRect,state,IsRight,IsJumping,IsFixed);
    SDL_RenderPresent(media.GetRenderer());
}

void OverLord::BackgroundLoop()
{
    destinationBackground.x = move;

    if(move<0) //PJ hacia la derecha
    {
        destinationMirrorBackground.x = screenWidth+move;
    }
    else if(move>0) //PJ hacia la izquierda
    {
        destinationMirrorBackground.x = -screenWidth+move;
    }

    if(move >= screenWidth || move <= -screenWidth) move = 0;

    for(SDL_Texture* texture : mainBackground)
    {
        SDL_RenderCopy(media.GetRenderer(), texture, NULL, &destinationBackground);
        SDL_RenderCopy(media.GetRenderer(), texture, NULL, &destinationMirrorBackground);
    }
}

void OverLord::MenuInit(){

    //Firts Frame of Background

    SDL_RenderCopy(media.GetRenderer(), background_init, NULL, NULL);
    SDL_RenderPresent(media.GetRenderer());

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

                SDL_RenderClear(media.GetRenderer());
                media.CopyFullTextures(mainBackground);
                SDL_RenderPresent(media.GetRenderer());  

                wait = false;
                break;
        
            case SDL_QUIT:
                wait = false;
                gameState = false;
                Close();
                break;
        } 
    }
    ///////////////////////////
}

void OverLord::Close()
{
    std::cout<<"GameState=False\nCall:Close()\n";

    map->~Map();

    if(PJ != nullptr)
    {
        PJ = nullptr;
        SDL_DestroyTexture(PJ);
        std::cout<<"Destroy PJ"<<std::endl;
    }

    if(background_init != nullptr)
    {
        background_init = nullptr;
        SDL_DestroyTexture(background_init);
        std::cout<<"Destroy Init Background"<<std::endl;
    }

    while(!mainBackground.empty())
    {
        for(auto iterator = mainBackground.rbegin(); iterator != mainBackground.rend(); ++iterator)
        {
            *iterator = nullptr;
            SDL_DestroyTexture(*iterator);
            mainBackground.pop_back();
        }
        std::cout<<"Destroy Main Background"<<std::endl;
    }

    if(media.GetRenderer() != nullptr)
    {
        media.SetRenderer(nullptr);
        SDL_DestroyRenderer(media.GetRenderer());
        std::cout<<"Destroy Renderer"<<std::endl;
    }

    if(window != nullptr)
    {
        window = nullptr;
        SDL_DestroyWindow(window);
        std::cout<<"Destroy Window"<<std::endl;
    }
    
    IMG_Quit();
    std::cout<<"IMG Quit"<<std::endl;
    SDL_Quit();
    std::cout<<"SDL Quit"<<std::endl;
}

