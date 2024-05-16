#include <headers/overlord.h>
#include <headers/exception.h>

//SDL_Renderer* OverLord::renderer = nullptr;

OverLord::OverLord()
{
    gameName = SDL_strdup("OverLord");
    gameState = true;
    frameIndexPlayer = 0;
    move = 0;

    window = nullptr;
    sky = nullptr;
    cloud_Dark = nullptr;
    cloud_Light = nullptr;
    name_Init = nullptr;
    pressToStar = nullptr;

    screenHeigth = 720;
    screenWidth = 1280;

    destinationBackground.h = screenHeigth;
    destinationBackground.w = screenWidth;
    destinationBackground.y = 0;

    destinationMirrorBackground.h = screenHeigth;
    destinationMirrorBackground.w = screenWidth;
    destinationMirrorBackground.y = 0;

    motion_Sky.h = screenHeigth;
    motion_Sky.w = screenWidth;
    motion_Sky.x = 0;
    motion_Sky.y = 0; 

    motionMirror_sky.h = screenHeigth;
    motionMirror_sky.w = screenWidth;
    motionMirror_sky.x = -screenWidth;
    motionMirror_sky.y = 0;

    motion_CL.h = screenHeigth;
    motion_CL.w = screenWidth;
    motion_CL.x = 0;
    motion_CL.y = 0; 

    motionMirror_CL.h = screenHeigth;
    motionMirror_CL.w = screenWidth;
    motionMirror_CL.x = -screenWidth;
    motionMirror_CL.y = 0;

    motion_CD.h = screenHeigth;
    motion_CD.w = screenWidth;
    motion_CD.x = 0;
    motion_CD.y = 0; 

    motionMirror_CD.h = screenHeigth;
    motionMirror_CD.w = screenWidth;
    motionMirror_CD.x = screenWidth;
    motionMirror_CD.y = 0;

    mainPJ.SetUpdateX(screenWidth/2 - screenWidth/25);
    mainPJ.SetUpdateY(screenHeigth/2 + screenHeigth/5);
    mainPJ.GetUpdateTexture()->w = 180;
    mainPJ.GetUpdateTexture()->h = 180;

    mainPJ.GetSourceTexture()->w = 69;
    mainPJ.GetSourceTexture()->h = 44;

    mainPJ.SetLimitY(mainPJ.GetUpdateTexture()->y);

    enemy.SetUpdateX(screenWidth/2 + screenWidth/6);
    enemy.SetUpdateY(screenHeigth/2 + screenHeigth/10);
    enemy.GetUpdateTexture()->w = 240;
    enemy.GetUpdateTexture()->h = 240;

    enemy.GetSourceTexture()->w = 140;
    enemy.GetSourceTexture()->h = 93;

    enemy.SetState(1);
    enemy.SetLimitY(enemy.GetUpdateTexture()->y);

    location_Name.h = 300;
    location_Name.w = 890;
    location_Name.x = screenWidth/2 - screenWidth/3;
    location_Name.y = 60;

    location_PressToStar.h = 160;
    location_PressToStar.w = 800;
    location_PressToStar.x = screenWidth/2 - screenWidth/3.3;
    location_PressToStar.y = 400;
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

        sky = media.CreateTexture("resources/img/background_0.png");
        cloud_Light = media.CreateTexture("resources/img/background_1.png");
        cloud_Dark = media.CreateTexture("resources/img/background_2.png");
        name_Init = media.CreateTexture("resources/img/Name.png");
        pressToStar = media.CreateTexture("resources/img/PressToStar.png");

        mainPJ.SetTexture(media.CreateTexture("resources/img/character/warrior.png"));
        enemy.SetTexture(media.CreateTexture("resources/img/character/Bringer-of-Death.png"));

        (*media.GetLevels()).SetTileset(media.CreateTexture("resources/img/map_tileset.png"));

        std::vector<char*> paths;
        paths.push_back(SDL_strdup("resources/img/background_layer_1.bmp"));
        paths.push_back(SDL_strdup("resources/img/background_layer_3.bmp"));
        media.LoadTextures(paths,mainBackground);

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

            //Al presionar tecla en keyboard
            case SDL_KEYDOWN:
                if(*(mainPJ.GetIsFixed()) == false)
                {
                    switch (event.key.keysym.sym){
                        case SDLK_a:
                            mainPJ.SetState(1); //running
                            mainPJ.SetIsRight(false); //Left
                        break;

                        case SDLK_d:
                            mainPJ.SetState(1); //running
                            mainPJ.SetIsRight(true); //Right
                        break;

                        case SDLK_w:
                            if(mainPJ.GetUpdateTexture()->y == mainPJ.GetLimitY()) //LimitY = Piso
                            {
                                //Si salta, este evento no se volvera a leer hasta que:
                                //deje de presionar el boton o hasta que suba a su altura maxima y bajar
                                mainPJ.SetJump(true); // jump
                                std::cout << "Jump TRUE" << std::endl;
                            } 
                        break;
                    }
                }
            break;

            //Al presionar tecla en Mouse
            case SDL_MOUSEBUTTONDOWN:
                if(mainPJ.GetJump() == false && *(mainPJ.GetIsFixed()) == false)
                {
                    switch (event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            mainPJ.SetState(2); //swing
                            mainPJ.SetIsFixed(true);
                        break;

                        case SDL_BUTTON_RIGHT:
                            mainPJ.SetState(3); //swing 2
                            mainPJ.SetIsFixed(true); 
                        break;
                    }
                } 
            break;
            
            //Al soltar la tecla
            case SDL_KEYUP:
                if(*(mainPJ.GetIsFixed()) == false)
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_a:
                        case SDLK_d:
                            mainPJ.SetState(-1);
                            std::cout << mainPJ.GetState() << std::endl;
                        break;

                        case SDLK_w:
                            mainPJ.SetJump(false);
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

        if(mainPJ.GetState() == -1); //estatico.
        else if(mainPJ.GetIsRight() == false)
        {
            //izquierda.
            if(mainPJ.GetJump() == true)
            {
                move += 8;
                enemy.SetUpdateX(enemy.GetUpdateTexture()->x + 8);
            } 
            else
            {
                if(mainPJ.GetState() == 2) move += 5;
                else if(mainPJ.GetState() == 3) move += 2;
                else 
                {
                    move += 8;
                    enemy.SetUpdateX(enemy.GetUpdateTexture()->x + 8);
                }
            }
            
        } 
        else if(mainPJ.GetIsRight() == true)
        {
            //derecha.
            if(mainPJ.GetJump() == true)
            {
                move -= 8;
                enemy.SetUpdateX(enemy.GetUpdateTexture()->x - 8);
            } 
            else
            {
                if(mainPJ.GetState() == 2) move -= 5;
                else if(mainPJ.GetState() == 3) move -= 2;
                else
                {
                    enemy.SetUpdateX(enemy.GetUpdateTexture()->x - 8);
                    move -= 8;
                } 
            }
        }
        
    if(!(*(enemy.GetIsFixed())))
    {
        if(mainPJ.GetIsRight() != enemy.GetIsRight()) enemy.SetIsRight(mainPJ.GetIsRight());

        if(enemy.GetUpdateTexture()->x > mainPJ.GetUpdateTexture()->x && enemy.GetIsRight()) enemy.SetIsRight(false);
        else if(enemy.GetUpdateTexture()->x < mainPJ.GetUpdateTexture()->x && !enemy.GetIsRight()) enemy.SetIsRight(true);

        if(enemy.GetState() == -1); //estatico.
        else if(enemy.GetIsRight() == false)
        {
            //izquierda.
            if(enemy.GetJump() == true) enemy.SetUpdateX(enemy.GetUpdateTexture()->x - 6);
            else
            {
                if(enemy.GetState() == 2) enemy.SetUpdateX(enemy.GetUpdateTexture()->x - 3);
                else if(enemy.GetState() == 3) enemy.SetUpdateX(enemy.GetUpdateTexture()->x - 1);
                else enemy.SetUpdateX(enemy.GetUpdateTexture()->x - 6);
            }
        } 
        else if(enemy.GetIsRight() == true)
        {
            //derecha.
            if(enemy.GetJump() == true) enemy.SetUpdateX(enemy.GetUpdateTexture()->x + 6);
            else
            {
                if(enemy.GetState() == 2) enemy.SetUpdateX(enemy.GetUpdateTexture()->x + 3);
                else if(enemy.GetState() == 3) enemy.SetUpdateX(enemy.GetUpdateTexture()->x + 1);
                else enemy.SetUpdateX(enemy.GetUpdateTexture()->x + 6);
            }
        }


        std::cout<<"Danger"<<std::endl;
        if(enemy.GetUpdateTexture()->x > mainPJ.GetUpdateTexture()->x - 50 && enemy.GetUpdateTexture()->x < mainPJ.GetUpdateTexture()->x + 50)
        {
            enemy.SetState((enemy.GetUpdateTexture()->x % 2)+2);
            enemy.SetIsFixed(true);
        }
    }
        
    //Animaciones. 
        //Player
        
        frameIndexPlayer = int(((SDL_GetTicks() / 100) % 12));
        mainPJ.SetSourceX((frameIndexPlayer % 6) * mainPJ.GetSourceTexture()->w);
        enemy.SetSourceX((frameIndexPlayer % 8) * enemy.GetSourceTexture()->w); 
}

void OverLord::Render(){
    SDL_RenderClear(media.GetRenderer());
    BackgroundLoop();
    media.DrawMap();
    media.DrawEnemy(enemy);
    media.DrawPJ(mainPJ);
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

    //firts and Second Frame of Background

    SDL_Event event;
    bool wait = true;
    while (wait == true)
    {
        SDL_RenderCopy(media.GetRenderer(), sky, NULL, &motion_Sky);
        SDL_RenderCopy(media.GetRenderer(), sky, NULL, &motionMirror_sky);
        SDL_RenderCopy(media.GetRenderer(), cloud_Light, NULL, &motion_CL);
        SDL_RenderCopy(media.GetRenderer(), cloud_Light, NULL, &motionMirror_CL);
        SDL_RenderCopy(media.GetRenderer(), cloud_Dark, NULL, &motion_CD);
        SDL_RenderCopy(media.GetRenderer(), cloud_Dark, NULL, &motionMirror_CD);
        SDL_RenderCopy(media.GetRenderer(), name_Init, NULL, &location_Name);
        SDL_RenderCopy(media.GetRenderer(), pressToStar, NULL, &location_PressToStar);
        SDL_RenderPresent(media.GetRenderer());

        double start = SDL_GetTicks();
        const int msPerframe = 28;
        double end = SDL_GetTicks();
        auto delay = start + msPerframe - end;
        if(delay > 0) SDL_Delay(delay);

        motion_Sky.x -= 1;
        motionMirror_sky.x -= 1;
        
        motion_CL.x += 1;
        motionMirror_CL.x += 1;
        
        motion_CD.x -= 2;
        motionMirror_CD.x -= 2;

        if (motionMirror_sky.x <= -screenWidth) motionMirror_sky.x *= -1;
        else if (motion_Sky.x <= -screenWidth) motion_Sky.x *= -1;

        if (motionMirror_CL.x >= screenWidth) motionMirror_CL.x *= -1;
        else if (motion_CL.x >= screenWidth) motion_CL.x *= -1;

        if (motionMirror_CD.x <= -screenWidth) motionMirror_CD.x *= -1;
        else if (motion_CD.x <= -screenWidth) motion_CD.x *= -1;


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

    if(mainPJ.GetTexture() != nullptr)
    {
        mainPJ.SetTexture(nullptr);
        SDL_DestroyTexture(mainPJ.GetTexture());
        std::cout<<"Destroy PJ"<<std::endl;
    }

    if(name_Init != nullptr)
    {
        name_Init = nullptr;
        SDL_DestroyTexture(name_Init);
        std::cout<<"Destroy name_Init"<<std::endl;
    }

    if(pressToStar != nullptr)
    {
        pressToStar = nullptr;
        SDL_DestroyTexture(pressToStar);
        std::cout<<"Destroy name_Init"<<std::endl;
    }

    if(sky != nullptr)
    {
        sky = nullptr;
        SDL_DestroyTexture(sky);
        std::cout<<"Destroy sky"<<std::endl;
    }

    if(cloud_Dark != nullptr)
    {
        cloud_Dark = nullptr;
        SDL_DestroyTexture(cloud_Dark);
        std::cout<<"Destroy cloud_Dark"<<std::endl;
    }

    if(cloud_Light != nullptr)
    {
        cloud_Light = nullptr;
        SDL_DestroyTexture(cloud_Light);
        std::cout<<"Destroy cloud_Light"<<std::endl;
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

