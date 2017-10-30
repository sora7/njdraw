#include <iostream>
//#include <fstream>
#include <string>
#include <SDL2/SDL.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool init()
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout << "SDL init fail" << endl;
        return false;
    }

//    //hide console
//    ofstream ctt("CON");
//    freopen( "CON", "w", stdout );
//    freopen( "CON", "w", stderr );
//    ctt.close();

    window = SDL_CreateWindow( "SDL Test",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN
                            );
    if( window == NULL )
    {
        cout << "cannot create window " << SDL_GetError() << endl;
        return false;
    }

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if( renderer == NULL )
    {
        cout << "cannot create renderer " << SDL_GetError() << endl;
        return false;
    }

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );

    return true;
}

void close()
{
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;

    SDL_Quit();
}

class Char
{
    public:
        Char()
        {
            this->x = 0;
            this->y = 0;

            this->w = 20;
            this->h = 30;
        }

        int x;
        int y;

        int w;
        int h;

        void draw(SDL_Renderer* renderer)
        {
            int h_2 = int(this->h/2);
            int w_2 = int(this->w/2);

            int x1 = this->x;
            int y1 = this->y - h_2;

            int x2 = this->x - w_2;
            int y2 = this->y + h_2;

            int x3 = this->x + w_2;
            int y3 = this->y + h_2;

            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
            SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
            SDL_RenderDrawLine(renderer, x3, y3, x1, y1);
            SDL_RenderPresent(renderer);
        }
};

int main(int argc, char** argv) {
    if( !init() )
    {
        cout << "init fail" << endl;
    }
    else
    {
        bool quit = false;

        Char c;
        c.x = 300;
        c.y = 200;

        while ( !quit )
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

            c.draw(renderer);

            SDL_Event e;
            while( SDL_PollEvent( &e ) != 0 )
            {
                if ( e.type == SDL_QUIT )
                {
                    cout << "oops, exit" << endl;
                    quit = true;
                }
                else if( e.type == SDL_KEYDOWN )
                {
                    switch( e.key.keysym.sym )
                    {
                        case SDLK_ESCAPE:
                            quit = true;
                            cout << "QUIT" << endl;
                            break;
                        case SDLK_UP:
                            c.y -= 10;
                            cout << "UP" << endl;
                            break;
                        case SDLK_DOWN:
                            c.y += 10;
                            cout << "DOWN" << endl;
                            break;
                        case SDLK_LEFT:
                            c.x -= 10;
                            cout << "LEFT" << endl;
                            break;
                        case SDLK_RIGHT:
                            c.x += 10;
                            cout << "RIGHT" << endl;
                            break;
                        case SDLK_KP_PLUS:
                            c.h += 2;
                            c.w += 2;
                            cout << "INCREASE" << endl;
                            break;
                        case SDLK_KP_MINUS:
                            c.h -= 2;
                            c.w -= 2;
                            cout << "DECREASE" << endl;
                            break;
                    }
                }
            }
        }
    }


    close();

    return 0;
}
