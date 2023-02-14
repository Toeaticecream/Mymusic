#ifndef KEYMESSAGE_H
#define KEYMESSAGE_H

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
int checkkey()
{
	if (KEY_DOWN(VK_MENU))
	{
		if (KEY_DOWN(VK_NUMPAD0))
		{
			return 0;
		}
		if (KEY_DOWN(VK_NUMPAD1))
		{
			return 1;
		}
		if (KEY_DOWN(VK_NUMPAD2))
		{
			return 2;
		}
		if (KEY_DOWN(VK_NUMPAD3))
		{
			return 3;
		}
		if (KEY_DOWN(VK_NUMPAD4))
		{
			return 4;
		}
		if (KEY_DOWN(VK_NUMPAD5))
		{
			return 5;
		}
		if (KEY_DOWN(VK_NUMPAD6))
		{
			return 6;
		}
		if (KEY_DOWN(VK_NUMPAD7))
		{
			return 7;
		}
		if (KEY_DOWN(VK_NUMPAD8))
		{
			return 8;
		}
		if (KEY_DOWN(VK_NUMPAD9))
		{
			return 9;
		}
		if (KEY_DOWN('A'))
		{
			return 10;
		}
		if (KEY_DOWN('B'))
		{
			return 11;
		}
		if (KEY_DOWN('C'))
		{
			return 12;
		}
		if (KEY_DOWN('D'))
		{
			return 13;
		}
		if (KEY_DOWN('E'))
		{
			return 14;
		}
		if (KEY_DOWN('F'))
		{
			return 15;
		}
		if (KEY_DOWN('G'))
		{
			return 16;
		}
		if (KEY_DOWN('H'))
		{
			return 17;
		}
	}
	return -1;
}

#endif
