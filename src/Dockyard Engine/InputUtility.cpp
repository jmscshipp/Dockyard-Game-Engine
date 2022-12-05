#include "InputUtility.h"

bool InputUtility::GetKeyInputState(KEY k)
{
	switch (k)
	{
	case NUM_0_KEY:
		return GetKeyState('0') & 0x08000;
		break;
	case NUM_1_KEY:
		return GetKeyState('1') & 0x08000;
		break;
	case NUM_2_KEY:
		return GetKeyState('2') & 0x08000;
		break;
	case NUM_3_KEY:
		return GetKeyState('3') & 0x08000;
		break;
	case NUM_4_KEY:
		return GetKeyState('4') & 0x08000;
		break;
	case NUM_5_KEY:
		return GetKeyState('5') & 0x08000;
		break;
	case NUM_6_KEY:
		return GetKeyState('6') & 0x08000;
		break;
	case NUM_7_KEY:
		return GetKeyState('7') & 0x08000;
		break;
	case NUM_8_KEY:
		return GetKeyState('8') & 0x08000;
		break;
	case NUM_9_KEY:
		return GetKeyState('9') & 0x08000;
		break;
	case A_KEY:
		return GetKeyState('A') & 0x08000;
		break;
	case B_KEY:
		return GetKeyState('B') & 0x08000;
		break;
	case C_KEY:
		return GetKeyState('C') & 0x08000;
		break;
	case D_KEY:
		return GetKeyState('D') & 0x08000;
		break;
	case E_KEY:
		return GetKeyState('E') & 0x08000;
		break;
	case F_KEY:
		return GetKeyState('F') & 0x08000;
		break;
	case G_KEY:
		return GetKeyState('G') & 0x08000;
		break;
	case H_KEY:
		return GetKeyState('H') & 0x08000;
		break;
	case I_KEY:
		return GetKeyState('I') & 0x08000;
		break;
	case J_KEY:
		return GetKeyState('J') & 0x08000;
		break;
	case K_KEY:
		return GetKeyState('K') & 0x08000;
		break;
	case L_KEY:
		return GetKeyState('L') & 0x08000;
		break;
	case M_KEY:
		return GetKeyState('M') & 0x08000;
		break;
	case N_KEY:
		return GetKeyState('N') & 0x08000;
		break;
	case O_KEY:
		return GetKeyState('O') & 0x08000;
		break;
	case P_KEY:
		return GetKeyState('p') & 0x08000;
		break;
	case Q_KEY:
		return GetKeyState('Q') & 0x08000;
		break;
	case R_KEY:
		return GetKeyState('R') & 0x08000;
		break;
	case S_KEY:
		return GetKeyState('S') & 0x08000;
		break;
	case T_KEY:
		return GetKeyState('T') & 0x08000;
		break;
	case U_KEY:
		return GetKeyState('U') & 0x08000;
		break;
	case V_KEY:
		return GetKeyState('V') & 0x08000;
		break;
	case W_KEY:
		return GetKeyState('W') & 0x08000;
		break;
	case X_KEY:
		return GetKeyState('X') & 0x08000;
		break;
	case Y_KEY:
		return GetKeyState('Y') & 0x08000;
		break;
	case Z_KEY:
		return GetKeyState('Z') & 0x08000;
		break;
	case SPACE_KEY:
		return GetKeyState(VK_SPACE) & 0x08000;
		break;
	case ARROW_DOWN_KEY:
		return GetKeyState(VK_DOWN) & 0x08000;
		break;
	case ARROW_UP_KEY:
		return GetKeyState(VK_UP) & 0x08000;
		break;
	case ARROW_LEFT_KEY:
		return GetKeyState(VK_LEFT) & 0x08000;
		break;
	case ARROW_RIGHT_KEY:
		return GetKeyState(VK_RIGHT) & 0x08000;
		break;
	case F9_KEY:
		return GetKeyState(VK_F9) & 0x08000;
		break;
	case F10_KEY:
		return GetKeyState(VK_F10) & 0x08000;
		break;
	}
}