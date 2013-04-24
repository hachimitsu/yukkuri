#include "../Math/Maths.h"
#include "node.h"
#include <SDL/SDL_opengl.h>

class Map
{
private:
	int width, length;
	tile **layout;

	bool compare_colour(colour,colour);
	std::vector<Node*> expand(Node*,tile);
	void sort(std::vector<Node*>&);
	bool exists(std::vector<Node*>, Node *);

public:
	Map();
	~Map();

	void init(int,int);
	void update();
	void display(vector3f);
	void display_pick();
	tile get_tile(colour);
	tile get_tile(vector3f);
	tile get_tile(int,int);
	void flip_traversable(vector3f);
	std::vector<tile> generate_area(tile,int);
	bool traversable(tile, tile, int);
	std::vector<tile> generate_path(tile,tile,int);
};