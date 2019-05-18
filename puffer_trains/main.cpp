#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <iostream>
#include <math.h>
#include <random>


int main()
{
	bool current[128][128];
	bool next[128][128];

	int len_x = 128;
	int len_y = 128;
	int scale = 8;
	//randomly generate starting life
	for (int x = 0; x < len_x; x++) {
		for (int y = 0; y < len_y; y++) {
			current[x][y] = rand() % 2;
		}
	}

	al_init();
	ALLEGRO_DISPLAY* display = al_create_display(len_x*scale, len_y*scale);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);	

	while (1) {
		al_rest(0.5);
		std::cout << "step" << std::endl;

		al_clear_to_color(al_map_rgb(0, 0, 0));
		//go through all spaces
		for (int x = 0; x < len_x; x++) {
			for (int y = 0; y < len_y; y++) {

				//define start and end coordinates to check cell statuses
				int start_x = x - 1;
				int start_y = y - 1;
				int end_x = x + 2;
				int end_y = y + 2;

				//edge cases
				if (x == 0) {
					start_x = 0;
				}
				if (y == 0) {
					start_y = 0;
				}
				if (x == len_x-1) {
					end_x = len_x + 1;
				}	
				if (y == len_y-1) {
					end_y = len_y + 1;
				}

				int neighbours = 0;
				//walk through spaces in 3x3 area, check which cells are live
				for (int i = start_x; i < end_x; ++i) {
					for (int j = start_y; j < end_y; ++j) {
						if (current[i][j]) {
							neighbours++;
						}
					}
				}
				if (current[x][y]) {
					//IF alive
					neighbours--;
					if ((2 == neighbours) || (neighbours == 3)) {
						next[x][y] = true;
					}
					else {
						next[x][y] = false;
					}
				}
				else {
					// IF dead
					if (neighbours == 3) {
						next[x][y] = true;
					}
					else {
						next[x][y] = false;
					}

				}
			}
		}

		/*
		for (int x = 0; x < 100; x++) {
			for (int y = 0; y < 100; y++) {
				if (current[x][y] == 1) {
					al_draw_pixel(x, y, color);
				}
				else {
					color = al_map_rgb(0, 0, 0);
					al_draw_pixel(x, y, color);
				}
			}
		}
		*/
		for (int x = 0; x < len_x; x++) {
			for (int y = 0; y < len_y; y++) {
				current[x][y] = next[x][y];
			}
		}
		//change alive cells to white
		for (int x = 0; x < len_x*scale; x++) {
			for (int y = 0; y < len_y*scale; y++) {
				if (current[x/scale][y/scale] == 1) {
					al_draw_pixel(x, y, color);
				}
			}
		}
		al_flip_display();
	}

	return 0;
}