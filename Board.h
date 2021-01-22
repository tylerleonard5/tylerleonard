#pragma once
#pragma once

#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <map>
#include <iostream>
#include <fstream>
#include "TextureManager.h"
#include "Tile.h"
using namespace std;
using namespace sf;

class Board
{
private:
	int Width;
	int Height;
	int numMine;
	int tileCount;
	int flags;
	int revealed;
public:

	int numRow;
	int numCol;
	vector<int> testboard1;
	vector<int> testboard2;
	vector<int> testboard3;

	vector<bool> tileTorF;

	map<string, Texture> staticIcons;

	Sprite debug;
	Sprite test1;
	Sprite test2;
	Sprite test3;
	Sprite face;

	Sprite hundreds;
	Sprite tens;
	Sprite ones;
	Sprite neg;

	bool lost = false;
	bool over = false;


public:

	vector<Tile> tiles;
	//Constructor
	Board();

	//For window
	Board(bool check);
	//Read Config
	void ReadConfig();

	void refresh(RenderWindow& window);
	void draw(RenderWindow& window);
	void debugRun();

	void createTiles();
	void smileyTiley();
	void testTiles(vector<int>& bits);

	void makeBombs();
	void textureIcon();

	void flagDigits();
	void faceUpdate();

	//GETTERS
	int getWidth();
	int getHeight();
	int getnumMine();
	int getTileCount();
};