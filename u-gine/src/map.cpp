#include "../include/map.h"
#include "../include/rectcollision.h"
#include "../include/collision.h"
#include "../include/image.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/string.h"
#include "../lib/rapidxml.hpp"
#include <limits.h>

using namespace rapidxml;

Map::Map(const String &filename, uint16 firstColId) {
	String mapInfo;
	xml_document<> doc;
	xml_node<>* root;
	String attr;
	xml_node<>* tileSet;
	xml_node<>* tileOffSet;
	xml_node<>* image;
	xml_node<>* data;
	xml_node<>* tile;

	uint32 firstGId, tileWidth, tileHeight,x,y,imageW,imageH;
	x = y = 0;

	// TAREA: Implementar constructor
	this->filename = filename;
	this->firstColId = firstColId;
	this->valid = false;
	mapInfo = String::Read(filename);
	
	doc.parse<0>((char*)mapInfo.ToCString());
	root = doc.first_node("map");
	

	attr=root->first_attribute("width")->value();
	this->width = attr.ToInt();
	attr = root->first_attribute("height")->value();
	this->height = attr.ToInt();
	attr = root->first_attribute("tilewidth")->value();
	this->tileWidth = attr.ToInt();
	attr = root->first_attribute("tileheight")->value();
	this->tileHeight = attr.ToInt();
	
	tileSet = root->first_node("tileset");
	attr = tileSet->first_attribute("firstgid")->value();
	firstGId = attr.ToInt();
	attr = tileSet->first_attribute("tilewidth")->value();
	tileWidth = attr.ToInt();
	attr = tileSet->first_attribute("tileheight")->value();
	tileHeight = attr.ToInt();
	tileOffSet= tileSet->first_node("tileoffset");
	if (tileOffSet) {
		attr = tileOffSet->first_attribute("x")->value();
		x = attr.ToInt();
		attr = tileOffSet->first_attribute("y")->value();
		y = attr.ToInt();
	}
	image= tileSet->first_node("image");
	attr = image->first_attribute("source")->value();
	this->imageFile = attr.StripDir();
	attr = image->first_attribute("height")->value();
	imageH = attr.ToInt();
	attr = image->first_attribute("width")->value();
	imageW = attr.ToInt();

	data = root->first_node("layer")->first_node("data");
	if (data->first_attribute("encoding")) {
		return;
	}
	tile = data->first_node("tile");
	while (tile)
	{
		attr = tile->first_attribute("gid")->value();
		this->tileIds.Add(attr.ToInt() - firstGId);
		tile = tile->next_sibling("tile");
	}
	this->image=ResourceManager::Instance().LoadImage(filename.ExtractDir()+"/"+ this->imageFile, imageW / tileWidth, imageH / tileHeight);
	if (!this->image) {
		return;
	}
	this->image->SetHandle(x, y);
	this->valid = true;
}

void Map::Render() const {
	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( GetTileId(x, y) >= 0 ) {
				Renderer::Instance().DrawImage(image, x*GetTileWidth(), y*GetTileHeight(), GetTileId(x, y));
			}
		}
	}
}

bool Map::CheckCollision(const Collision* collision) const {
	// Creamos caja de colisiones
	double boxX = 0, boxY = 0, boxWidth = GetTileWidth(), boxHeight = GetTileHeight();
	RectCollision boxCol(&boxX, &boxY, &boxWidth, &boxHeight);
	
	// Comprobamos colision con cada tile
	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( GetTileId(x, y) >= firstColId ) {
				boxX = x * GetTileWidth();
				boxY = y * GetTileHeight();

				if ( collision->DoesCollide(&boxCol) )
					return true;
			}
		}
	}

	return false;
}

double Map::GetGroundY(double x, double y) const {
	double groundY = UINT_MAX;

	if ( x < 0  ||  x >= width*tileWidth  ||  y >= height*tileHeight ) return groundY;
	if ( y < 0 ) y = 0;

	// Buscamos el primer tile en esa columna
	for ( int tiley = int(y/tileHeight); tiley < height; tiley++ ) {
		if ( tileIds[tiley*width + int(x/tileWidth)] >= 0 ) {
			groundY = tiley*tileHeight;
			break;
		}
	}
	return groundY;
}
