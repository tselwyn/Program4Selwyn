// Tyler Selwyn
// CPSC 440 - Game Programming
// Program 4 - Hedge Maze
// Sprite sheet handler class for player character

#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
using namespace std;

class Sprite
{
public:
	Sprite();
	~Sprite();
	void InitSprites(int width, int height);
	void DrawSprites(int xoffset, int yoffset);
	float getX() { return x; }
	float getY() { return y; }
	int getWidth() { return frameWidth; }
	int getHeight() { return frameHeight; }
private:
	float x;
	float y;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationDirection;

	ALLEGRO_BITMAP* image;
};