struct Message {
	enum msgType {
		MSGMOVE,
		MSGGETENTITYSTATE,
		MSGROTATE,
		MSGSCALE
	};
	msgType type;
};
struct MessageGetEntityState : public Message {
	MessageGetEntityState(){
		type = MSGGETENTITYSTATE;
	}
	double o_x, o_y, o_z, o_rot, o_sX,o_sY;
};
struct MessageMove : public Message {
	MessageMove() {
		type = MSGMOVE;
	}
	double x, y, z;
};
struct MessageRotate : public Message {
	MessageRotate() {
		type = MSGROTATE;
	}
	double rot;
};
struct MessageScale : public Message {
	MessageScale() {
		type = MSGSCALE;
	}
	double scaleX, scaleY;
};