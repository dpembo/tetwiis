#ifndef __GUI_H__
#define __GUI_H__

#include <grrlib.h>    

#define FONT_HEIGHT 16
#define FONT_WIDTH 8

#define START_X 150
#define START_Y 150
#define START_OX 300

Mtx GXmodelView2D;
GRRLIB_texImg	*tex_back,*tex_bull, *tex_cursor, *tex_font,*tex_logo;

void tex_Init();
void tex_free();

void draw_background();
void draw_bullet(int x,int y, bool filled);

#endif //__GUI_H__
