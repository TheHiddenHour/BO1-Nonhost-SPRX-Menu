#include "stdafx.h"

#include <cellstatus.h>
#include <sys/ppu_thread.h>
#include <sys/sys_time.h>
#include <sys/syscall.h>
#include <sys/syscall.h>
#include <sys/timer.h>
#include <sys/types.h>
#include <sys/prx.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>

#include <PS3.h>
#include <Zombies.h>
#include <Menu.h>

SYS_MODULE_INFO( BO1_ZM_Nonhost_HUDs, 0, 1, 1);
SYS_MODULE_START( _BO1_ZM_Nonhost_HUDs_prx_entry );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _BO1_ZM_Nonhost_HUDs_export_function, LIBNAME );

//This Funcution Constintly Draws Engine Text
void DrawHuds()
{
	DrawText_UI("^5DUKE'S FPS MENU", 0, -20, 160, 0.5, Text_Color);//Title
	DrawShader_UI(Scroller_X, Scroller_Y, 160, 20, Scroller_Color, "white");//Scroller
	DrawText_UI(Menu_MenuText[Menu_MenuIndex], 0, -20, 180, 0.4f, Text_Color);//Options
}

bool buttonPressed(int address)
{
	if (*(char*)address == 0x01)
		return true;
	return false;
}

void BO1_Thread(uint64_t arg)
{
	sleep(25000);//Just to prevent starting game startup or something

	//Hooks Night Vision Address
	PatchInJump(0xDA980, (int)DrawHuds, false);

	//Disable cheat protection by Milky4444
	*(int*)0x456904 = 0x38600000;
	*(int*)0x456910 = 0x38000000;
	*(int*)0x45691C = 0x38800000;

	//This is the menu's main loop
	for (;;)
	{
		//If currently in game
		if (Dvar_GetBool("cl_ingame") == 1)
		{
			//If menu is not open
			if (!Menu_Open)
			{
				//If DPAD RIGHT is held for a bit (open menu)
				if (buttonPressed(0xB4ECE3))
				{
					Menu_MenuIndex = 0;
					Menu_ScrollerIndex = 0;

					//Make menu HUDs visible
					Text_Color[3] = 1;
					Scroller_Color[3] = 1;

					//Reset scroller pos
					Scroller_Y = 160;

					Menu_Open = true;
				}
			}
			else
			{
				//If DPAD LEFT is held for a bit (go back)
				if (buttonPressed(0xB4ECD3))
				{
					switch (Menu_MenuIndex)
					{
						case 0://---OPEN MENU---
							//Make menu HUDs invisible
							Text_Color[3] = 0;
							Scroller_Color[3] = 0;

							Menu_Open = false;
							break;
						case 1://---MAIN MENU---
						case 2://---FUN MENU---
						case 3://---WEAPONS MENU---
						case 4://---THEME MENU---
							Submenu(0);
							break;
					}

					sleep(200);
				}

				//If DPAD DOWN is held for a bit (option down)
				if (buttonPressed(0xB4ECC3))
				{
					//Handle scroller
					Menu_ScrollerIndex = (Menu_ScrollerIndex != Menu_OptionSize[Menu_MenuIndex]-1) ? Menu_ScrollerIndex + 1 : 0;
					Scroller_Y = 160.0f + (19.3f * Menu_ScrollerIndex);

					sleep(100);
				}

				//If DPAD UP is held for a bit (option up)
				if (buttonPressed(0xB4ECB3))
				{
					//Handle scroller
					Menu_ScrollerIndex = (Menu_ScrollerIndex != 0) ? Menu_ScrollerIndex - 1 : Menu_OptionSize[Menu_MenuIndex]-1;
					Scroller_Y = 160.0f + (19.3f * Menu_ScrollerIndex);

					sleep(100);
				}

				//If SQUARE is held for a bit (select option)
				if (buttonPressed(0xB4EBA3))
				{
					if (Menu_MenuIndex == 0)//---OPEN MENU---
					{
						switch (Menu_ScrollerIndex)
						{
							case 0://Main Menu
								Submenu(1);
								break;
							case 1://Fun Menu
								Submenu(2);
								break;
							case 2://Weapons Menu
								Submenu(3);
								break;
						}
					}
					else if (Menu_MenuIndex == 1)//---MAIN MENU---
					{
						switch (Menu_ScrollerIndex)
						{
							case 0://Godmode
								ToggleGodmode();
								break;
							case 1://Noclip
								ToggleNoclip();
								break;
							case 2://UFO
								ToggleUFO();
								break;
							case 3://No Target
								ToggleNoTarget();
								break;
							case 4://Clear Zombies
								cBuf_AddText(0, "ai axis delete");
								break;
							case 5://Inf. Ammo
								ToggleInfAmmo();
								break;
						}
					}
					else if (Menu_MenuIndex == 2)//---FUN MENU---
					{
						switch (Menu_ScrollerIndex)
						{
							case 0://Third Person
								ToggleThirdPerson();
								break;
							case 1://Toggle FOV
								cBuf_AddText(0, "toggle cg_fov 80 90 100 110 120 65");
								break;
							case 2://Give Ammo
								cBuf_AddText(0, "give ammo");
								break;
							case 3://Drop Weapon
								cBuf_AddText(0, "dropweapon");
								break;
							case 4://Toggle HUD
								ToggleHUD();
								break;
							case 5://Draw FPS
								ToggleFPS();
								break;
							case 6://Hide Gun
								ToggleHideGun();
								break;
						}
					}
					else if (Menu_MenuIndex == 3)//---WEAPONS MENU---
					{
						switch (Menu_ScrollerIndex)
						{
							case 0://Raygun
								cBuf_AddText(0, "give ray_gun_upgraded_zm");
								break;
							case 1://Wunderwaffe
								cBuf_AddText(0, "give tesla_gun_upgraded_zm");
								break;
							case 2://Zeus Cannon
								cBuf_AddText(0, "give thundergun_upgraded_zm");
								break;
							case 3://Winter's Howl
								cBuf_AddText(0, "give freezegun_upgraded_zm");
								break;
							case 4://Human Gun
								cBuf_AddText(0, "give humangun_zm");
								break;
							case 5://Scavenger
								cBuf_AddText(0, "give sniper_explosive_upgraded_zm");
								break;
							case 6://Shrink Ray
								cBuf_AddText(0, "give shrink_ray_upgraded_zm");
								break;
							case 7://Zap Guns
								cBuf_AddText(0, "give microwavegunlh_upgraded_zm");
								break;
							case 8://Default Weapon
								cBuf_AddText(0, "give defaultweapon_zm");
								break;
							case 9://Death Machine
								cBuf_AddText(0, "give minigun_zm");
								break;
							case 10://AK47
								cBuf_AddText(0, "give ak47_zm");
								break;
							case 11://Monkey Bomb
								cBuf_AddText(0, "give zombie_cymbal_monkey");
								break;
						}
					}

					sleep(200);
				}
			}
		}
		else
			sleep(1000);
	}
}

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _BO1_ZM_Nonhost_HUDs_export_function(void)
{
    return CELL_OK;
}

extern "C" int _BO1_ZM_Nonhost_HUDs_prx_entry(void)
{
	create_thread(BO1_Thread, 0x4AA, 0x6000, "Main_Thread");

    return SYS_PRX_RESIDENT;
}
