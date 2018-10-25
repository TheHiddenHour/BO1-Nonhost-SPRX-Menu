#include <Zombies.h>

enum Buttons
{
	SQUARE = 0xB4EBA3,
	UP = 0xB4ECB3,
	DOWN = 0xB4ECC3,
	LEFT = 0xB4ECD3,
	RIGHT = 0xB4ECE3
};

bool ButtonPressed(Buttons button)
{
	return *(char*)button == 0x01;
}

enum Menus
{
	StartMenu, // Menu that shows up when you open the menu
		MainMenu, // Main Mods menu
		FunMenu, // Fun Mods menu
		WeaponsMenu, // Weapons menu
		CustomizationMenu // Customization menu
};

// Options variables
bool Godmode = false;
bool UFOMode = false;
bool Noclip = false;
bool NoTarget = false;
bool HideHud = false;

namespace Menu
{
	bool Open = false;
	Menus CurrentMenu = StartMenu;
	int CurrentScroll = 0;
	int ScrollMax = 0;
	float TitleColor[4] = { 0.0f, 153.0f, 200.0f, 0.0f }; //R, G, B, Alpha
	float TextColor[4] = { 1.0f, 1.0f, 1.0f, 0.0f };
	float ScrollerColor[4] = { 0.0f, 153.0f, 200.0f, 0.0f };
	float ScrollerX = -20.0f;
	float ScrollerY = 160.0f;

	void EnterMenu(Menus menu)
	{
		CurrentMenu = menu;
		CurrentScroll = 0;
	}

	int GetOptionSize(char* options)
	{
		int size = 0;
		
		for (int i = 0; i < strlen(options); i++)
		{
			if (options[i] == '\n')
				size++;
		}

		return size + 1;
	}

	static void DrawMenu()
	{
		ScrollerY = 160.0f + (19.3f * CurrentScroll);
		char* options;
		switch (CurrentMenu)
		{
		default:
		case StartMenu:
			options = "Main Menu\nFun Menu\nWeapons Menu\nCustomization Menu";
			break;
		case MainMenu:
			options = "Godmode\nGive Ammo\nUFO Mode\nNoclip\nNo Target\nClear Zombies";
			break;
		case FunMenu:
			options = "Third Person\nToggle FOV\nDrop Weapon\nToggle HUD\nDraw FPS\nHide Gun";
			break;
		case WeaponsMenu:
			options = "Ray Gun\nDeath Machine\nThundergun\nWinter's Howl\nV-R11\nScavenger\n31-79 JGb215\nWave Gun/Zap Gun\nWunderwaffe";
			break;
		case CustomizationMenu:
			options = "Default Theme\nBlue Theme\nRed Theme\nYellow Theme\nGreen Theme";
		}
		ScrollMax = GetOptionSize(options) - 1;

		DrawText_UI("DUKE'S NONHOST MENU", 0, -20, 160, 0.5, TitleColor); // Title
		DrawShader_UI(ScrollerX, ScrollerY, 160, 20, ScrollerColor, "white"); // Scroller
		DrawText_UI(options, 0, -20, 180, 0.4f, TextColor); // Options
	}

	void OpenMenu()
	{
		//CurrentMenu = StartMenu;
		//CurrentScroll = 0;
		EnterMenu(StartMenu);

		TitleColor[3] = 1.0f; // Set title alpha to 1
		ScrollerColor[3] = 1.0f; // Set scroller alpha to 1
		TextColor[3] = 1.0f; // Set option text alpha to 1

		Open = true;
	}

	void CloseMenu()
	{
		TitleColor[3] = 0.0f; // Set title alpha to 0
		ScrollerColor[3] = 0.0f; // Set scroller alpha to 0
		TextColor[3] = 0.0f; // Set option text alpha to 0

		Open = false;
	}

	void ChangeTheme(float red, float green, float blue)
	{
		TitleColor[0] = red;
		TitleColor[1] = green;
		TitleColor[2] = blue;

		ScrollerColor[0] = red;
		ScrollerColor[1] = green;
		ScrollerColor[2] = blue;
	}
}