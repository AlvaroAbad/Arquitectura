#include "..\include\isometricmap.h"
#include "../include/image.h"
#include "../include/math.h"
#include "../lib/rapidxml.hpp"
#include <limits.h>

using namespace rapidxml;

IsometricMap::IsometricMap(const String & filename, uint16 firstColId) :Map(filename, firstColId)
{
	String mapInfo;
	xml_document<> doc;
	xml_node<>* root;
	String attr;
	xml_node<>* tileSet;
	xml_node<>* tileOffSet;
	xml_node<>* image;
	xml_node<>* data;
	xml_node<>* tile;

	uint32 firstGId, tileWidth, tileHeight, x, y, imageW, imageH;
	x = y = 0;

	double handleX, handleY;

	mapInfo = String::Read(filename);

	doc.parse<0>((char*)mapInfo.ToCString());
	root = doc.first_node("map");


	tileSet = root->first_node("tileset");
	attr = tileSet->first_attribute("firstgid")->value();
	firstGId = attr.ToInt();
	attr = tileSet->first_attribute("tilewidth")->value();
	tileWidth = attr.ToInt();
	attr = tileSet->first_attribute("tileheight")->value();
	tileHeight = attr.ToInt();
	tileOffSet = tileSet->first_node("tileoffset");
	if (tileOffSet) {
		attr = tileOffSet->first_attribute("x")->value();
		x = attr.ToInt();
		attr = tileOffSet->first_attribute("y")->value();
		y = attr.ToInt();
	}

	data = root->first_node("layer")->next_sibling("layer")->first_node("data");
	if (data->first_attribute("encoding")) {
		return;
	}
	tile = data->first_node("tile");
	while (tile)
	{
		attr = tile->first_attribute("gid")->value();
		this->topLayerIds.Add(attr.ToInt() - firstGId);
		tile = tile->next_sibling("tile");
	}

	handleX = GetImage()->GetHandleX();
	handleY = GetImage()->GetHandleY();

	handleX += GetTileWidth();
	handleY = GetImage()->GetHeight() - handleY - tileHeight;

	GetImage()->SetHandle(handleX, handleY);
}

void IsometricMap::GenerateLayerSprites(IsometricScene * scene)
{
	IsometricSprite * sprite;
	int32 id;
	for (uint32 column = 0; column < GetColumns(); column++)
	{
		for (uint32 row = 0; row < GetRows(); row++) {
			id = topLayerIds[row*GetColumns() + column];
			if (id >-1) {
				sprite = scene->CreateSprite(GetImage());
				sprite->SetCurrentFrame(id);
				sprite->SetPosition(column*GetTileHeight(), row*GetTileWidth(),0);
				if (id >= GetFirstColId()) {
					sprite->SetCollision(IsometricSprite::COLLISION_RECT);
				}
			}
		}

	}
}

void IsometricMap::Render() const
{
	double screenX, screenY;
	for (uint16 y = 0; y < GetRows(); y++) {
		for (uint16 x = 0; x < GetColumns(); x++) {
			if (GetTileId(x, y) >= 0) {
				TransformIsoCoords(x*GetTileWidth(), y*GetTileHeight(), 0, &screenX, &screenY);
				Renderer::Instance().DrawImage(GetImage(), screenX, screenY, GetTileId(x, y));
			}
		}
	}
}
