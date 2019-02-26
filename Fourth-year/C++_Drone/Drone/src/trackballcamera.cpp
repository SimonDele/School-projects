#include "../include/trackballcamera.h"

#include <GL/glu.h>
#include <cmath>
#include "../include/sdlglutils.h"

TrackBallCamera::TrackBallCamera()
{
    const char *hand1[] =
        {
            /* width height num_colors chars_per_pixel */
            " 16 16 3 1 ",
            /* colors */
            "X c #000000",
            ". c #ffffff",
            "  c None",
            /* pixels */
            "       XX       ",
            "   XX X..XXX    ",
            "  X..XX..X..X   ",
            "  X..XX..X..X X ",
            "   X..X..X..XX.X",
            "   X..X..X..X..X",
            " XX X.......X..X",
            "X..XX..........X",
            "X...X.........X ",
            " X............X ",
            "  X...........X ",
            "  X..........X  ",
            "   X.........X  ",
            "    X.......X   ",
            "     X......X   ",
            "     X......X   ",
            "0,0"
        };

    const char *hand2[] =
        {
            /* width height num_colors chars_per_pixel */
            " 16 16 3 1 ",
            /* colors */
            "X c #000000",
            ". c #ffffff",
            "  c None",
            /* pixels */
            "                ",
            "                ",
            "                ",
            "                ",
            "    XX XX XX    ",
            "   X..X..X..XX  ",
            "   X........X.X ",
            "    X.........X ",
            "   XX.........X ",
            "  X...........X ",
            "  X...........X ",
            "  X..........X  ",
            "   X.........X  ",
            "    X.......X   ",
            "     X......X   ",
            "     X......X   ",
            "0,0"
        };
    _hand1 = cursorFromXPM(hand1);
    _hand2 = cursorFromXPM(hand2);
    SDL_SetCursor(_hand1);
    _hold = false;
    _angleY = 0;
    _angleZ = 0;
    _distance = 2;
    _motionSensivity = 0.3;
    _scrollSensivity = 1;
}

void TrackBallCamera::OnMouseMotion(const SDL_MouseMotionEvent & event)
{
    if (_hold)
    {
        _angleZ += event.xrel*_motionSensivity;
        _angleY += event.yrel*_motionSensivity;
        if (_angleY > 90)
            _angleY = 90;
        else if (_angleY < -90)
            _angleY = -90;
    }
}

void TrackBallCamera::OnMouseButton(const SDL_MouseButtonEvent & event)
{
    if (event.button == SDL_BUTTON_LEFT)
    {
        if ((_hold)&&(event.type == SDL_MOUSEBUTTONUP))
        {
            _hold = false;
            SDL_SetCursor(_hand1);
        }
        else if ((!_hold)&&(event.type == SDL_MOUSEBUTTONDOWN))
        {
            _hold = true;
            SDL_SetCursor(_hand2);
        }
    }
    else if ((event.button == SDL_BUTTON_WHEELUP)&&(event.type == SDL_MOUSEBUTTONDOWN))
    {
        _distance -= _scrollSensivity;
        if (_distance < 0.1)
            _distance = 0.1;
    }
    else if ((event.button == SDL_BUTTON_WHEELDOWN)&&(event.type == SDL_MOUSEBUTTONDOWN))
    {
            _distance += _scrollSensivity;
    }
}

void TrackBallCamera::OnKeyboard(const SDL_KeyboardEvent & event)
{
    if ((event.type == SDL_KEYDOWN)&&(event.keysym.sym == SDLK_HOME))
    {
        _angleY = 0;
        _angleZ = 0;
    }
}

void TrackBallCamera::setMotionSensivity(double sensivity)
{
    _motionSensivity = sensivity;
}

void TrackBallCamera::setScrollSensivity(double sensivity)
{
    _scrollSensivity = sensivity;
}

TrackBallCamera::~TrackBallCamera()
{
    SDL_FreeCursor(_hand1);
    SDL_FreeCursor(_hand2);
    SDL_SetCursor(NULL);
}

void TrackBallCamera::look()
{
    gluLookAt(_distance,0,0,
              0,0,0,
              0,0,1);
    glRotated(_angleY,0,1,0);
    glRotated(_angleZ,0,0,1);
}
