#include<headers/map.h>


int lvl1[10][35] = {

    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
    { 0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },

};

Map::Map()
{
    tileset = MediaFiles::CreateTexture("resources/img/map_tileset.png");

    LoadMap(lvl1);

    src.y = 0;
    src.w = dest.w = 24;
    src.h = dest.h = 24;

    dest.x = dest.y = 0;
}

Map::~Map(){};

void Map::LoadMap(int arr[10][35])
{
    for(int row = 0; row< 10; ++row){
        for (int column = 0; column < 35; ++column)
        {
            map[row][column] = arr[row][column];
        }
    }
}

void Map::Draw()
{
    int type;

    for(int row = 0; row< 10; ++row){
        for (int column = 0; column < 35; ++column)
        {
            type = map[row][column];

            dest.x = column * 32;
            dest.y = row * 32;

            switch (type)
            {
            //Dirt left
            case 0:
                src.x = src.y = 0;
                src.w = src.h = 24;
                SDL_RenderCopy(OverLord::renderer, tileset, &src, &dest);
                //MediaFiles::DrawMap(tileset, src, dest);
            break;

            //Dirt Center
            case 1:
                src.x = 48;
                SDL_RenderCopy(OverLord::renderer, tileset, &src, &dest);
                //MediaFiles::DrawMap(tileset, src, dest);
            break;

            //Dirt Right.
            case 2:
                src.x = 72;
                SDL_RenderCopy(OverLord::renderer, tileset, &src, &dest);
                //MediaFiles::DrawMap(tileset, src, dest);
            break;
            }
        }
    }
}