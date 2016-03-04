#ifndef WORLDDEFENDERS_MESSAGES_H
#define WORLDDEFENDERS_MESSAGES_H
#include "enumentitytype.h"
class Collision;
class Entity;
class Sprite;
struct Message {
	enum msgType {
		MSGMOVE,
		MSGGETENTITYSTATE,
		MSGROTATE,
		MSGSCALE,
		MSGSPOS,
		MSGSROT,
		MSGSSCALE,
		MSGFIRE,
		MSGGFIREVECTOR,
		MSGCFIRECOL,
		MSGCCOL,
		MSGGCOL,
		MSGSCOL,
		MSGGTYPE, 
		MSGGSPRITE,
		MSGSSPRITESCALE
	};
	msgType type;
};
struct MessageGetEntityState : public Message {
	MessageGetEntityState() {
		type = MSGGETENTITYSTATE;
	}
	double o_x, o_y, o_z, o_rot, o_width, o_height;
};
struct MessageSetPos : public Message {
	MessageSetPos(double x, double y, double z):x(x),y(y),z(z) {
		type = MSGSPOS;
	}
	double x, y, z;
};
struct MessageSetRotation : public Message {
	MessageSetRotation() {
		type = MSGSROT;
	}
	double rot;
};
struct MessageSetScale : public Message {
	MessageSetScale(double width, double height):width(width), height(height){
		type = MSGSSCALE;
	}
	double width, height;
};
struct MessageMove : public Message {
	enum direction {
		DIRNULL,
		DIRUP,
		DIRDOWN,
		DIRLEFT,
		DIRRIGHT
	};
	MessageMove() {
		type = MSGMOVE;
	}
	direction Vertical, Horizontal;
};
struct MessageFire : public Message {
	MessageFire(double targetX, double targetY):targetX(targetX), targetY(targetY){
		type = MSGFIRE;
	}
	double targetX, targetY;
};
struct MessageGetFiringVector : public Message {
	MessageGetFiringVector() {
		type = MSGGFIREVECTOR;
	}
	bool o_firing;
	double o_originX, o_originY, o_targetX, o_targetY;
};
struct MessageCheckFireCollision : public Message {
	MessageCheckFireCollision(double originX, double originY, double targetX, double targetY)
	:originX(originX), originY(originY), targetX(targetX), targetY(targetY){
		type = MSGCFIRECOL;
	}
	bool collision;
	double originX, originY, targetX, targetY;
};
struct MessageCheckCollision : public Message {
	MessageCheckCollision(){
		type = MSGCCOL;
	}
	Entity * entity;
};
struct MessageGetCollider : public Message {
	MessageGetCollider() {
		type = MSGGCOL;
	}
	const Collision * o_collision;
};
struct MessageSetCollision : public Message {
	MessageSetCollision(Entity *entity): entity(entity){
		type = MSGSCOL;
	}
	Entity *entity;
};
struct MessageGetEntityType : public Message {
	MessageGetEntityType() {
		type = MSGGTYPE;
	}
	EntityType o_eType;
};
struct MessageGetSprite : public Message {
	MessageGetSprite() {
		type = MSGGSPRITE;
	}
	Sprite* o_sprite;
};
struct MessageSetSpriteScale : public Message {
	MessageSetSpriteScale(double width, double height) :width(width), height(height) {
		type = MSGSSPRITESCALE;
	}
	double width, height;
};
#endif // !WORLDDEFENDERS_MESSAGES_H
