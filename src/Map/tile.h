#pragma once
#include "../Math/Maths.h"
#include <SDL/SDL_opengl.h>

class tile
{
private:
	vector3f pos;
	vector3f wpos;
	colour col, pick;
	vector3f p[6];
	bool visible,traversable;
	GLuint index;

public:tile();
	tile(vector3f, vector3f, colour, colour, bool, bool, float);
	~tile();
	void display();
	void display_pick();

	void flip_traversable(){ traversable = !traversable; };
	
	vector3f get_pos(){
		return pos;
	};

	vector3f get_wpos(){
		return wpos;
	};

	colour get_pick_colour(){
		return pick;
	};

	colour get_colour(){
		return col;
	};

	bool is_traversable(){
		return traversable;
	};

	bool is_visible(){
		return visible;
	};

	int distance(tile);
	int distance(tile,tile);
	int distance(vector3f);

	bool operator==(const tile&) const;
	bool operator!=(const tile&) const;
};