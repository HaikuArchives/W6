#include "WeatherView.h"
#include "country.h"
#include "politic.h"
#include "group.h"
#include "day.h"
#include <Bitmap.h>
#include <TranslationUtils.h>

WeatherView::WeatherView(BRect r, Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur)
: BView(r, "", B_FOLLOW_TOP, B_WILL_DRAW)
{
  
	_jour=compteur;
	_country = Country_id;
	_group = Group_id; 
	_politic = Politic_id;
		
//+-----------------------------------

img_very_dry		= BTranslationUtils::GetBitmap('RAWT', 70, NULL);
img_dry				= BTranslationUtils::GetBitmap('RAWT', 71, NULL);
img_normal_hum		= BTranslationUtils::GetBitmap('RAWT', 72, NULL);
img_rainy			= BTranslationUtils::GetBitmap('RAWT', 73, NULL);
img_very_rainy		= BTranslationUtils::GetBitmap('RAWT', 74, NULL);

img_very_cold		= BTranslationUtils::GetBitmap('RAWT', 80, NULL);
img_cold			= BTranslationUtils::GetBitmap('RAWT', 81, NULL);
img_normal_temp		= BTranslationUtils::GetBitmap('RAWT', 82, NULL);
img_hot				= BTranslationUtils::GetBitmap('RAWT', 83, NULL);
img_very_hot		= BTranslationUtils::GetBitmap('RAWT', 84, NULL);
	
}



void WeatherView::Draw(BRect update_rect)
{
	char str[255];
	char str2[255];
	
	//Weather (pour agriculture)
	switch (_country[_jour->active_country]->real_temperature)
	{
		case VERY_COLD: sprintf(str,"Very cold");	DrawBitmap(img_very_cold,  BPoint(0,0)); break;
		case COLD: sprintf(str,"Cold");				DrawBitmap(img_cold,  BPoint(0,0)); break;
		case MODERATE: sprintf(str,"Cool");			DrawBitmap(img_normal_temp,  BPoint(0,0)); break;
		case WARM: sprintf(str,"Warm");				DrawBitmap(img_hot,  BPoint(0,0)); break;
		case HOT: sprintf(str,"Hot");				DrawBitmap(img_very_hot,  BPoint(0,0)); break;
	}

	switch (_country[_jour->active_country]->real_weather)
	{
		case VERY_DRY: sprintf(str2," / Very Dry");		DrawBitmap(img_very_dry,  BPoint(10,0)); break;
		case DRY: sprintf(str2," / Dry");				DrawBitmap(img_dry,  BPoint(10,0)); break;
		case MODERATE: sprintf(str2," / Stable");		DrawBitmap(img_normal_hum,  BPoint(10,0)); break;
		case RAINY: sprintf(str2," / Rainy");			DrawBitmap(img_rainy,  BPoint(10,0)); break;
		case VERY_RAINY: sprintf(str2," / Very rainy");	DrawBitmap(img_very_rainy,  BPoint(10,0)); break;
	}
	
	strcat(str,str2);
	bb_help.SetHelp(this,str);

}