class Grid {
	void setUp();
public:
	// attributes
	vector<vector<Tile*>> tiles; // "Matrix" of pointer objects
	int Length; // number of segments on one side ie. 4x4 has Length 4
	int tileSize; // for passing to new Tile objects
	int tileStartStage; //for passing to new Tile objects

	bool canLeft  = true;
	bool canRight = true;
	bool canUp    = true;
	bool canDown  = true;

	// methods
	// constructor initializes arguments
	// calls the setUp method
	// spawns 3 new Tiles
	Grid(int len, int size, int start);
	// spawns the tile in available space
	void spawnNew();

	// for debugging purposes only!
	void show();
	// moves the tiles
	void left();
	void right();
	void up();
	void down();
	// checks for game over
	bool gameOver();
	// resets gameOver conditions
	void resetConditions();
	void resetGrid();
};

void Grid::setUp() {
	vector<Tile*> temp;
	for (int i = 0; i < Length; i++) {
		temp.push_back(nullptr);
	}
	for (int i = 0; i < Length; i++) {
		tiles.push_back(temp);
	}
}

Grid::Grid(int len, int size, int start) {
	Length = len;
	tileSize = size;
	tileStartStage = start;
	setUp();
	spawnNew();
	spawnNew();
	spawnNew();
}

void Grid::spawnNew() {
	int x;
	int y;
	while (true) {
		x = rand() % 4;
		y = rand() % 4;
		if (tiles[x][y] == nullptr) {
			tiles[x][y] = new Tile(tileSize,tileStartStage);
			tiles[x][y]->setPosition(y*tileSize,x*tileSize);
			break;
		}
	}
}

void Grid::show() {
	for (int i = 0; i < Length; i++) {
		for (int j = 0; j < Length; j++) {
			if (tiles[i][j] != nullptr) {
				cout << tiles[i][j]->currentStage << " ";
			} else {
				cout << -1 << " ";
			}
		}
		cout << endl;
	}
}

void Grid::left() {
	bool done = false;
	int count = 0;
	while(!done) {
		done = true;
		for (int i = 0; i < Length; i++) {
			for (int k = 1; k < Length; k++) {
				if (tiles[i][k] != nullptr && tiles[i][k-1] == nullptr) {
					tiles[i][k]->move(-tileSize,0);
					tiles[i][k-1] = tiles[i][k];
					tiles[i][k] = nullptr;
					done = false;
					count++;
				} else if (tiles[i][k] != nullptr && tiles[i][k-1] != nullptr) {
					if (tiles[i][k]->currentStage == tiles[i][k-1]->currentStage) {
						delete tiles[i][k-1];
						tiles[i][k-1] = nullptr;
						tiles[i][k-1] = tiles[i][k];
						tiles[i][k] = nullptr;
						tiles[i][k-1]->move(-tileSize,0);
						tiles[i][k-1]->upgrade();
						done = false;
						count++;
					}
				}
			}
		}
	}
	if (count) {
		resetConditions();
		spawnNew();
	} else {
		canLeft = false;
	}
}

void Grid::right() {
	bool done = false;
	int count = 0;
	while(!done) {
		done = true;
		for (int i = 0; i < Length; i++) {
			for (int k = 0; k < Length-1; k++) {
				if (tiles[i][k] != nullptr && tiles[i][k+1] == nullptr) {
					tiles[i][k]->move(tileSize,0);
					tiles[i][k+1] = tiles[i][k];
					tiles[i][k] = nullptr;
					done = false;
					count++;
				} else if (tiles[i][k] != nullptr && tiles[i][k+1] != nullptr) {
					if (tiles[i][k]->currentStage == tiles[i][k+1]->currentStage) {
						delete tiles[i][k+1];
						tiles[i][k+1] = nullptr;
						tiles[i][k+1] = tiles[i][k];
						tiles[i][k] = nullptr;
						tiles[i][k+1]->move(tileSize,0);
						tiles[i][k+1]->upgrade();
						done = false;
						count++;
					}
				}
			}
		}
	}
	if (count) {
		resetConditions();
		spawnNew();
	} else {
		canRight = false;
	}
}

void Grid::up() {
	bool done = false;
	int count = 0;
	while(!done) {
		done = true;
		for (int i = 1; i < Length; i++) {
			for (int k = 0; k < Length; k++) {
				if (tiles[i][k] != nullptr && tiles[i-1][k] == nullptr) {
					tiles[i][k]->move(0,-tileSize);
					tiles[i-1][k] = tiles[i][k];
					tiles[i][k] = nullptr;
					done = false;
					count++;
				} else if (tiles[i][k] != nullptr && tiles[i-1][k] != nullptr) {
					if (tiles[i][k]->currentStage == tiles[i-1][k]->currentStage) {
						delete tiles[i-1][k];
						tiles[i-1][k] = nullptr;
						tiles[i-1][k] = tiles[i][k];
						tiles[i][k] = nullptr;
						tiles[i-1][k]->move(0,-tileSize);
						tiles[i-1][k]->upgrade();
						done = false;
						count++;
					}
				}
			}
		}
	}
	if (count) {
		resetConditions();
		spawnNew();
	} else {
		canUp = false;
	}
}

void Grid::down() {
	bool done = false;
	int count = 0;
	while(!done) {
		done = true;
		for (int i = 0; i < Length-1; i++) {
			for (int k = 0; k < Length; k++) {
				if (tiles[i][k] != nullptr && tiles[i+1][k] == nullptr) {
					tiles[i][k]->move(0,tileSize);
					tiles[i+1][k] = tiles[i][k];
					tiles[i][k] = nullptr;
					done = false;
					count++;
				} else if (tiles[i][k] != nullptr && tiles[i+1][k] != nullptr) {
					if (tiles[i][k]->currentStage == tiles[i+1][k]->currentStage) {
						delete tiles[i+1][k];
						tiles[i+1][k] = nullptr;
						tiles[i+1][k] = tiles[i][k];
						tiles[i][k] = nullptr;
						tiles[i+1][k]->move(0,tileSize);
						tiles[i+1][k]->upgrade();
						done = false;
						count++;
					}
				}
			}
		}
	}
	if (count) {
		resetConditions();
		spawnNew();
	} else {
		canDown = false;
	}
}

bool Grid::gameOver() {
	if (!canLeft && !canRight && !canUp && !canDown) {
		return true;
	} else {
		return false;
	}
}

void Grid::resetConditions() {
		canLeft  = true;
		canRight = true;
		canUp    = true;
		canDown  = true;
	}

void Grid::resetGrid() {
	for (int i = 0; i < Length; i++) {
		for (int k = 0; k < Length; k++) {
			if (tiles[i][k] != nullptr) {
				delete tiles[i][k];
				tiles[i][k] = nullptr;
			}
		}
	}
	resetConditions();
	spawnNew();
	spawnNew();
	spawnNew();
}