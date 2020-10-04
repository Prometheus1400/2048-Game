class Tile: public sf::Sprite {
public:
	// texture object
	sf::Texture textureTile;
	// possible textures
	vector<string> stages = 
	{"pieces/2.png","pieces/4.png","pieces/8.png","pieces/16.png","pieces/32.png",
     "pieces/64.png","pieces/128.png","pieces/256.png","pieces/512.png",
     "pieces/1024.png","pieces/2048.png","pieces/4096.png","pieces/8192.png"};
	// indicated the current stage of the tile
	// EX. 0->2,1->2,2->4 ...
	int currentStage;
	// constructor, loads texture of stage and sets correct
	// size of tile
	Tile (int desiredSize, int stage);
	// updates the tile to the next stage
	void upgrade();
};


Tile::Tile(int desiredSize, int stage) {
		float scale = desiredSize / 100.0f; // 100 is original size of tiles
		currentStage = stage;
		if (!textureTile.loadFromFile(stages[currentStage])){
			throw std::invalid_argument("Texture not loaded");
		}
		textureTile.setSmooth(true); // smooths the texture
		setTexture(textureTile); // sets the texture of current tile
		setScale(scale,scale); //sets the correct scale
	}

void Tile::upgrade() {
	currentStage++;
	if (!textureTile.loadFromFile(stages[currentStage])){
		throw std::invalid_argument("Texture not loaded");
	}
	setTexture(textureTile);
}
