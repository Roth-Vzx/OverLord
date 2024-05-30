#include <headers/overlord.h>
#include <headers/exception.h>

//SDL_Renderer* OverLord::renderer = nullptr;

OverLord::OverLord()
{
    gameName = SDL_strdup("OverLord");
    gameState = true;
    frameIndexPlayer = 0;
    movePlayer = 0;

    window = nullptr;
    sky = nullptr;
    cloud_Dark = nullptr;
    cloud_Light = nullptr;
    name_Init = nullptr;
    pressToStar = nullptr;

    screenHeigth = 720;
    screenWidth = 1280;

    media.SetScreenWidth(screenWidth);
    media.SetScreenHeigth(screenHeigth);

    mainPJ.GetSource()->w = 69;
    mainPJ.GetSource()->h = 44;

    mainPJ.GetUpdate()->w = 180;
    mainPJ.GetUpdate()->h = 180;
    mainPJ.GetUpdate()->x = screenWidth/2 - screenWidth/25;
    mainPJ.GetUpdate()->y = screenHeigth - mainPJ.GetUpdate()->h - media.GetLevels()->GetDestinyLand()->h;

    mainPJ.SetLimitY(mainPJ.GetUpdate()->y);

    enemy.GetUpdate()->w = 240;
    enemy.GetUpdate()->h = 240;
    enemy.GetUpdate()->x = screenWidth/2 + screenWidth/6;
    enemy.GetUpdate()->y = screenHeigth - enemy.GetUpdate()->h - media.GetLevels()->GetDestinyLand()->h;

    enemy.GetSource()->w = 140;
    enemy.GetSource()->h = 93;

    enemy.SetState(1);
    enemy.SetLimitY(enemy.GetUpdate()->y);
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
        paths.push_back(SDL_strdup("resources/img/background_layer_1.png"));
        paths.push_back(SDL_strdup("resources/img/background_layer_3.png"));
        media.SetBackground(paths);

        std::cout<<"FINISH INIT"<<std::endl;
    }
    catch(const SDL_Exception& exception)
    {
        std::cout<<"An Error has ocurred: "<<exception.message<<std::endl;
        gameState = false;
        Close();
    }
}

void OverLord::GenerateDelay(const double& start, const int& msPerframe)
{
    double end = SDL_GetTicks();
    auto delay = start + msPerframe - end;
    if(delay > 0) SDL_Delay(delay);
}

void OverLord::GameLoop()
{
    MenuInit();
    while(true)
    {
        double start = SDL_GetTicks();
        HandleEvents();
        if(gameState==false)
        {
            Close();
            break;
        }
        else
        {
            Update();
            Render();
            GenerateDelay(start,16);
        }
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
                            if(mainPJ.GetUpdate()->y == mainPJ.GetLimitY()) //LimitY = Piso
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
                movePlayer += 8;
                enemy.GetUpdate()->x += 8;
            } 
            else
            {
                if(mainPJ.GetState() == 2) 
                {
                    movePlayer += 5;
                    enemy.GetUpdate()->x += 5;
                }
                else if(mainPJ.GetState() == 3)
                {
                    movePlayer += 2;
                    enemy.GetUpdate()->x += 2;
                } 
                else 
                {
                    movePlayer += 8;
                    enemy.GetUpdate()->x += 8;
                }
            }  
        } 
        else if(mainPJ.GetIsRight() == true)
        {
            //derecha.
            if(mainPJ.GetJump() == true)
            {
                movePlayer -= 8;
                enemy.GetUpdate()->x -= 8;
            } 
            else
            {
                if(mainPJ.GetState() == 2)
                {
                    movePlayer -= 5;
                    enemy.GetUpdate()->x -= 5;
                } 
                else if(mainPJ.GetState() == 3)
                {
                    movePlayer -= 2;
                    enemy.GetUpdate()->x -= 2;
                } 
                else
                {
                    enemy.GetUpdate()->x -= 8;
                    movePlayer -= 8;
                } 
            }
        }  
        
    if(!(*(enemy.GetIsFixed())))
    {
        if(mainPJ.GetIsRight() != enemy.GetIsRight()) enemy.SetIsRight(mainPJ.GetIsRight());

        if(enemy.GetUpdate()->x > mainPJ.GetUpdate()->x && enemy.GetIsRight()) enemy.SetIsRight(false);
        else if(enemy.GetUpdate()->x < mainPJ.GetUpdate()->x && !enemy.GetIsRight()) enemy.SetIsRight(true);

        if(enemy.GetState() == -1); //estatico.
        else if(enemy.GetIsRight() == false)
        {
            //izquierda.
            if(enemy.GetJump() == true) enemy.GetUpdate()->x -= 6;
            else
            {
                if(enemy.GetState() == 2) enemy.GetUpdate()->x -= 3;
                else if(enemy.GetState() == 3) enemy.GetUpdate()->x -= 1;
                else enemy.GetUpdate()->x -= 6;
            }
        } 
        else if(enemy.GetIsRight() == true)
        {
            //derecha.
            if(enemy.GetJump() == true) enemy.GetUpdate()->x += 6;
            else
            {
                if(enemy.GetState() == 2) enemy.GetUpdate()->x += 3;
                else if(enemy.GetState() == 3) enemy.GetUpdate()->x += 1;
                else enemy.GetUpdate()->x += 6;
            }
        }

        //std::cout<<"Danger"<<std::endl;
        if(enemy.GetUpdate()->x > mainPJ.GetUpdate()->x - 50 && enemy.GetUpdate()->x < mainPJ.GetUpdate()->x + 50)
        {
            enemy.SetState((enemy.GetUpdate()->x % 2)+2);
            enemy.SetIsFixed(true);
        }
    }
        
    //Animaciones. 
        //Player
        
    frameIndexPlayer = int(((SDL_GetTicks() / 100) % 12));
    mainPJ.GetSource()->x = (frameIndexPlayer % 6) * mainPJ.GetSource()->w;
    enemy.GetSource()->x = (frameIndexPlayer % 8) * enemy.GetSource()->w;
}

void OverLord::Render(){
    SDL_RenderClear(media.GetRenderer());
    media.DrawLevel(mainPJ, enemy, movePlayer);
    SDL_RenderPresent(media.GetRenderer());
}

void OverLord::MenuInit(){

    SDL_Rect destSky, destCloudsL, destCloudsD;
    SDL_Rect destName, destPressToStart;

    destSky.h = destCloudsL.h = destCloudsD.h = screenHeigth; // Para ocupar Alto de la Pantalla

    destSky.w = destCloudsL.w = destCloudsD.w = screenWidth; // Para ocupar Ancho de la Pantalla

    destSky.x = destSky.y = destCloudsL.x = destCloudsL.y = destCloudsD.x = destCloudsD.y = 0; // Posicion (0,0)

    //Posicion Letras

    destName.h = 300;
    destName.w = 890;
    destName.x = screenWidth/2 - screenWidth/3;
    destName.y = 60;

    destPressToStart.h = 160;
    destPressToStart.w = 800;
    destPressToStart.x = screenWidth/2 - screenWidth/3.3;
    destPressToStart.y = 400;

    SDL_Event event;
    bool wait = true;
    while (wait == true)
    {
        double start = SDL_GetTicks();

        media.DrawDoubleFrame(sky, destSky, -1);
        media.DrawDoubleFrame(cloud_Light, destCloudsL, 1);
        media.DrawDoubleFrame(cloud_Dark, destCloudsD, -2);

        SDL_RenderCopy(media.GetRenderer(), name_Init, NULL, &destName);
        SDL_RenderCopy(media.GetRenderer(), pressToStar, NULL, &destPressToStart);

        SDL_RenderPresent(media.GetRenderer());

        GenerateDelay(start,24);
        
        SDL_PollEvent(&event);
        switch (event.type)
        {
            case SDL_KEYUP:
            case SDL_MOUSEBUTTONUP:
                wait = false;
                break;    
            case SDL_QUIT:
                wait = false;
                gameState = false;
                break;
        } 
    }
    DestroyTexture(sky);
    DestroyTexture(cloud_Light);
    DestroyTexture(cloud_Dark);
    DestroyTexture(name_Init);
    DestroyTexture(pressToStar);  
}

void OverLord::DestroyTexture(SDL_Texture*& texture)
{
    try
    {
        if(texture == nullptr) std::cout<<"Anything to Destroy"<<std::endl;
        else 
        {
            texture = nullptr;
            SDL_DestroyTexture(texture);
            std::cout<<"Destroy Texture"<<std::endl;
        }
    }
    catch(const SDL_Exception& exception)
    {
        std::cout<<"An Error has ocurred: "<<exception.message<<std::endl;
    }
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

    while(!(*media.GetLevels()->GetBackground()).empty())
    {
        for(auto iterator = (*media.GetLevels()->GetBackground()).rbegin(); iterator != (*media.GetLevels()->GetBackground()).rend(); ++iterator)
        {
            *iterator = nullptr;
            SDL_DestroyTexture(*iterator);
            (*media.GetLevels()->GetBackground()).pop_back();
            std::cout<<"Destroy Main Background"<<std::endl;
        }
        std::cout<<"Destroy Main Background Confirm"<<std::endl;
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

