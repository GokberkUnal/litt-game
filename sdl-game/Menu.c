#include "Draws.h"

#include "Globals.h"

#include "Game.h"

void play() {
	game_state = INGAME;
}

void editor() {
	game_state = EDITOR;
}

void instructions() {
	game_state = MENU;
}

void exit_game() {
	game_state = QUIT;
}

void RenderMenu() {
	DrawButtonOnScreen("Oyna", (Rect) { camera->width / 2 - 100, camera->height / 2, 200, 50 }, (Color) { 0, 0, 0, 255 }, (Color) { 255, 255, 255, 255 }, Font_Minecraft, play, NULL);
	DrawButtonOnScreen("Harita Editoru", (Rect) { camera->width / 2 - 100, camera->height / 2 + 60, 200, 50 }, (Color) { 0, 0, 0, 255 }, (Color) { 255, 255, 255, 255 }, Font_Minecraft, editor, NULL);
	DrawButtonOnScreen("Nasil Oynanir?", (Rect) { camera->width / 2 - 100, camera->height / 2 + 60 * 2, 200, 50 }, (Color) { 0, 0, 0, 255 }, (Color) { 255, 255, 255, 255 }, Font_Minecraft, instructions, NULL);
	DrawButtonOnScreen("Cikis", (Rect) { camera->width / 2 - 100, camera->height / 2 + 60 * 3, 200, 50 }, (Color) { 0, 0, 0, 255 }, (Color) { 255, 255, 255, 255 }, Font_Minecraft, exit_game, NULL);
}

