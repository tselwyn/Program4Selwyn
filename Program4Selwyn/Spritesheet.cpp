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
	frameWidth = 60;
	frameHeight = 56;
	animationColumns = 4;
	animationDirection = 0; // facing down

	image = al_load_bitmap("player.bmp");
	al_convert_mask_to_alpha(image, al_map_rgb(255, 0, 255));
}

void Sprite::UpdateSprites(int width, int height, int dir)
{
	if (dir == 4) // standing still
	{
		curFrame = 0;
		return;
	}

	int oldx = x;
	int oldy = y;
	animationDirection = dir;

	// move in the direction pressed
	if (dir == 0) y += 8;
	else if (dir == 1) x -= 8;
	else if (dir == 2) y -= 8;
	else if (dir == 3) x += 8;

	// cycle walk animation
	if (++frameCount > frameDelay)
	{
		frameCount = 0;
		if (++curFrame >= maxFrame)
			curFrame = 0;
	}

	// collision box pulled in so we fit through corridors
	int left = x + 5;
	int right = x + frameWidth - 5;
	int top = y + 5;
	int bottom = y + frameHeight - 5;

	// undo move if any corner hits a wall
	if (collided(left, top) || collided(right, top) ||
		collided(left, bottom) || collided(right, bottom))
	{
		x = oldx;
		y = oldy;
	}
}

bool Sprite::CollisionEndBlock()
{
	// check middle of sprite for exit tile
	if (endValue(x + frameWidth / 2, y + frameHeight / 2))
		return true;
	return false;
}

// put player back at the starting spot for new level
void Sprite::ResetPosition()
{
	x = 80;
	y = 80;
	curFrame = 0;
	animationDirection = 0;
}

void Sprite::DrawSprites(int xoffset, int yoffset)
{
	int fx = curFrame * frameWidth;
	int fy = animationDirection * frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight,
		x - xoffset, y - yoffset, 0);
}