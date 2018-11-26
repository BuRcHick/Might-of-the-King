#ifndef MOK_HPP
#define MOK_HPP

#include"GraphicEngine.hpp"
#include"Building.hpp"
#include"resource.h"
#include<memory>
#include"Soldier_class.hpp"
#include"soldier.hpp"
#include"army.hpp"
#include"Hero.hpp"
#include"ButtonHead.hpp"
#define BATT_CONS_COUNT 6

//my message
#define SET_TIMER (WM_USER + 1)
#define WM_TYPE_OF_BUTTLE (WM_USER + 2)

//------------WinMain-------------------------------------------------------------------------------------------------------------
void MainWndRegisterClass(HINSTANCE); //register_main`s_window_class

BOOL InitInstance(HINSTANCE, int);//create_main_window

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);//WndProc_of_main_window

LRESULT CALLBACK CompWndProc(HWND, UINT, WPARAM, LPARAM);//WndProc_of_company_window

LRESULT CALLBACK FightWndProc(HWND, UINT, WPARAM, LPARAM);//WndProc_of_fight_window

LRESULT CALLBACK PreFightWndProc(HWND, UINT, WPARAM, LPARAM);//WndProc_of_prefight_window

BOOL CALLBACK VillageDlgProc(HWND, UINT, WPARAM, LPARAM);//WndProc_of_villages

BOOL CALLBACK CampDlgProc(HWND, UINT, WPARAM, LPARAM);//WndProc_of_camps

BOOL CALLBACK CaveDlgProc(HWND, UINT, WPARAM, LPARAM);//WndProc_of_caves

BOOL CALLBACK TombDlgProc(HWND, UINT, WPARAM, LPARAM);//WndProc_of_tombs

BOOL CALLBACK CastleDlgProc(HWND, UINT, WPARAM, LPARAM);//WndProc_of_castles

void CompWndRegisterClass(HINSTANCE); //register_company`s_window_class
void FightWndRegisterClass(HINSTANCE);
void PreFightRegisterClass(HINSTANCE);

//------------Graphic-------------------------------------------------------------------------------------------------------------
void CreateWorld(HINSTANCE, HWND);//создание мира(карта)

void DrawMap(HDC);

void MoveCam(WPARAM);//движение по карте

//------------Building-------------------------------------------------------------------------------------------------------------
Building* SelectBuild(int, int);//выборка постройки

const int CoordVillages[VILLAGES_COUNT] = {
	MAKELONG(155, 185),
	MAKELONG(1160, 600),
	MAKELONG(275, 885),
	MAKELONG(790, 1170),
	MAKELONG(122, 1593),
	MAKELONG(1367, 1838),
	MAKELONG(1751, 1615),
	MAKELONG(2256, 1430),
	MAKELONG(2326, 1905),
	MAKELONG(2371, 1110),
	MAKELONG(2265, 742),
	MAKELONG(2620, 116) };

const int CoordCamps[CAMPS_COUNT] = {
	MAKELONG(920, 80),
	MAKELONG(770, 735),
	MAKELONG(1150, 1000),
	MAKELONG(83, 1741),
	MAKELONG(1773, 1782),
	MAKELONG(1818, 1167),
	MAKELONG(2686, 850),
	MAKELONG(2756, 554),
	MAKELONG(2385, 319)
};

const int CoordCaves[CAVES_COUNT] = {
	MAKELONG(1255, 145),
	MAKELONG(1305, 770),
	MAKELONG(531,  1738),
	MAKELONG(1611,  1140),
	MAKELONG(1808, 345)
};

const int CoordTombs[TOMBS_COUNT] = {
	MAKELONG(565, 15),
	MAKELONG(38, 1124),
	MAKELONG(950,  1747),
	MAKELONG(1806,  777),
	MAKELONG(2804, 255)
};

const int CoordCastles[CASTLES_COUNT] = {
	MAKELONG(615, 350),
	MAKELONG(805, 1390),
	MAKELONG(2425,  1560),
	MAKELONG(2025, 30)
};

extern HBITMAP* Villages_Anime_PTR;
extern HBITMAP*	Camps_Anime_PTR;
extern HBITMAP*	Caves_Anime_PTR;
extern HBITMAP*	Tombs_Anime_PTR;
extern HBITMAP*	Castle_1_Anime_PTR;
extern HBITMAP*	Castle_2_Anime_PTR;
extern HBITMAP*	Castle_3_Anime_PTR;
extern HBITMAP*	Castle_4_Anime_PTR;

extern HBITMAP	MaphBmp,
				Hero_info;

extern Building Map;
extern Village* Villages_PTR;
extern Camp* Camps_PTR;
extern Tomb* Tombs_PTR;
extern Cave* Caves_PTR;
extern Castle Castle_1, Castle_2, Castle_3, Castle_4;
extern WORD SX, SY;
//-----------Battlefield-param-------------------------------------------------------------------------------------------------------------
extern int bloks_coords[BLOCKS_H_COUNT][BLOCKS_W_COUNT];//координаты блоков главного поля битвы
extern int constr_coords[BATT_CONS_COUNT];//координаты поля конструктора
extern Solclass* Battlefield[BLOCKS_H_COUNT][BLOCKS_W_COUNT];//главное поле
void Create_Battlefield(HINSTANCE,HWND);//создание поля битвы

void DrawBattlefield(HDC);//отрисовка поля

bool SetCell(Solclass*,//установка указателя объекта в блок главного поля
	const LPARAM);

void hit(const int, LPARAM, const Side); //hit soldier

Solclass* CellSelect(const LPARAM);//выбор указателя из блока главного поля

Solclass* Construct_Soldier(const Army*, const LPARAM);//создание объекта в куче и передача его адреса в 

void eraseBattlefield();//очистка поля
extern HBITMAP RecruithBmp, SoldierhBmp, KnighthBmp,
				ArcherhBmp, ArbalesterhBmp, SurgeonhBmp;// битмапы для содат

int* wave_algorithm(const int, LPARAM, int&);

void Draw_Way(HDC, int*, const int, const int);

//-----------Player-param-------------------------------------------------------------------------------------------------------------
extern Hero Player;

//------------Save/Download-save-------------------------------------------------------------------------------------------------------------
bool SaveProgress();//сохранение
bool DownloadSave();//загрузка
int getValaue(char*, int, char);//выборка значений из файла загрузки
const LPCSTR SaveFile = "Save";


//------------Button-param-------------------------------------------------------------------------------------------------------------
#endif // !MOK_HPP

