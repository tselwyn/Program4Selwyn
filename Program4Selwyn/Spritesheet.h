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

int collided(int x, int y);
bool endValue(int x, int y);

class Sprite
{
	friend int collided(int x, int y);
	friend bool endValue(int x, int y);
public:
	Sprite();
	~Sprite();
	void InitSprites(int width, int height);
	void UpdateSprites(int width, int height, int dir); // 0=down 1=left 2=up 3=right 4=idle
	void DrawSprites(int xoffset, int yoffset);
	bool CollisionEndBlock();
	void ResetPosition();
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
	int animationDirection; // 0=down, 1=left, 2=up, 3=right

	ALLEGRO_BITMAP* image;
};