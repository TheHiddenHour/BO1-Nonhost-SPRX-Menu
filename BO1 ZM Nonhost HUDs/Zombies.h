#include "stdafx.h"

#include <cellstatus.h>
#include <sys/prx.h>

#define TOC 0xA544B0//1.13

/*Non-Host HUDs by -JM-*/
struct opd_s
{
	int32_t sub;
	int32_t toc;
};

struct Font_s
{
	int fontName;
	float pixelHeight;
	int glyphCount;
	int material;
	int glowMaterial;
	int glyphs;
};

struct ScreenPlacement
{
	int64_t	 scaleVirtualToReal;
	int64_t scaleVirtualToFull;
	int64_t scaleRealToVirtual;
	int64_t virtualViewableMin;
	int64_t virtualViewableMax;
	int64_t virtualTweakableMin;
	int64_t virtualTweakableMax;
	int64_t realViewportBase;
	int64_t realViewportSize;
	int64_t realViewportMid;
	int64_t realViewableMin;
	int32_t realViewableMaxX;
	int32_t realViewableMaxY;
	int64_t realTweakableMin;
	int64_t realTweakableMax;
	int64_t subScreen;
};

/*NickBeHaxing*/
opd_s dvgb = { 0x455638, TOC };
bool(*Dvar_GetBool)(const char *dvarName) = (bool(*)(const char*))&dvgb;
opd_s Com_sprintf_t = { 0x468578, TOC };
int(*Com_sprintf)(char *dest, int size, const char *fmt, ...) = (int(*)(char*, int, char const *, ...))&Com_sprintf_t;
opd_s CBF = { 0x00395BA8, TOC };
void(*cBuf_AddText)(int clientNum, const char *text) = (void(*)(int, const char *))&CBF;

//Adressses & Definations
opd_s Material_RegisterHandle = { 0x685790, TOC };
opd_s UI_DrawText_p = { 0x3D8398, TOC };
opd_s UI_GetFont = { 0x3D80D8, TOC };
opd_s CL_DrawStr = { 0x4D5DB0, TOC };
void*(*Material_Register)(const char * font, int imageTrac) = (void*(*)(const char *, int))&Material_RegisterHandle;
void(*UI_DrawText)(ScreenPlacement* scrPlace, const char *text, int maxChars, Font_s* font, float x, float y, int horzAlign, int vertAlign, float scale, const float *color, int style) = (void(*)(ScreenPlacement*, const char*, int, Font_s*, float, float, int, int, float, const float*, int))&UI_DrawText_p;
Font_s*(*UI_GetFontHandle)(ScreenPlacement* scrPlace, int fontEnum, float scale) = (Font_s*(*)(ScreenPlacement*, int, float))&UI_GetFont;
void(*CL_DrawStretchPic)(ScreenPlacement* scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, float s1, float t1, float s2, float t2, const float *color, void *material) = (void(*)(ScreenPlacement*, float, float, float, float, int, int, float, float, float, float, const float *, void *))&CL_DrawStr;

//ColorsRGB
float White[4] = { 1, 1, 1, 0 };

//Drawing Calls
void DrawShader_UI(float x, float y, float width, float height, const float * color, const char * material)
{
	ScreenPlacement* scr = (ScreenPlacement*)0xB56C50;
	scr->realViewableMaxX = (int32_t)x;
	scr->realViewableMaxY = (int32_t)y;
	CL_DrawStretchPic(scr, x, y, width, height, 0, 0, 1, 1, 1, 1, color, Material_Register(material, 0));
}

void DrawText_UI(const char *Text, int font, float x, float y, float scale, const float *color)
{
	ScreenPlacement* scr = (ScreenPlacement*)0xB56C50;
	scr->realViewableMaxX = (int32_t)x;
	scr->realViewableMaxY = (int32_t)y;
	Font_s* font_p = UI_GetFontHandle(scr, font, scale);
	UI_DrawText(scr, Text, 0x7FFFFFFF, font_p, x, y, 0, 0, scale, color, 0);
}