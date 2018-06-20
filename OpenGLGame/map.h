
#ifndef MAP_H
#define MAP_H

enum Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

enum MapTiles
{
	PATH = 0,
	WALL = 1
};

class Map
{
public:
	Map(char height, char width);
	~Map();

	char getHeight();
	char getWidth();
	
	void loadMap(char ** map);

	bool checkNextDir(int x, int y, Direction dir);

private:

	char height = 0;
	char width = 0;

	char ** map;

};

#endif // !MAP_H

