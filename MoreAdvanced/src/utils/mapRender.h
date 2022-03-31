static enum MapState {W_DOWN = 0, W_UP = 1, W_RIGHT = 2,  W_LEFT = 3};

void moveLevel(unsigned char direction);
void moveLevelX(unsigned char direction, int minX, int maxX);
void moveLevelY(unsigned char direction, int minY, int maxY);