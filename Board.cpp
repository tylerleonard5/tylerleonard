#include "Board.h"
#include "TextureManager.h"

//READ
void Board::ReadConfig() {
	ifstream inFile("boards/config.cfg");
	int val;

	int i = 0;

	if (inFile.is_open()) {
		while (inFile >> val) {
			if (i == 0) {
				numCol = val;
				this->Width = val * 32;
			}
			else if (i == 1) {
				numRow = val;
				this->Height = (val * 32) + 88;
			}
			else if (i == 2) {
				this->numMine = val;
			}
			i++;
		}
		inFile.close();
	}
	this->tileCount = numCol * numRow;
}

Board::Board(bool check) {
	ReadConfig();
}

//CONSTRUCTOR
Board::Board() {
	ReadConfig();

	srand(time(0));
	flags = numMine;

	ifstream inFile;
	string line;

	inFile.open("boards/testboard1.brd");

	if (inFile.is_open())
	{
		int bit;
		while (getline(inFile, line)) {
			for (int i = 0; i < line.size(); i++) {
				int num = line[i] - '0';
				testboard1.push_back(num);
			}
		}
	}
	else {
		cout << "Not open";
	}
	inFile.close();

	inFile.open("boards/testboard2.brd");

	if (inFile.is_open())
	{
		int bit;
		while (getline(inFile, line)) {
			for (int i = 0; i < line.size(); i++) {
				int num = line[i] - '0';
				testboard2.push_back(num);
			}
		}
	}
	else {
		cout << "Not open";
	}
	inFile.close();

	inFile.open("boards/testboard3.brd");

	if (inFile.is_open())
	{
		int bit;
		while (getline(inFile, line)) {
			for (int i = 0; i < line.size(); i++) {
				int num = line[i] - '0';
				testboard3.push_back(num);
			}
		}
	}
	else {
		cout << "Not open";
	}
	inFile.close();

	//LOAD IMAGES

	//TILES
	staticIcons.emplace("tile_revealed", TextureManager::GetTexture("tile_revealed"));
	staticIcons.emplace("tile_hidden", TextureManager::GetTexture("tile_hidden"));

	//TESTS
	staticIcons.emplace("test_1", TextureManager::GetTexture("test_1"));
	staticIcons.emplace("test_2", TextureManager::GetTexture("test_2"));
	staticIcons.emplace("test_3", TextureManager::GetTexture("test_3"));

	//NUMBERS
	staticIcons.emplace("number_1", TextureManager::GetTexture("number_1"));
	staticIcons.emplace("number_2", TextureManager::GetTexture("number_2"));
	staticIcons.emplace("number_3", TextureManager::GetTexture("number_3"));
	staticIcons.emplace("number_4", TextureManager::GetTexture("number_4"));
	staticIcons.emplace("number_5", TextureManager::GetTexture("number_5"));
	staticIcons.emplace("number_6", TextureManager::GetTexture("number_6"));
	staticIcons.emplace("number_7", TextureManager::GetTexture("number_7"));
	staticIcons.emplace("number_8", TextureManager::GetTexture("number_8"));

	//MINE/FLAG
	staticIcons.emplace("flag", TextureManager::GetTexture("flag"));
	staticIcons.emplace("mine", TextureManager::GetTexture("mine"));


	//FACES
	staticIcons.emplace("face_win", TextureManager::GetTexture("face_win"));
	staticIcons.emplace("face_lose", TextureManager::GetTexture("face_win"));
	staticIcons.emplace("face_happy", TextureManager::GetTexture("face_happy"));

	//DIGITS
	staticIcons.emplace("digits", TextureManager::GetTexture("digits"));


	//DEBUG
	staticIcons.emplace("debug", TextureManager::GetTexture("debug"));

	//SET POSITION FOR STATIC ICONS

	//debug/TESTS   POSITION
	debug.setTexture(TextureManager::GetTexture("debug"));
	debug.setPosition((Width - (64 * 4)), (this->Height - 88));

	test1.setTexture(TextureManager::GetTexture("test_1"));
	test1.setPosition((Width - (64 * 3)), (this->Height - 88));

	test2.setTexture(TextureManager::GetTexture("test_2"));
	test2.setPosition((Width - (64 * 2)), (this->Height - 88));

	test3.setTexture(TextureManager::GetTexture("test_3"));
	test3.setPosition((Width - (64 * 1)), (this->Height - 88));

	//FACE
	face.setTexture(TextureManager::GetTexture("face_happy"));
	face.setPosition(((Width/2) - (32)), (this->Height - 88));

	//Digits
	hundreds.setTexture(staticIcons["digits"]);
	tens.setTexture(staticIcons["digits"]);
	ones.setTexture(staticIcons["digits"]);
	neg.setTexture(staticIcons["digits"]);
	flagDigits();
	neg.setPosition(0, (this->Height - 88));
	hundreds.setPosition(21, (this->Height - 88));
	tens.setPosition(42, (this->Height - 88));
	ones.setPosition(63, (this->Height - 88));
	

	createTiles();
	smileyTiley();


}

//Create BOOL VECTOR WITH RANDOM VALS
void Board::smileyTiley() {
	ReadConfig();
	tileTorF.clear();
	int count = 0;
	vector<int>ranNums;
	vector<int>counted;
	int num;
	for (int i = 0; i < tileCount; i++) {
		counted.push_back(0);
	}
	while (count < numMine) {
		num = rand() % tileCount;

		if (counted.at(num) == 0) {
			counted.at(num) == 1;
			ranNums.push_back(num);
			count++;
		}
	}
	for (int i = 0; i < tileCount; i++) {
		tileTorF.push_back(false);
	}

	for (int i = 0; i < ranNums.size(); i++) {
		tileTorF.at(ranNums.at(i)) = true;
	}

	makeBombs();
	textureIcon();

	flags = numMine;
	flagDigits();
	revealed = 0;

	lost = false;
	over = false;

}

void Board::createTiles() {
	float x = 0;
	float y = 0;
	int rowTileNum = (this->Height - 88) / 32;
	int colomnTileNum = (this->Width) / 32;

	for (int i = 0; i < rowTileNum; i++) {
		for (int j = 0; j < colomnTileNum; j++) {
			Tile tile = Tile(staticIcons, x, y);
			tiles.push_back(tile);
			x += 32.0f;
		}
		x = 0;
		y += 32.0f;
	}
}

//FOR TEST CASES CREATE BOOL VECTOR
void Board::testTiles(vector<int>& bits) {
	
	tileTorF.clear();
	tileCount = bits.size();
	for (int i = 0; i < bits.size(); i++) {
		if (bits[i] == 0)
		{
			tileTorF.push_back(false);
		}
		else
		{
			tileTorF.push_back(true);
		}
	}
	
	makeBombs();

	textureIcon();
	int count = 0;
	for (int i = 0; i < bits.size(); i++) {
		if (bits.at(i) == 1) {
			count++;
		}
	}
	numMine = count;
	flags = numMine;
	
	flagDigits();
	
	revealed = 0;

	lost = false;
	over = false;
}

void Board::makeBombs() {
	for (int i = 0; i < tileCount; i++)
	{
		tiles[i].setBombState(tileTorF[i]);
	}
}

	void Board::textureIcon() {
	for (int i = 0; i < tileCount; i++) {
		//clear
		tiles[i].neighborTiles.clear();
		//initialize neighbors to nullptr
		for (int j = 0; j < 8; j++) {
			tiles[i].neighborTiles.push_back(nullptr);
		}
		if (i == 0) //top left corner 3 neighbors
		{
			tiles[i].neighborTiles[4] = &(tiles[i + 1]); //midright
			tiles[i].neighborTiles[6] = &(tiles[i + numCol]); //botmid
			tiles[i].neighborTiles[7] = &(tiles[i + (numCol + 1)]); //botright

		}
		else if (i == (numCol - 1)) // top right corner has three neigbors
		{
			tiles[i].neighborTiles[5] = &(tiles[i + (numCol-1)]); //botleft
			tiles[i].neighborTiles[6] = &(tiles[i + numCol]); //botmid
			tiles[i].neighborTiles[3] = &(tiles[i - 1]); //midleft
		}
		else if (i == (tileCount - numCol)) //bot left has 3 neighbors
		{
			tiles[i].neighborTiles[1] = &(tiles[i - numCol]); //topmid
			tiles[i].neighborTiles[2] = &(tiles[i - (numCol - 1)]); //topright
			tiles[i].neighborTiles[4] = &(tiles[i + 1]); //midright
		}
		else if (i == (tileCount - 1)) //bot right has 3 neighbors
		{
			tiles[i].neighborTiles[1] = &(tiles[i - numCol]); //topmid
			tiles[i].neighborTiles[0] = &(tiles[i - (numCol + 1)]); //topleft
			tiles[i].neighborTiles[3] = &(tiles[i - 1]); //midleft
		}
		else if (i < numCol - 1) //top row tiles have 5 neighbors 
		{
			tiles[i].neighborTiles[3] = &(tiles[i - 1]); //midleft
			tiles[i].neighborTiles[4] = &(tiles[i + 1]); //midright
			tiles[i].neighborTiles[5] = &(tiles[i + (numCol - 1)]); //botleft
			tiles[i].neighborTiles[6] = &(tiles[i + numCol]); //botmid
			tiles[i].neighborTiles[7] = &(tiles[i + (numCol + 1)]); //botright
		}
		else if (i> (tileCount - numCol)) //bot row tiles have 5 neighbors
		{
			tiles[i].neighborTiles[0] = &(tiles[i - (numCol + 1)]); //topleft
			tiles[i].neighborTiles[1] = &(tiles[i - numCol]); //topmid
			tiles[i].neighborTiles[2] = &(tiles[i - (numCol - 1)]); //topright
			tiles[i].neighborTiles[3] = &(tiles[i - 1]); //midleft
			tiles[i].neighborTiles[4] = &(tiles[i + 1]); //midright
		}
		else if (i % numCol == 0) //tile on left edge has 5 neighbors
		{
			tiles[i].neighborTiles[2] = &(tiles[i - (numCol - 1)]); //topright
			tiles[i].neighborTiles[1] = &(tiles[i - numCol]); //topmid
			tiles[i].neighborTiles[4] = &(tiles[i + 1]); //midright
			tiles[i].neighborTiles[6] = &(tiles[i + numCol]); //botmid
			tiles[i].neighborTiles[7] = &(tiles[i + (numCol + 1)]); //botright
		}
		else if (((i - (numCol-1)) % numCol) == 0) //tile on right edge
		{
			tiles[i].neighborTiles[0] = &(tiles[i - (numCol + 1)]); //topleft
			tiles[i].neighborTiles[1] = &(tiles[i - numCol]); //topmid
			tiles[i].neighborTiles[3] = &(tiles[i - 1]); //midleft
			tiles[i].neighborTiles[6] = &(tiles[i + numCol]); //botmid
			tiles[i].neighborTiles[5] = &(tiles[i + (numCol - 1)]); //botleft
		}
		else //Tile in middle 
		{
			tiles[i].neighborTiles[0] = &(tiles[i - (numCol + 1)]); //topleft
			tiles[i].neighborTiles[1] = &(tiles[i - numCol]); //topmid
			tiles[i].neighborTiles[2] = &(tiles[i - (numCol - 1)]); //topright
			tiles[i].neighborTiles[3] = &(tiles[i - 1]); //midleft
			tiles[i].neighborTiles[4] = &(tiles[i + 1]); //midright
			tiles[i].neighborTiles[5] = &(tiles[i + (numCol - 1)]); //botleft
			tiles[i].neighborTiles[6] = &(tiles[i + numCol]); //botmid
			tiles[i].neighborTiles[7] = &(tiles[i + (numCol+1)]); //botright
		}
		tiles[i].iconUpdate(staticIcons);
		
	}
}
	

//GETTERS
int Board::getWidth() {
	return this->Width;
}
int Board::getHeight() {
	return this->Height;
}
int Board::getnumMine() {
	cout << flags << endl;
	return this->numMine;
}
int Board::getTileCount() {
	return this->tileCount;
}

void Board::flagDigits() {
	int temp = flags;
	if (temp < 0) {
		temp *= -1;
	}
	int ones1 = temp % 10;
	int tens1 = (temp % 100) / 10;
	int hunds1 = temp / 100;
	if (temp == 0) {
		int ones1 = temp % 10;
		int tens1 = (temp % 100) / 10;
		int hunds1 = temp / 100;
	}

	neg.setTextureRect(Rect<int>(21 * 10, 0, 21, 32));
	hundreds.setTextureRect(Rect<int>(21 * hunds1, 0, 21, 32));
	tens.setTextureRect(Rect<int>(21 * tens1, 0, 21, 32));
	ones.setTextureRect(Rect<int>(21 * ones1, 0, 21, 32));
	neg.setColor(Color(255, 255, 255, 0));
	if (flags < 0) {
		neg.setColor(Color(255, 255, 255, 255));
	}
}

void Board::refresh(RenderWindow& window) {

	if (Mouse::isButtonPressed(Mouse::Left) ) {
		Vector2i pos = Mouse::getPosition(window);
		if (pos.y >= 0 && pos.y < (Height - 88) && over == false) { //mouse clicks on board
			if (pos.x >= 0 && pos.x <= Width) {
				int tilexPos = (pos.x / 32);
				int tileyPos = (pos.y / 32);

				int index = (tileyPos * numCol) + tilexPos;
				int count = 0; //for tiles revealed count
				//If tile is bomb lose game
				if (tiles[index].reveal(count)) { //reveals all tiles if bomb if not count is updated recursively for tile reveal
					lost = true;
					over = true;
					int temp = 0; //for revealing bombs
					for (int i = 0; i < tileCount; i++) {
						 if (tiles[i].isBomb) {  //if TIle is bomb show bomb
							tiles[i].reveal(temp); 
						}
					}
				}
				else {
					revealed += count;
				}
			}
		}
		//FOR MENU OPTIONS AT THE BOTTOM
		else if (pos.y >= (this->Height - 88) && pos.y < (this->Height + 64)) {
			if (pos.x >= ((Width / 2) - (32)) && pos.x < ((Width / 2) + (32))) {
				smileyTiley();
			}
			if (pos.x >= (Width - (64 * 4)) && pos.x < ((Width - (64 * 4))+64)) {
				if (lost || over) {

				}
				else {
					debugRun();
				}
			}
			if (pos.x >= (Width - (64 * 3)) && pos.x < ((Width - (64 * 3)) + 64)) {
				testTiles(testboard1);
				
			}
			if (pos.x >= (Width - (64 * 2)) && pos.x < ((Width - (64 * 2)) + 64)) {
				testTiles(testboard2);
			}
			if (pos.x >= (Width - (64 * 1)) && pos.x <= ((Width - (64 * 1)) + 64)) {
				testTiles(testboard3);
			}
		}
	}

	if (Mouse::isButtonPressed(Mouse::Right)) {
		Vector2i pos = Mouse::getPosition(window);
		if (pos.y >= 0 && pos.y < (Height - 88) && over == false) {
			if (pos.y >= 0 && pos.y <= (Height - 88)) {
				int tilexPos = (pos.x / 32);
				int tileyPos = (pos.y / 32);

				int index = (tileyPos * numCol) + tilexPos;
				if (tiles[index].isFlag == false && tiles[index].isReveal == false) {
					tiles[index].flagShow();
					flags--;
				}
				else if (tiles[index].isFlag == true && tiles[index].isReveal == false) {
					tiles[index].flagShow();
					flags++;
				}
				flagDigits();
			}

		}
	}
	if (revealed == (tileCount - numMine) && lost == false) {
		over = true;
		for (int i = 0; i < tileCount; i++) {
			if (tiles[i].isBomb == true && tiles[i].isFlag == false)
			{
				tiles[i].flagShow();
			}
		}
	}
	faceUpdate();
	draw(window);
}

void Board::draw(RenderWindow& window) {
	for (int c = 0; c < tileCount; c++)
		tiles[c].drawTile(window);

	window.draw(face);
	window.draw(debug);
	window.draw(test1);
	window.draw(test2);
	window.draw(test3);

	window.draw(hundreds);
	window.draw(tens);
	window.draw(ones);
	window.draw(neg);
}

void Board::faceUpdate() {
	if (over) {
		if (lost) {
			face.setTexture(TextureManager::GetTexture("face_lose"));
		}else
			face.setTexture(TextureManager::GetTexture("face_win"));
	}
	else
		face.setTexture(TextureManager::GetTexture("face_happy"));
}

void Board::debugRun() {
	for (int i = 0; i < tileCount; i++)
	{
		tiles[i].debugShow();
	}
}