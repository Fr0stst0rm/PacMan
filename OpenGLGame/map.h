
#ifndef MAP_H
#define MAP_H

class Map
{
public:
	Map(char height, char width);
	~Map();

	char getHeight();
	char getWidth();
	
	void loadMap(char * map);


private:

	char height = 0;
	char width = 0;

	char * map;

};

#endif // !MAP_H

