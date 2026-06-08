// Tyler Selwyn
// CPSC 440 - Game Programming
// Program 4 - Hedge Maze
// Sprite sheet handler implementation

#include "SpriteSheet.h"

Sprite::Sprite()
{
	image = NULL;
}

Sprite::~Sprite()
{
	al_destroy_bitmap(image);
}

void Sprite::InitSprites(int width, int height)
{
	x = 80;
	y = 80;

	maxFrame = 4;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 30;
	frameHeight = 28;
	animationColumns = 4;
	animationDirection = 0; // facing down

	image = al_load_bitmap("player.bmp");
	al_convert_mask_to_alpha(image, al_map_rgb(255, 0, 255));
}

void Sprite::DrawSprites(int xoffset, int yoffset)
{
	int fx = curFrame * frameWidth;
	int fy = animationDirection * frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight,
		x - xoffset, y - yoffset, 0);
}