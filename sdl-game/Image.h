#pragma once

//#ifndef IMAGE_H
//#define IMAGE_H

#include "Structs.h"


void InitializeImage();

Image* LoadTexture(char* path, bool is_sprite_sheet, Vector2 clip_size);

bool UnloadTexture(Image * img);

//SDL_Texture** SplitTexture(Image* texture, Vector2 split_size, int *size);

void DrawImage(Image* image, Rect rect, bool left);
void DrawClipImage(Image* image, Rect rect, Rect clipRect, int index, bool);

//#endif // !IMAGE_H
