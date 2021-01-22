#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TextureManager.h"

using namespace sf;
using namespace std;

class Tile {
private:

	Sprite revealed;
	Sprite hidden;
	Sprite icon;
	Sprite flag;


public:
	Tile(map<string, Texture>& textures, float xpos, float ypos);

	vector<Tile*> neighborTiles;
	int neighborBombs;
	bool isBomb;
	bool isFlag;
	bool isReveal;
	bool isDebug;

	void setBombState(bool bombstate);
	void iconUpdate(map<string, Texture>& textures);

	bool flagShow();
	void debugShow();
	bool reveal(int& count);

	void drawTile(RenderWindow& window);
};