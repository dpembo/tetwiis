#include <gccore.h>
#include <stdlib.h>
#include "images/img_bull.h"
#include "images/img_cursor.h"
#include "images/tetwiisback.h"
#include "fonts/BMfont5.h"

#include "gui.h"

void tex_Init()
{	//font is initialized first
	tex_font=GRRLIB_LoadTexture(BMfont5);
    GRRLIB_InitTileSet(tex_font, FONT_WIDTH, FONT_HEIGHT, 0);
	
	tex_cursor=GRRLIB_LoadTexturePNG(img_cursor);
	tex_back=GRRLIB_LoadTexturePNG(tetwiisback);
	tex_bull=GRRLIB_LoadTexturePNG(img_bull);
}

void tex_free()
{	free(tex_back);
	free(tex_logo);
	free(tex_bull);
	free(tex_cursor);
	free(tex_font);
}

void draw_background()
{
    GRRLIB_FillScreen(0x000000FF);    // Clear the screen
	GRRLIB_DrawImg(0,-20,tex_back,0,1,1,0xFFFFFFFF);
}

void draw_bullet(int x,int y, bool filled)
{
	GRRLIB_DrawImg(x,y,tex_bull,0,1,1,0xFFFFFF00+(filled?0xFF:0x40));
}

