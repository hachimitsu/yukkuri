#include "Map.h"

Map::~Map(){ 
	for (int i = 0; i < 12; i++){
		delete [] layout[i];
	}
	delete [] layout;
}

Map::Map(){

}

void Map::init(int _width, int _length){
	width = _width;
	length = _length;

	layout = new tile*[length];
	for (int i = 0; i < length; ++i){
		layout[i] = new tile[width];
	}
	const float radius = 1;
	const float offsety = sqrt(radius*radius - radius/2*radius/2);
	const float offsetx = (radius * 2) * 0.75;

	vector3f wpos(-(width * radius * 2 * 0.75 + radius * 2 * 0.25)/2.0f, 0, -(length * offsetx * 2 + offsety)/2.0f);
	vector3f pos(0,0,0);

	colour c[1], p;

	set_colour(c[0],0,0,0,255);

	for (int i = 0; i < length; i++){
		wpos.z = -(length * offsety * 2 + offsety)/2.0f + i*offsety*2;
		wpos.x = -(width * radius * 2 * 0.75 + radius * 2 * 0.25)/2.0f;
		pos.x = 0;
		pos.y = i;
		pos.z = -i;
		for (int j = 0; j < width; j++){
			layout[i][j] = tile(pos, wpos, c[0], p, true, true, radius);

			if( p.r < 255 )
				p.r += 1;
			else if( p.g < 255 )
				p.g += 1;
			else
				p.b += 1;

			pos.x++;
			if( j%2 == 1 ){
				pos.y--;
				wpos.z -= offsety;
			}
			else
				wpos.z += offsety;
			pos.z = -(pos.x + pos.y);
			wpos.x += offsetx;
		}
	}
}


void Map::update(){

}

void Map::display(vector3f camera){
	static GLuint index;

	if( !index ){
		index = glGenLists(1);
		glNewList(index,GL_COMPILE);
		for (int i = 0; i < length; ++i){
			for (int j = 0; j < width; ++j){
				if( layout[i][j].is_visible() )
					layout[i][j].display();
			}
		}
		glEndList();
	}

	glCallList(index);
}

void Map::display_pick(){
	static GLuint index;

	if( !index ){
		index = glGenLists(1);
		glNewList(index,GL_COMPILE);
		for (int i = 0; i < length; ++i){
			for (int j = 0; j < width; ++j){
				if( layout[i][j].is_visible() )
					layout[i][j].display_pick();
			}
		}
		glEndList();
	}

	glCallList(index);
}

void Map::flip_traversable(vector3f v){
	int x = v.x;
	int y = v.y + floor(x/2.0f);
	layout[y][x].flip_traversable();
}

tile Map::get_tile(colour c){
	for (int i = 0; i < length; ++i){
		for (int j = 0; j < width; ++j){
			colour t = layout[i][j].get_pick_colour();
			if( c.r == t.r && c.g == t.g && c.b == t.b )
				return layout[i][j];
		}
	}
	return tile();
}

tile Map::get_tile(vector3f v){
	int x = v.x;
	int y = v.y + floor(x/2.0f);

	return layout[y][x];
}

tile Map::get_tile(int x, int y){
	return layout[y][x];
}

std::vector<tile> Map::generate_area(tile t, int radius){
	std::vector<tile> v;
	for (int i = 0; i < length; i++){
		for (int j = 0; j < width; j++){
			if( layout[i][j] != t && t.distance(layout[i][j]) <= radius && traversable(t, layout[i][j], radius) )
				v.push_back(layout[i][j]);
		}
	}

	return v;
}

bool Map::traversable(tile o, tile t, int depth){
	std::vector<tile> path = generate_path(o,t,depth);

	if( path.size() > 0 )
		return true;

	return false;
}

std::vector<tile> Map::generate_path(tile o, tile t, int depth){
	std::vector<Node*> open,closed,children;
	std::vector<tile> path;
	bool found = false;
	Node *n = new Node;
	n->t = o;
	n->c = t.distance(o);
	n->n = NULL;
	n->s = 0;
	open.push_back(n);

	while( open.size() > 0 ){
		n = open[0];

		if( n->c == 0 ){
			found = true;
			break;
		}
				
		if( n->s < depth )		
			children = expand(n,t);
		closed.push_back(n);
		open.erase(open.begin());

		for (int i = 0; i < children.size(); ++i){
			if( exists( closed, children[i]) )
				continue;
			if( !exists( open, children[i]) )
				open.push_back( children[i] );
		}

		sort(open);
		children.clear();
	}

	if( found ){
		while( n ){
			path.push_back(n->t);
			n = n->n;
		}
	}

	return path;
}

std::vector<Node*> Map::expand(Node *t, tile g){
	std::vector<Node*> v;
	int x = t->t.get_pos().x;
	int y = t->t.get_pos().y + floor(x/2.0f);

	if( y-1 > -1 && layout[y-1][x].is_traversable() ){
		Node *n = new Node;
		n->t = layout[y-1][x];
		n->c = g.distance(layout[y-1][x]);
		n->s = t->s + 1;
		n->n = t;
		v.push_back( n );
	}
	if( y+1 < length && layout[y+1][x].is_traversable() ){
		Node *n = new Node;
		n->t = layout[y+1][x];
		n->c = g.distance(layout[y+1][x]);
		n->s = t->s + 1;
		n->n = t;
		v.push_back( n );
	}
	if( x-1 > -1 && layout[y][x-1].is_traversable() ){
		Node *n = new Node;
		n->t = layout[y][x-1];
		n->c = g.distance(layout[y][x-1]);
		n->s = t->s + 1;
		n->n = t;
		v.push_back( n );
	}
	if( x+1 < width && layout[y][x+1].is_traversable() ){
		Node *n = new Node;
		n->t = layout[y][x+1];
		n->c = g.distance(layout[y][x+1]);
		n->s = t->s + 1;
		n->n = t;
		v.push_back( n );
	}

	if( x%2 == 0 ){
		if( x-1 > -1 && y-1 > -1 && layout[y-1][x-1].is_traversable() ){
			Node *n = new Node;
			n->t = layout[y-1][x-1];
			n->c = g.distance(layout[y-1][x-1]);
			n->s = t->s + 1;
			n->n = t;
			v.push_back( n );
		}
		if( x+1 < width && y-1 > -1 && layout[y-1][x+1].is_traversable() ){
			Node *n = new Node;
			n->t = layout[y-1][x+1];
			n->c = g.distance(layout[y-1][x+1]);
			n->s = t->s + 1;
			n->n = t;
			v.push_back( n );
		}
	}
	else{
		if( x-1 > -1 && y+1 < length && layout[y+1][x-1].is_traversable() ){
			Node *n = new Node;
			n->t = layout[y+1][x-1];
			n->c = g.distance(layout[y+1][x-1]);
			n->s = t->s + 1;
			n->n = t;
			v.push_back( n );
		}
		if( x+1 < width && y+1 < length && layout[y+1][x+1].is_traversable() ){
			Node *n = new Node;
			n->t = layout[y+1][x+1];
			n->c = g.distance(layout[y+1][x+1]);
			n->s = t->s + 1;
			n->n = t;
			v.push_back( n );
		}
	}

	return v;
}

bool Map::exists(std::vector<Node*> l, Node *n){
	for (int i = 0; i < l.size(); ++i){
		if ( l[i]->t == n->t ){
			return true;
		}
	}
	return false;
}

void Map::sort(std::vector<Node*> &t){
	int size = t.size();

	for (int i = 1; i < size; ++i){
		int pos = i;
		Node *val = t[i];
		while( pos > 0 && val->c < t[pos-1]->c ){
			t[pos] = t[pos-1];
			pos--;
		}
		t[pos] = val;
	}
}