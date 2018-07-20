//Mod variables
int ToggleFOV = 65;
bool Godmode = false;
bool Noclip = false;
bool UFO = false;
bool ThirdPerson = false;
bool NoTarget = false;
bool DrawFPS = false;
bool InfiniteAmmo = false;
bool HideGun = false;
bool HideHUD = false;

//Menu Variables
bool Menu_Open = false;
int Menu_MenuIndex = 0;
int Menu_ScrollerIndex = 0;

char Menu_MenuText[4][132] = {
	"Main Menu\nFun Menu\nWeapons Menu\nTheme Menu",//Menu opened
	"Godmode\nNoclip\nUFO\nNo Target\nClear Zombies\nInfinite Ammo",//Main Menu
	"Third Person\nToggle FOV\nGive Ammo\nDrop Weapon\nToggle HUD\nDraw FPS\nHide Gun",//Fun Menu
	"Ray Gun\nWunderwaffe\nZeus Cannon\nWinter's Howl\nHuman Gun\nScavenger\nShrink Ray\nZap Guns\nDefault Weapon\nDeath Machine\nAK47\nMonkey Bomb",//Weapons Menu

	//"Godmode\nNoclip\nUFO\nThird Person\nNo Target\nToggle FOV\nGive Ammo\nDrop Weapon\nHide Ammo\nDraw FPS\nClear Zombies\nInfinite Ammo\nHide Gun\nHide Crosshair\nWeapons Menu",
	//"Ray Gun\nWunderwaffe\nZeus Cannon\nWinter's Howl\nHuman Gun\nScavenger\nShrink Ray\nZap Guns\nDefault Weapon\nDeath Machine\nAK47\nMonkey Bomb"
};
int Menu_OptionSize[4] = { 4, 6, 7, 12 };//Menu Opened, Main Menu, Fun Menu, Weapons Menu

float Text_Color[4] = { 1, 1, 1, 0 };//R, G, B, Alpha
float Scroller_Color[4] = { 0, 153, 204, 0 };

float Scroller_X = -20.0f;
float Scroller_Y = 160.0f;

void Submenu(int menuindex)
{
	Menu_MenuIndex = menuindex;
	Menu_ScrollerIndex = 0;

	Scroller_Y = 160.0f + (19.3f * Menu_ScrollerIndex);
}

void ToggleGodmode()
{
	Godmode = !Godmode;
	if (Godmode)
		cBuf_AddText(0, "god 1");
	else
		cBuf_AddText(0, "god 0");
}

void ToggleNoclip()
{
	Noclip = !Noclip;
	if (Noclip)
		cBuf_AddText(0, "noclip 1");
	else
		cBuf_AddText(0, "noclip 0");
}

void ToggleUFO()
{
	UFO = !UFO;
	if (UFO)
		cBuf_AddText(0, "ufo 1");
	else
		cBuf_AddText(0, "ufo 0");
}

void ToggleNoTarget()
{
	NoTarget = !NoTarget;
	if (NoTarget)
		cBuf_AddText(0, "notarget 1");
	else
		cBuf_AddText(0, "notarget 0");
}

void Infinite_Ammo_Thread(uint64_t arg)
{
	while (InfiniteAmmo)
	{
		cBuf_AddText(0, "give ammo");
		sleep(250);
	}

	sys_ppu_thread_exit(0);
}

void ToggleInfAmmo()
{
	InfiniteAmmo = !InfiniteAmmo;
	if (InfiniteAmmo)
		create_thread(Infinite_Ammo_Thread, 0x4AA, 0x6000, "InfAmmo_Thread");
}

void ToggleThirdPerson()
{
	ThirdPerson = !ThirdPerson;
	if (ThirdPerson)
		cBuf_AddText(0, "cg_thirdPerson 1");
	else
		cBuf_AddText(0, "cg_thirdPerson 0");
}

void ToggleHUD()
{
	HideHUD = !HideHUD;
	if (HideHUD)
	{
		cBuf_AddText(0, "cg_crosshairAlpha 0 ; ammoCounterHide 1");
	}
	else
	{
		cBuf_AddText(0, "cg_crosshairAlpha 1 ; ammoCounterHide 0");
	}
}

void ToggleFPS()
{
	DrawFPS = !DrawFPS;
	if (DrawFPS)
		cBuf_AddText(0, "cg_drawFPS 1");
	else
		cBuf_AddText(0, "cg_drawFPS 0");
}

void ToggleHideGun()
{
	HideGun = !HideGun;
	if (HideGun)
		cBuf_AddText(0, "cg_drawGun 0");
	else
		cBuf_AddText(0, "cg_drawGun 1");
}