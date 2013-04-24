#include "tile.h"

tile::~tile(){

}

tile::tile(){
	visible = false;
	traversable = false; 
	pos = vector3f(-1,-1,-1);
}

// Creates a tile with map coordinates and world coordinates
// Has a rendering colour and picking colour for colour picking
// Can be set to be visible or not
// Can be set to traversable or not
// Created with given radius
tile::tile(vector3f a, vector3f b, colour c, colour d, bool v, bool t, float radius){
	pos         = vector3f(a.x, a.y, a.z);
	wpos        = vector3f(b.x, b.y, b.z);
	col.r       = c.r;
	col.g       = c.g;
	col.b       = c.b;
	col.o       = c.o;
	pick.r      = d.r;
	pick.g      = d.g;
	pick.b      = d.b;
	pick.o      = d.o;
	visible     = t;
	traversable = v;

	float degree = 360;

	for (int i = 0; i < 6; i++){
		p[i].x = wpos.x + radius * cos(to_rad(degree));
		p[i].y = 0;
		p[i].z = wpos.z + radius * sin(to_rad(degree));

		degree -= 60;
	}
}

// Draws the tile
void tile::display(){
	// glColor4ub(col.r, col.g, col.b, col.o);
	// glBegin(GL_POLYGON);
	// 	glNormal3f(0,1,0);
	// 	for (int i = 0; i < 6; i++)
	// 		glVertex3f(p[i].x, p[i].y, p[i].z);
	// glEnd();

	glLineWidth(2);
	glColor4ub(25, 25, 25, 255);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_LOOP);
		//glNormal3f(0,1,0);
		for (int i = 0; i < 6; ++i)
			glVertex3f(p[i].x, p[i].y, p[i].z);
	glEnd();
	glEnable(GL_LIGHTING);
}

// Draws the tile with its picking colour
void tile::display_pick(){
	glColor4ub(pick.r, pick.g, pick.b, pick.o);
	glBegin(GL_POLYGON);
		glNormal3f(0,1,0);
		for (int i = 0; i < 6; ++i)
			glVertex3f(p[i].x, p[i].y, p[i].z);
	glEnd();
}

// Calculates the Euclidean distance between two tiles
int tile::distance(tile i){
	int d1 = abs(i.pos.x - pos.x);
	int d2 = abs(i.pos.y - pos.y);
	int d3 = abs(i.pos.z - pos.z);

	if( d1 >= d2)
		if( d1 >= d3 )
			return d1;
	if( d2 >= d1 )
		if( d2 >= d3 )
			return d2;
	return d3;
}

// Calculates the Euclidean distance between two tiles
int tile::distance(vector3f i){
	int d1 = abs(i.x - pos.x);
	int d2 = abs(i.y - pos.y);
	int d3 = abs(i.z - pos.z);

	if( d1 >= d2)
		if( d1 >= d3 )
			return d1;
	if( d2 >= d1 )
		if( d2 >= d3 )
			return d2;
	return d3;
}

// Calculates the Euclidean distance between two tiles
int tile::distance(tile i, tile j){
	int d1 = abs(i.pos.x - j.pos.x);
	int d2 = abs(i.pos.y - j.pos.y);
	int d3 = abs(i.pos.z - j.pos.z);

	if( d1 >= d2)
		if( d1 >= d3 )
			return d1;
	if( d2 >= d1 )
		if( d2 >= d3 )
			return d2;
	return d3;
}

// Comparison overloaders
bool tile::operator==(const tile& rhs) const
{
	return pos == rhs.pos;
}

bool tile::operator!=(const tile& rhs) const
{
	return pos != rhs.pos;
}