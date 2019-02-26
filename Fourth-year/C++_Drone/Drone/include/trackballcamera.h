#ifndef TRACKBALLCAMERA_H
#define TRACKBALLCAMERA_H

#include <SDL/SDL.h>

/**
  * Class gestionnaire de tous les mouvements de la caméra; permet d'effectuer des rotations autour du centre à la souris.
  * Récupéré d'Openclassrooms.
  * @author Louis, Openclassrooms
  */
class TrackBallCamera
{
public:
    TrackBallCamera();

    virtual void OnMouseMotion(const SDL_MouseMotionEvent & event);
    virtual void OnMouseButton(const SDL_MouseButtonEvent & event);
    virtual void OnKeyboard(const SDL_KeyboardEvent & event);

    virtual void look();
    virtual void setMotionSensivity(double sensivity);
	virtual void setScrollSensivity(double sensivity);

    virtual ~TrackBallCamera();
protected:
    double _motionSensivity;
	double _scrollSensivity;
    bool _hold;
    double _distance;
    double _angleY;
    double _angleZ;
    SDL_Cursor * _hand1;
    SDL_Cursor * _hand2;
};

#endif //TRACKBALLCAMERA_H
