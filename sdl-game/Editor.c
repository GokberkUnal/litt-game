#include "Editor.h"

#include <SDL2/SDL_image.h>
#include <string.h>

#include "Game.h"

#include "Draws.h"

#include "Colors.h"

#define SavePNG(surface, file) \
        SDL_SaveBMP_RW(surface, SDL_RWFromFile(file, "rb+"), 1)

//To hold the temporary pixel info for a GameObject
//DEFAULT: WHITE
Uint32 temp = 0xFFFFFFFF;

//Location of the map
const char* mapLocation = "resources/environment/test.png";

int scale = 15;

_Bool init = 0;

GameObjectList InitializeEditor()
{
	if (!init) {
		init++;
		map_init();
	}
	render_map();
	return list;
}

void RenderEditor() {
	//TODO: DrawButtonWithImageOnScreen i�in parametreleri olan bir fonksiyonu alan varyant�n� yap.
	//DrawButtonWithImageOnScreen()
	//TODO
}

void render_map() {
	if (!init) {
		init++;
		map_init();
	}
	for (int y = 0; y < maps->h; y++) {
		for (int x = 0; x < maps->w; x++) {
			//TODO: DrawButtonOnScreen i�in parametreleri olan bir fonksiyonu alan varyant�n� yap.
			int parameters[3] = { x,y, BLACK};
			//printf("%X\n", get_pixel_data(12,10));
			DrawInteractiveRectangleOnScreen((Rect) {x*scale, y*scale, scale, scale}, to_color(get_pixel_data(x,y)), put_pixel, parameters);
			//DrawRectangleOnScreen((Rect){ x * scale, y * scale, scale, scale }, Black);
		}
	}
	SDL_FreeSurface(maps);
	init--;
}


void map_init()
{
	maps = IMG_Load(mapLocation);
}

/**
Obje tipleri:
	0 - player
	1 - yarasa
	2 - iskelet
	3 - ��valye
	4 - boss
	5 - trap1
	6 - trap2
	7 - dirt
	8 - grass
*/
void onclick(Uint8 object) {
	switch (object) {
	case 0:
		temp = 0xFF1900FF;
		break;
	case 1:
		temp = 0xFFFF0010;
		break;
	case 2:
		temp = 0xFFC1000C;
		break;
	case 3:
		temp = 0xFF820008;
		break;
	case 4:
		temp = 0xFF000000;
		break;
	case 5:
		temp = 0xFF9E5C38;
		break;
	case 6:
		temp = 0xFF00821A;
		break;
	case 7:
		temp = 0xFFFF00FA;
		break;
	case 8:
		temp = 0xFFA300A0;
		break;
	}
}
void process_pixels() {
	Uint8 rgba[4]; //0 - r, 1 - g, 2 - b, 3 - a

	int bpp = maps->format->BytesPerPixel;

	for (int y = 0; y < maps->h; y++) {
		for (int x = 0; x < maps->w; x++) {
			
		}
	}
}

Uint32 get_pixel_data(int x, int y)
{
	if (SDL_MUSTLOCK(maps)) {
		if (SDL_LockSurface(maps) < 0) {
			fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
			return;
		}
	}
	int bpp = maps->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8* p = (Uint8*)maps->pixels + y * maps->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16*)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32*)p;
		break;

	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
	if (SDL_MUSTLOCK(maps)) {
		SDL_UnlockSurface(maps);
	}
}

void put_pixel(int* parameters) // int x, int y, Uint32 pixel
{
	int x = (int)parameters[0];
	int y = (int)parameters[1];
	Uint32 pixel = (Uint32)parameters[2];
	//printf("%X", pixel);
	if (SDL_MUSTLOCK(maps)) {
		if (SDL_LockSurface(maps) < 0) {
			fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
			return;
		}
	}
	int bpp = maps->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8* p = (Uint8*)maps->pixels + y * maps->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16*)p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32*)p = pixel;
		break;
	}
	printf("%X", *(Uint32*)p);
	if (SDL_MUSTLOCK(maps)) {
		SDL_UnlockSurface(maps);
	}
	SDL_LockSurface(maps);

	SavePNG(maps, mapLocation);
		SDL_UnlockSurface(maps);
}

Uint32 get_object_color(Uint8 red, Uint8 green, Uint8 blue)
{
	Uint32 data = 0;
	data = (Uint32)255 << 24;
	data += (Uint32)red << 16;
	data += (Uint32)green << 8;
	data += (Uint32)blue << 0;

	return data;
}

void get_rgba(Uint32 pixel_data, Uint8* rgba)
{
	SDL_GetRGBA(pixel_data, maps->format, rgba[0], rgba[1], rgba[2], rgba[3]);
}

Color to_color(Uint32 pixel_data)
{
	Color temp;

	if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
		temp.b = (pixel_data >> 24) & 0xff;
		temp.g = (pixel_data >> 16) & 0xff;
		temp.r = (pixel_data >> 8) & 0xff;
		temp.a = pixel_data & 0xff;
	}
	else {
		temp.a = (pixel_data >> 24) & 0xff;
		temp.b = (pixel_data >> 16) & 0xff;
		temp.g = (pixel_data >> 8) & 0xff;
		temp.r = pixel_data & 0xff;
	}
	
	return temp;
}
