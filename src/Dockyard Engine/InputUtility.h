#ifndef _InputUtility
#define _InputUtility

enum KEY
{
	NUM_0_KEY = 0x30,
	NUM_1_KEY = 0x31,
	NUM_2_KEY = 0x32,
	NUM_3_KEY = 0x33,
	NUM_4_KEY = 0x34,
	NUM_5_KEY = 0x35,
	NUM_6_KEY = 0x36,
	NUM_7_KEY = 0x37,
	NUM_8_KEY = 0x38,
	NUM_9_KEY = 0x39,
	A_KEY = 0x41,
	B_KEY = 0x42,
	C_KEY = 0x43,
	D_KEY = 0x44,
	E_KEY = 0x45,
	F_KEY = 0x46,
	G_KEY = 0x47,
	H_KEY = 0x48,
	I_KEY = 0x49,
	J_KEY = 0x4A,
	K_KEY = 0x4B,
	L_KEY = 0x4C,
	M_KEY = 0x4D,
	N_KEY = 0x4E,
	O_KEY = 0x4F,
	P_KEY = 0x50,
	Q_KEY = 0x51,
	R_KEY = 0x52,
	S_KEY = 0x53,
	T_KEY = 0x54,
	U_KEY = 0x55,
	V_KEY = 0x56,
	W_KEY = 0x57,
	X_KEY = 0x58,
	Y_KEY = 0x59,
	Z_KEY = 0x5A,
	SPACE_KEY = 0x20,
	ARROW_DOWN_KEY = 0x28,
	ARROW_UP_KEY = 0x26,
	ARROW_LEFT_KEY = 0x25,
	ARROW_RIGHT_KEY = 0x27,
	F10_KEY = 0x79,
	F9_KEY = 0x78
};

class InputUtility
{
public:
	// big four
	InputUtility() = default;
	InputUtility(const InputUtility&) = delete;
	InputUtility& operator = (const InputUtility&) = delete;
	virtual ~InputUtility() = default;

	static bool GetKeyInputState(KEY k);
};

#endif