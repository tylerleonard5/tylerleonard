#include "Tile.h"
#include "TextureManager.h"

Tile::Tile(map<string, Texture>& textures, float x, float y) {
	revealed.setPosition(x, y);
	hidden.setPosition(x, y);
	flag.setPosition(x, y);
	icon.setPosition(x, y);

	revealed.setTexture(textures["tile_revealed"]);
	hidden.setTexture(textures["tile_hidden"]);
	flag.setTexture(textures["flag"]);

	flag.setColor(Color(255, 255, 255, 0));

	isBomb = false;
	isFlag = false;
	isReveal = false;
	isDebug = false;
}

void Tile::setBombState(bool state) {
	isBomb = state;
}

void Tile::iconUpdate(map<string, Texture>& textures) {
	neighborBombs = 0;
	//Calculates amount of neighbor bombs
	for (int i = 0; i < 8; i++) {
		//checks if neighbor tiles are bombs
		if (neighborTiles[i] != nullptr && neighborTiles[i]->isBomb) {
			neighborBombs++;
		}
	}
	//set bomb image to tile if isBomb
	if (isBomb == true) {
		icon.setTexture(textures["mine"]);
	}
	else
	{
		if (neighborBombs == 1) {
			icon.setTexture(textures["number_1"]);
		} else if (neighborBombs == 2) {
			icon.setTexture(textures["number_2"]);
		}
		else if (neighborBombs == 3) {
			icon.setTexture(textures["number_3"]);
		}
		else if (neighborBombs == 4) {
			icon.setTexture(textures["number_4"]);
		}
		else if (neighborBombs == 5) {
			icon.setTexture(textures["number_5"]);
		}
		else if (neighborBombs == 6) {
			icon.setTexture(textures["number_6"]);
		}
		else if (neighborBombs == 7) {
			icon.setTexture(textures["number_7"]);
		}
		else if (neighborBombs == 8) {
			icon.setTexture(textures["number_8"]);
		}
		else {
			icon.setTexture(textures["tile_revealed"]);
		}
	}
	icon.setColor(Color(255, 255, 255, 0));
	flag.setColor(Color(255, 255, 255, 0));
	hidden.setColor(Color(255, 255, 255, 255));
	isReveal = false;
	isFlag = false;
	isDebug = false;
} 

bool Tile::flagShow() {
	if (!isReveal) {
		//if already flagged set color to opaque and flag to false
		if (isFlag) {
			isFlag = false;
			flag.setColor(Color(255, 255, 255, 0));
		}
		else
		{
			isFlag = true;
			flag.setColor(Color(255, 255, 255, 255));
		}
	}

	return isFlag;
}

void Tile::debugShow() {

	if (isBomb && !isReveal) {
		//if isDebug opaque zero
		if (isDebug) {
			isDebug = false;
			icon.setColor(Color(255, 255, 255, 0));
		}
		//if !isDebug opaque MAX
		else {
			isDebug = true;
			icon.setColor(Color(255, 255, 255, 255));
		}

	}

}

bool Tile::reveal(int& count) {
	//if not reveal nor flagged
	if (isBomb && isFlag){
		icon.setColor(Color(255, 255, 255, 255));
		hidden.setColor(Color(255, 255, 255, 0));
		}
	if (!isReveal & !isFlag) {
		isReveal = true;
		//One is revealed
		count++;
		hidden.setColor(Color(255, 255, 255, 0));
		icon.setColor(Color(255, 255, 255, 255));
		//RECURSION FOR BOMB REVEAL WITH ZERO ADJACENT BOMBS This will adjust count accordingly
		if (neighborBombs == 0 && !isBomb) {
			for (int i = 0; i < 8; i++) {
				//RECURSION STEP
				if (neighborTiles[i] != nullptr && ((neighborTiles[i]->isBomb) == false)) {
					neighborTiles[i]->reveal(count);
				}
			}
		}
	}
	return isBomb;
}

void Tile::drawTile(RenderWindow& window) {
	//order: revelead, hidden, icon, flag
	window.draw(revealed);
	window.draw(hidden);
	window.draw(flag);
	window.draw(icon);
}