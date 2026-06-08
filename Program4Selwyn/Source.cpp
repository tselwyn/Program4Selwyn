// Tyler Selwyn
// CPSC 440 - Game Programming
// Program 4 - Hedge Maze
// Main game file - side scrolling maze with 3 levels and a countdown timer

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "SpriteSheet.h"
#include "mappy_A5.h"
#include <cstdio>
#include <iostream>
using namespace std;

int collided(int x, int y);
bool endValue(int x, int y);

int main(void)
{
	const int WIDTH = 800;
	const int HEIGHT = 600;
	bool done = false;
	bool render = false;

	// arrow key tracking
	bool keys[] = { false, false, false, false };
	enum KEYS { UP, DOWN, LEFT, RIGHT };

	Sprite player;

	// timer countdown stuff
	int frameCounter = 0;
	int secondsLeft = 60;
	char timerText[32];

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_FONT* font = NULL;

	if (!al_init()) return -1;
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	display = al_create_display(WIDTH, HEIGHT);
	if (!display) return -1;

	font = al_load_font("JA.TTF", 24, 0);
	player.InitSprites(WIDTH, HEIGHT);

	char mapName[] = "map1.FMP";
	if (MapLoad(mapName, 1)) return -5;

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);

	int xOff = 0;
	int yOff = 0;

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			// count frames for the countdown
			frameCounter++;
			if (frameCounter >= 60)
			{
				frameCounter = 0;
				secondsLeft--;
			}

			// move player based on which arrow is held
			if (keys[UP])
				player.UpdateSprites(WIDTH, HEIGHT, 2);
			else if (keys[DOWN])
				player.UpdateSprites(WIDTH, HEIGHT, 0);
			else if (keys[LEFT])
				player.UpdateSprites(WIDTH, HEIGHT, 1);
			else if (keys[RIGHT])
				player.UpdateSprites(WIDTH, HEIGHT, 3);
			else
				player.UpdateSprites(WIDTH, HEIGHT, 4); // idle

			render = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			}
		}

		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;

			// center map on player
			xOff = player.getX() + player.getWidth() - WIDTH / 2;
			yOff = player.getY() + player.getHeight() - HEIGHT / 2;

			if (xOff < 0) xOff = 0;
			if (xOff > (mapwidth * mapblockwidth - WIDTH))
				xOff = mapwidth * mapblockwidth - WIDTH;
			if (yOff < 0) yOff = 0;
			if (yOff > (mapheight * mapblockheight - HEIGHT))
				yOff = mapheight * mapblockheight - HEIGHT;

			MapDrawBG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1);
			MapDrawFG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1, 0);
			player.DrawSprites(xOff, yOff);

			// draw timer in top left
			sprintf_s(timerText, "Time: %d", secondsLeft);
			al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, 0, timerText);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	MapFreeMem();
	al_destroy_font(font);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}

// check if a tile is solid
int collided(int x, int y)
{
	BLKSTR* blockdata;
	blockdata = MapGetBlock(x / mapblockwidth, y / mapblockheight);
	return blockdata->tl;
}

// check if tile is the level exit
bool endValue(int x, int y)
{
	BLKSTR* data;
	data = MapGetBlock(x / mapblockwidth, y / mapblockheight);
	if (data->user1 == 8)
		return true;
	return false;
}