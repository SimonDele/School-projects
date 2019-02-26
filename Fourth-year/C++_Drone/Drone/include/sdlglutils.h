#ifndef SDLGLUTILS_H
#define SDLGLUTILS_H

#include <GL/gl.h>
#include <SDL/SDL.h>

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

GLuint loadTexture(const char * filename,bool useMipMap = true);
int takeScreenshot(const char * filename);
/** Dessine les axes
  * @param scale la taille des arêtes */
void drawAxis(double scale = 1);
/** Dessine une boîte*
  * @param sideLength la taille d'une arête */
void drawBox(double sideLength);
int initFullScreen(unsigned int * width = NULL,unsigned int * height = NULL);
int XPMFromImage(const char * imagefile, const char * XPMfile);
SDL_Cursor * cursorFromXPM(const char * xpm[]);

#endif //SDLGLUTILS_H
