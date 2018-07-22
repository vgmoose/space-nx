// "PAD" controls (unique to us)
#define PAD_BUTTON_LEFT		0b00000001
#define PAD_BUTTON_RIGHT	0b00000010
#define PAD_BUTTON_UP		0b00000100
#define PAD_BUTTON_DOWN		0b00001000

#define PAD_BUTTON_MINUS	0b00010000
#define PAD_BUTTON_PLUS		0b00100000

#define PAD_BUTTON_A		0b01000000
#define PAD_BUTTON_B		0b10000000

// custom data structure for space game input
struct PADData {
	int btns_h;
	float rstick_x;
	float lstick_x;
	float rstick_y;
	float lstick_y;

	int touched;
	int touched_x;
	int touched_y;
};

void PADInit();
void PADDestroy();
void PADRead(struct PADData* data);
