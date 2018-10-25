#include "stdafx.h"
#include <cellstatus.h>
#include <sys/prx.h>
#include <PS3.h>
#include <Menu.h>

SYS_MODULE_INFO( BO_ZM_Nonhost_Menu, 0, 1, 1);
SYS_MODULE_START( _BO_ZM_Nonhost_Menu_prx_entry );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _BO_ZM_Nonhost_Menu_export_function, LIBNAME );

sys_ppu_thread_t _main_id;
bool _main_loop_destroy = false;

void _main(std::uint64_t args)
{
	sleep(10000);
	PatchInJump(0xDA980, (int)Menu::DrawMenu, false); // Hook night vision address to constantly run the DrawMenu function
	console_write("\n--- BO ZM Nonhost Menu ---\n\n"); // Print to check whether or not the SPRX has started

	//Main menu loop where tasks are done
	while (!_main_loop_destroy)
	{
		if (Dvar_GetBool("cl_ingame"))
		{
			if (!Menu::Open) // Menu not open
			{
				if (ButtonPressed(RIGHT)) // Right button pressed
				{
					Menu::OpenMenu(); // Open menu
				}
			}
			else // Menu is open
			{
				if (ButtonPressed(LEFT)) // Left button pressed
				{
					switch (Menu::CurrentMenu)
					{
					default:
					case StartMenu:
						Menu::CloseMenu();
						break;
					case MainMenu:
					case FunMenu:
					case WeaponsMenu:
					case CustomizationMenu:
						Menu::EnterMenu(StartMenu);
						break;
					}

					sleep(100);
				}
				else if (ButtonPressed(UP)) // Up button pressed
				{
					if (Menu::CurrentScroll > 0)
						Menu::CurrentScroll--;
					else
						Menu::CurrentScroll = Menu::ScrollMax;

					sleep(100);
				}
				else if (ButtonPressed(DOWN)) // Down button pressed
				{
					if (Menu::CurrentScroll < Menu::ScrollMax)
						Menu::CurrentScroll++;
					else
						Menu::CurrentScroll = 0;

					sleep(100);
				}
				else if (ButtonPressed(SQUARE)) // Square button pressed
				{
					switch (Menu::CurrentMenu)
					{
					default:
					case StartMenu:
						switch (Menu::CurrentScroll)
						{
						default:
						case 0:
							Menu::EnterMenu(MainMenu);
							break;
						case 1:
							Menu::EnterMenu(FunMenu);
							break;
						case 2:
							Menu::EnterMenu(WeaponsMenu);
							break;
						case 3:
							Menu::EnterMenu(CustomizationMenu);
							break;
						}
						break;
					case MainMenu:
						switch (Menu::CurrentScroll)
						{
						default:
						case 0: // Godmode toggle
							if (Godmode)
								Cbuf_AddText(0, "god 0");
							else
								Cbuf_AddText(0, "god 1");
							Godmode = !Godmode;

							break;
						case 1: // Give ammo
							Cbuf_AddText(0, "give ammo");
							CG_BoldGameMessage(0, "Ammo given", 5);
							break;
						case 2: // Ufo mode toggle
							if (UFOMode)
								Cbuf_AddText(0, "ufo 0");
							else

								Cbuf_AddText(0, "ufo 1");
							UFOMode = !UFOMode;

							break;
						case 3: // Noclip toggle
							if (Noclip)
								Cbuf_AddText(0, "noclip 0");
							else
								Cbuf_AddText(0, "noclip 1");
							Noclip = !Noclip;

							break;
						case 4: // Notarget toggle
							if (NoTarget)
								Cbuf_AddText(0, "notarget 0");
							else
								Cbuf_AddText(0, "notarget 1");
							NoTarget = !NoTarget;

							break;
						case 5: // Clear zombies
							Cbuf_AddText(0, "ai axis delete");

							break;
						}
						break;
					case FunMenu:
						switch (Menu::CurrentScroll)
						{
						default:
						case 0: // Third person toggle
							Cbuf_AddText(0, "toggle cg_thirdperson 1 0");

							break;
						case 1: // FOV toggle
							Cbuf_AddText(0, "toggle cg_fov 80 90 100 110 120 65");

							break;
						case 2: // Drop weapon
							Cbuf_AddText(0, "dropweapon");

							break;
						case 3: // Toggle HUD
							if (HideHud)
								Cbuf_AddText(0, "cg_crosshairAlpha 1; ammoCounterHide 0");
							else
								Cbuf_AddText(0, "cg_crosshairAlpha 0; ammoCounterHide 1");
							HideHud = !HideHud;

							break;
						case 4: // Draw FPS
							Cbuf_AddText(0, "toggle cg_drawFPS 1 0");

							break;
						case 5: // Hide gun
							Cbuf_AddText(0, "toggle cg_drawGun 1 0");

							break;
						}
						break;
					case WeaponsMenu:
						switch (Menu::CurrentScroll)
						{
						default:
						case 0: // Ray gun
							Cbuf_AddText(0, "give ray_gun_zm");
							break;
						case 1: // Death machine
							Cbuf_AddText(0, "give minigun_zm");
							break;
						case 2: // Thundergun
							Cbuf_AddText(0, "give thundergun_zm");
							break;
						case 3: // Winters howl
							Cbuf_AddText(0, "give freezegun_zm");
							break;
						case 4: // Shrink ray
							Cbuf_AddText(0, "give shrink_ray_zm");
							break;
						case 5: // Scavenger
							Cbuf_AddText(0, "give sniper_explosive_zm");
							break;
						case 6: // Human gun
							Cbuf_AddText(0, "give humangun_zm");
							break;
						case 7: // Wave gun zap gun
							Cbuf_AddText(0, "give microwavegun_zm");
							break;
						case 8: // Wunderwaffe
							Cbuf_AddText(0, "give tesla_gun_zm");
							break;
						}
						break;
					case CustomizationMenu:
						switch (Menu::CurrentScroll)
						{
							//"Default Theme\nBlue Theme\nRed Theme\nYellow Theme\nGreen Theme";
						default:
						case 0: // Default theme
							Menu::ChangeTheme(0.0f, 153.0f, 200.0f);
							break;
						case 1: // Blue theme
							Menu::ChangeTheme(0.0f, 0.0f, 1.0f);
							break;
						case 2: // Red theme
							Menu::ChangeTheme(1.0f, 0.0f, 0.0f);
							break;
						case 3: // Yellow
							Menu::ChangeTheme(1.0f, 1.0f, 0.0f);
							break;
						case 4: // Green
							Menu::ChangeTheme(0.0f, 1.0f, 0.0f);
							break;
						}
						break;
					}

					sleep(250);
				}
			}
		}
		else
			sleep(1000);
	}
	
	_main_loop_destroy = false;
	sys_ppu_thread_exit(0);
}

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _BO_ZM_Nonhost_Menu_export_function(void)
{
    return CELL_OK;
}

extern "C" int _BO_ZM_Nonhost_Menu_prx_entry(void)
{
	//Create main thread for menu
	if (sys_ppu_thread_create(&_main_id, _main, 0, 0, 0x1000, SYS_PPU_THREAD_CREATE_JOINABLE, "_main_thread") < 0)
		return SYS_PRX_STOP_FAILED;

    return SYS_PRX_RESIDENT;
}