#include"MoK.hpp"




HBITMAP*	Villages_Anime_PTR = new HBITMAP[VILLAGES_CADS];
HBITMAP*	Camps_Anime_PTR = new HBITMAP[CAMPSS_CADS];
HBITMAP*	Caves_Anime_PTR = new HBITMAP[CAVES_CADS];
HBITMAP*	Tombs_Anime_PTR = new HBITMAP[TOMBS_CADS];
HBITMAP*	Castle_1_Anime_PTR = new HBITMAP[CASTLE_1_CADS];
HBITMAP*	Castle_2_Anime_PTR = new HBITMAP[CASTLE_2_CADS];
HBITMAP*	Castle_3_Anime_PTR = new HBITMAP[CASTLE_3_CADS];
HBITMAP*	Castle_4_Anime_PTR = new HBITMAP[CASTLE_4_CADS];


HBITMAP MaphBmp, Hero_info, BatthBmp;


const char* VillagesName[VILLAGES_COUNT] = {
	"Village 1",
	"Village 2",
	"Village 3",
	"Village 4",
	"Village 5",
	"Village 6",
	"Village 7",
	"Village 8",
	"Village 9",
	"Village 10",
	"Village 11",
	"Village 12" };

const char* CampsName[CAMPS_COUNT] = {
	"Camp 1",
	"Camp 2",
	"Camp 3",
	"Camp 4",
	"Camp 5",
	"Camp 6",
	"Camp 7",
	"Camp 8",
	"Camp 9" };

const char* CavesName[CAVES_COUNT] = {
	"Cave 1",
	"Cave 2",
	"Cave 3",
	"Cave 4",
	"Cave 5" };

const char* TombsName[TOMBS_COUNT] = {
	"Tomb 1",
	"Tomb 2",
	"Tomb 3",
	"Tomb 4",
	"Tomb 5" };

const char* CastlesName[CASTLES_COUNT] = {
	"Castle 1",
	"Castle 2",
	"Castle 3",
	"Castle 4" };

int bloks_coords[BLOCKS_H_COUNT][BLOCKS_W_COUNT];
int constr_coords[BATT_CONS_COUNT];

Solclass* Battlefield[BLOCKS_H_COUNT][BLOCKS_W_COUNT];

Building Map;
Village* Villages_PTR = new Village[VILLAGES_COUNT];
Camp* Camps_PTR = new Camp[CAMPS_COUNT];
Tomb* Tombs_PTR = new Tomb[TOMBS_COUNT];
Cave* Caves_PTR = new Cave[CAVES_COUNT];
Castle Castle_1;
Castle Castle_2;
Castle Castle_3;
Castle Castle_4;
WORD SX = GetSystemMetrics(SM_CXSCREEN);
WORD SY = GetSystemMetrics(SM_CYSCREEN);

//----------Soldiers--------------------------------------------------------------------------------------------------
HBITMAP RecruithBmp, SoldierhBmp, KnighthBmp,
ArcherhBmp, ArbalesterhBmp, SurgeonhBmp;

//---------World-features---------------------------------------------------------------------------------------------------
void CreateWorld(HINSTANCE hInst, HWND hWnd)
{
	SetTimer(hWnd, TIMER_REDRAW, TIMREDRSPEED, NULL);
	SetTimer(hWnd, TIMER_ANIMATION, TIMANIMSPEED, NULL);
	SetTimer(hWnd, TIMER_TOMB, TIMETOMBSPEED, NULL);
	SetTimer(hWnd, TIMER_CAVE, TIMECAVESPEED, NULL);
	SetTimer(hWnd, TIMER_CASTLE_1, TIMECS1_SPEED, NULL);
	SetTimer(hWnd, TIMER_CASTLE_2, TIMECS2_SPEED, NULL);
	SetTimer(hWnd, TIMER_CASTLE_3, TIMECS3_SPEED, NULL);
	SetTimer(hWnd, TIMER_CASTLE_4, TIMECS4_SPEED, NULL);

	MaphBmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MAP)); //load map bitmap
	Hero_info = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_HERO_INFMENU)); //load maenu of hero bitmap
	Map.set_Sprite_list(&MaphBmp, 0);
	Map.setType(Build::Map);
	//--------Load-Villages-Sprite-list----------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < VILLAGES_CADS; i++)
		Villages_Anime_PTR[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_VILLAGE_1 + i));
	
	//--------Load-Camps-Sprite-list----------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < CAMPSS_CADS; i++)
		Camps_Anime_PTR[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CAMP_1 + i));

	//--------Load-Tombs-Sprite-list----------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < TOMBS_CADS; i++)
		Tombs_Anime_PTR[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_TOMB_1 + i));

	//--------Load-Caves-Sprite-list----------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < CAVES_CADS; i++)
		Caves_Anime_PTR[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CAVE_1 + i));
	
	//--------Load-Castle-1-Sprite-list----------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < CASTLE_1_CADS; i++)
		Castle_1_Anime_PTR[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CASTLE1_1 + i));

	//--------Load-Castle-2-Sprite-list----------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < CASTLE_2_CADS; i++)
		Castle_2_Anime_PTR[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CASTLE2_1 + i));

	//--------Load-Castle-3-Sprite-list----------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < CASTLE_3_CADS; i++)
		Castle_3_Anime_PTR[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CASTLE_3_1 + i));

	//--------Load-Castle-4-Sprite-list----------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < CASTLE_4_CADS; i++)
		Castle_4_Anime_PTR[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CASTLE_4_1 + i));


	//--------Create-Villages----------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < VILLAGES_COUNT; i++)
	{
		Villages_PTR[i].setType(Build::Village);
		Villages_PTR[i].setName(VillagesName[i]);
		Villages_PTR[i].setEnable(true);
		Villages_PTR[i].setX(LOWORD(CoordVillages[i]));
		Villages_PTR[i].setY(HIWORD(CoordVillages[i]));
		Villages_PTR[i].set_Sprite_list(Villages_Anime_PTR, VILLAGES_CADS);
	}

	//--------Create-Camps----------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < CAMPS_COUNT; i++)
	{
		Camps_PTR[i].setType(Build::Camp);
		Camps_PTR[i].setName(CampsName[i]);
		Camps_PTR[i].setEnable(true);
		Camps_PTR[i].setX(LOWORD(CoordCamps[i]));
		Camps_PTR[i].setY(HIWORD(CoordCamps[i]));
		Camps_PTR[i].set_Sprite_list(Camps_Anime_PTR, CAMPSS_CADS);
	}

	//--------Create-Tombs----------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < TOMBS_COUNT; i++)
	{
		Tombs_PTR[i].setType(Build::Tomb);
		Tombs_PTR[i].setName(TombsName[i]);
		Tombs_PTR[i].setEnable();
		Tombs_PTR[i].setX(LOWORD(CoordTombs[i]));
		Tombs_PTR[i].setY(HIWORD(CoordTombs[i]));
		Tombs_PTR[i].set_Sprite_list(Tombs_Anime_PTR, TOMBS_CADS);
	}

	//--------Create-Caves----------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < CAVES_COUNT; i++)
	{
		Caves_PTR[i].setType(Build::Cave);
		Caves_PTR[i].setName(CavesName[i]);
		Caves_PTR[i].setX(LOWORD(CoordCaves[i]));
		Caves_PTR[i].setY(HIWORD(CoordCaves[i]));
		Caves_PTR[i].set_Sprite_list(Caves_Anime_PTR, CAVES_CADS);
	}

	//--------Create-Castle_1----------------------------------------------------------------------------------------------------------------------------------------------------
	Castle_1.setType(Build::Castle_1);
	Castle_1.setName(CastlesName[0]);
	Castle_1.setEnable();
	Castle_1.setX(LOWORD(CoordCastles[0]));
	Castle_1.setY(HIWORD(CoordCastles[0]));
	Castle_1.set_Sprite_list(Castle_1_Anime_PTR, CASTLE_1_CADS);

	//--------Create-Castle_2----------------------------------------------------------------------------------------------------------------------------------------------------
	Castle_2.setType(Build::Castle_2);
	Castle_2.setName(CastlesName[1]);
	Castle_2.setX(LOWORD(CoordCastles[1]));
	Castle_2.setY(HIWORD(CoordCastles[1]));
	Castle_2.set_Sprite_list(Castle_2_Anime_PTR, CASTLE_2_CADS);

	//--------Create-Castle_3----------------------------------------------------------------------------------------------------------------------------------------------------
	Castle_3.setType(Build::Castle_3);
	Castle_3.setName(CastlesName[2]);
	Castle_3.setX(LOWORD(CoordCastles[2]));
	Castle_3.setY(HIWORD(CoordCastles[2]));
	Castle_3.set_Sprite_list(Castle_3_Anime_PTR, CASTLE_3_CADS);

	//--------Create-Castle_4----------------------------------------------------------------------------------------------------------------------------------------------------
	Castle_4.setType(Build::Castle_4);
	Castle_4.setName(CastlesName[3]);
	Castle_4.setEnable(true);
	Castle_4.setX(LOWORD(CoordCastles[3]));
	Castle_4.setY(HIWORD(CoordCastles[3]));
	Castle_4.set_Sprite_list(Castle_4_Anime_PTR, CASTLE_4_CADS);
}

void DrawMap(HDC _hdc)
{
	//-------Map--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	DrawBitmap(
		_hdc,
		Map.get_hBmp(),
		Map.getX(),
		Map.getY()
	);

	//-------Villages--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < VILLAGES_COUNT; i++)
		DrawTransperentBitmap(
			_hdc,
			Villages_PTR[i].get_hBmp(),
			Map.getX() + Villages_PTR[i].getX(),
			Map.getY() + Villages_PTR[i].getY(),
			0x0000FF00
		);

	//-------Camps--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < CAMPS_COUNT; i++)
		DrawTransperentBitmap(
			_hdc,
			Camps_PTR[i].get_hBmp(),
			Map.getX() + Camps_PTR[i].getX(),
			Map.getY() + Camps_PTR[i].getY(),
			0x0000FF00
		);

	//-------Caves--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < CAVES_COUNT; i++)
		DrawTransperentBitmap(
			_hdc,
			Caves_PTR[i].get_hBmp(),
			Map.getX() + Caves_PTR[i].getX(),
			Map.getY() + Caves_PTR[i].getY(),
			0x0000FF00
		);

	//-------Tombs--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < TOMBS_COUNT; i++)
		DrawTransperentBitmap(
			_hdc,
			Tombs_PTR[i].get_hBmp(),
			Map.getX() + Tombs_PTR[i].getX(),
			Map.getY() + Tombs_PTR[i].getY(),
			0x0000FF00
		);

	//-------Castle_1--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	DrawTransperentBitmap(
		_hdc,
		Castle_1.get_hBmp(),
		Map.getX() + Castle_1.getX(),
		Map.getY() + Castle_1.getY(),
		0x0000FF00
	);

	//-------Castle_2--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	DrawTransperentBitmap(
		_hdc,
		Castle_2.get_hBmp(),
		Map.getX() + Castle_2.getX(),
		Map.getY() + Castle_2.getY(),
		0x0000FF00
	);

	//-------Castle_3--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	DrawTransperentBitmap(
		_hdc,
		Castle_3.get_hBmp(),
		Map.getX() + Castle_3.getX(),
		Map.getY() + Castle_3.getY(),
		0x0000FF00
	);

	//-------Castle_4--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	DrawTransperentBitmap(
		_hdc,
		Castle_4.get_hBmp(),
		Map.getX() + Castle_4.getX(),
		Map.getY() + Castle_4.getY(),
		0x0000FF00
	);

	DrawTransperentBitmap(
		_hdc,
		Hero_info,
		0,
		0,
		0x0000FF00
	);


}

void MoveCam(WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case VK_UP:
		if (Map.getY() != 0)
			Map.setY(Map.getY() + STEP);
		break;

	case VK_DOWN:
		if (Map.getY() != -1160)
			Map.setY(Map.getY() - STEP);
		break;

	case VK_RIGHT:
		if (Map.getX() != -1500)
			Map.setX(Map.getX() - STEP);
		break;

	case VK_LEFT:
		if (Map.getX() != 0)
			Map.setX(Map.getX() + STEP);
		break;
	}
}

Building* SelectBuild(int _x, int _y)
{
	for (int i = 0; i < VILLAGES_COUNT; i++)
		if (Map.getX() + (Villages_PTR[i].getX() + VILLAGE_W) >= _x && Map.getX() + Villages_PTR[i].getX() <= _x
			&& Map.getY() + (Villages_PTR[i].getY() + VILLAGE_H) >= _y && Map.getY() + Villages_PTR[i].getY() <= _y)
			return &Villages_PTR[i];

	for (int i = 0; i < CAMPS_COUNT; i++)
		if (Map.getX() + (Camps_PTR[i].getX() + CAMP_W) >= _x && Map.getX() + Camps_PTR[i].getX() <= _x
			&& Map.getY() + (Camps_PTR[i].getY() + CAMP_H) >= _y && Map.getY() + Camps_PTR[i].getY() <= _y)
			return &Camps_PTR[i];

	for (int i = 0; i < CAVES_COUNT; i++)
		if (Map.getX() + (Caves_PTR[i].getX() + CAVE_W) >= _x && Map.getX() + Caves_PTR[i].getX() <= _x
			&& Map.getY() + Caves_PTR[i].getY() + CAVE_H >= _y && Map.getY() + Caves_PTR[i].getY() <= _y)
			return &Caves_PTR[i];

	for (int i = 0; i < TOMBS_COUNT; i++)
		if (Map.getX() + Tombs_PTR[i].getX() + TOMB_W >= _x && Map.getX() + Tombs_PTR[i].getX() <= _x
			&& Map.getY() + Tombs_PTR[i].getY() + TOMB_H >= _y && Map.getY() + Tombs_PTR[i].getY() <= _y)
			return &Tombs_PTR[i];

	if (Map.getX() + Castle_1.getX() + CASTLE_W >= _x && Map.getX() + Castle_1.getX() <= _x
		&& Map.getY() + Castle_1.getY() + CASTLE_H >= _y && Map.getY() + Castle_1.getY() <= _y)
		return &Castle_1;

	if (Map.getX() + Castle_2.getX() + CASTLE_W >= _x && Map.getX() + Castle_2.getX() <= _x
		&& Map.getY() + Castle_2.getY() + CASTLE_H >= _y && Map.getY() + Castle_2.getY() <= _y)
		return &Castle_2;

	if (Map.getX() + Castle_3.getX() + CASTLE_W >= _x && Map.getX() + Castle_3.getX() <= _x
		&& Map.getY() + Castle_3.getY() + CASTLE_H >= _y && Map.getY() + Castle_3.getY() <= _y)
		return &Castle_3;

	if (Map.getX() + Castle_4.getX() + CASTLE_W >= _x && Map.getX() + Castle_4.getX() <= _x
		&& Map.getY() + Castle_4.getY() + CASTLE_H >= _y && Map.getY() + Castle_4.getY() <= _y)
		return &Castle_4;
	
	return nullptr;
}

//--------Save/DownLoad-features------------------------------------------------------------------------------------------------------------------

bool SaveProgress()
{
	char buf[50];
	DWORD dwTemp;
	HANDLE hSave = CreateFile(SaveFile, GENERIC_READ | GENERIC_WRITE,
		NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hSave == INVALID_HANDLE_VALUE)
		return false;
	else
	{
		WriteFile(hSave, buf, wsprintf(buf, "map_x=%d;map_y=%d;", Map.getX(), Map.getY()), &dwTemp, NULL);
		CloseHandle(hSave);
		return true;
	}
}

bool DownloadSave()
{
	char buff[50];
	int res[2];
	DWORD dwTemp;
	HANDLE hSave = CreateFile(SaveFile, GENERIC_READ | GENERIC_WRITE,
		NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hSave == INVALID_HANDLE_VALUE)
		return false;
	else
	{
		ReadFile(hSave, buff, sizeof(buff), &dwTemp, NULL);
		for (int i = 0, j = 0; i < strlen(buff); i++)
			if (buff[i] == '=')
			{
				res[j] = getValaue(buff, i + 1, ';');
				++j;
			}

		Map.setX(res[0]);
		Map.setY(res[1]);
		CloseHandle(hSave);
		return true;
	}
}

int getValaue(char* _buff, int _start, char _symb)
{
	char buff[50];
	for (int i = _start, j = 0; i < strlen(_buff); i++)
	{
		if (_buff[i] != _symb)
		{
			buff[j] = _buff[i];
			j++;
		}
		else
			return atoi(buff);
	}
	return 0;
}

//--------Battlefield-features----------------------------------------------------------------------------------------------------------------------------------------
void Create_Battlefield(HINSTANCE hInst, HWND hWnd)
{
	SetTimer(hWnd,TIMER_REDRAW, TIMREDRSPEED, NULL);
	BatthBmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GRID));
	int x = 168, y = 10;
	for (int i = 0; i < BLOCKS_H_COUNT; i++)
	{
		x = 168;
		for (int j = 0; j < BLOCKS_W_COUNT; j++)
		{
			bloks_coords[i][j] = MAKELONG(x, y);
			x += 100;
			Battlefield[i][j] = nullptr;
		}
		y += 100;
	}

	x = 418;
	y = SY - 100;
	for (int i = 0; i < BATT_CONS_COUNT; i++)
	{
		constr_coords[i] = MAKELONG(x, y);
		x += BLOCK_W;
	}

	RecruithBmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_RECRUIT));
}

void DrawBattlefield(HDC _hdc)
{
	HBRUSH hBrush;
	DrawBitmap(
		_hdc,
		BatthBmp,
		0,
		0);
	hBrush = CreateSolidBrush(RGB(229, 229, 118));
	for (int i = 0; i < BLOCKS_H_COUNT * BLOCKS_W_COUNT; i++)
	{
			SelectObject(_hdc, hBrush);
			Rectangle(
				_hdc,
				LOWORD(bloks_coords[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT]),
				HIWORD(bloks_coords[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT]),
				LOWORD(bloks_coords[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT]) + BLOCK_W,
				HIWORD(bloks_coords[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT]) + BLOCK_H);

			if (Battlefield[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT] != nullptr)
			{
				char buff[50];
				SetBkColor(_hdc, RGB(229, 229, 118));
				SetTextColor(_hdc, 0x00005011);
				TextOut(_hdc,
					LOWORD(bloks_coords[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT]),
					HIWORD(bloks_coords[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT]),
					buff,
					wsprintf(
						buff,
						"%d",
						Battlefield[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT]->getHelth()));

				DrawTransperentBitmap(
					_hdc,
					Battlefield[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT]->getSkin(),
					LOWORD(Battlefield[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT]->getCoords()),
					HIWORD(Battlefield[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT]->getCoords()),
					0x0000FF00);
			}

		}

	DeleteObject(hBrush);
//---------------Constructor------------------------------------------------------------------------------------------------------------------------------------------------------------
	hBrush = CreateSolidBrush(RGB(225, 124, 0));
	for (int i = 0; i < BATT_CONS_COUNT; i++)
	{
		SelectObject(_hdc, hBrush);
		Rectangle(_hdc, LOWORD(constr_coords[i]), HIWORD(constr_coords[i]),
			LOWORD(constr_coords[i]) + BLOCK_W, HIWORD(constr_coords[i]) + BLOCK_H);
		DrawTransperentBitmap(
			_hdc,
			RecruithBmp,
			LOWORD(constr_coords[i]),
			HIWORD(constr_coords[i]),
			0x0000FF00);
	}
	DeleteObject(hBrush);
}

Solclass* CellSelect(const LPARAM _coord)
{
	Solclass* sp;
	for (int i = 0; i < BLOCKS_H_COUNT*BLOCKS_W_COUNT; i++)
		if (LOWORD(_coord) >= LOWORD(bloks_coords[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT]) &&
			LOWORD(_coord) <= LOWORD(bloks_coords[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT]) + BLOCK_W &&
			HIWORD(_coord) >= HIWORD(bloks_coords[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT]) &&
			HIWORD(_coord) <= HIWORD(bloks_coords[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT]) + BLOCK_H &&
			Battlefield[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT] != nullptr)
		{
			sp = Battlefield[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT];
			Battlefield[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT] = nullptr;
			return sp;
		}
	return nullptr;
}

Solclass* Construct_Soldier(
	const Army* _army, 
	const LPARAM _coord)
{
	static Solclass* sp;
	for (int i = 0; i < BATT_CONS_COUNT; i++)
		if (LOWORD(_coord) >= LOWORD(constr_coords[i]) &&
			LOWORD(_coord) <= LOWORD(constr_coords[i]) + BLOCK_W &&
			HIWORD(_coord) >= HIWORD(constr_coords[i]) &&
			HIWORD(_coord) <= HIWORD(constr_coords[i]) + BLOCK_H)
		{
			switch ((Soldier)i)
			{
			case Soldier::recruit:
				sp = new Infantry(
					100, 
					20, 
					15, 
					Soldier::recruit, 
					15, 
					20, 
					200,
					4,
					Side::side_1);
				sp->set_Skin(&RecruithBmp, 0);
				break;

			case Soldier::soldier:
				sp = new Infantry(
					200,
					30,
					25,
					Soldier::soldier,
					25,
					40,
					400,
					5,
					Side::side_1);
				sp->set_Skin(&RecruithBmp, 0);
				break;

			case Soldier::knight:
				sp = new Infantry(
					400,
					60,
					40,
					Soldier::knight,
					40,
					80,
					800,
					4,
					Side::side_1);
				sp->set_Skin(&RecruithBmp, 0);
				break;

			case Soldier::archer:
				sp = new Archer(
					200,
					30,
					10,
					Soldier::archer,
					0,
					40,
					400,
					6,
					Side::side_1);
				sp->set_Skin(&RecruithBmp, 0);
				break;

			case Soldier::arbalester:
				sp = new Archer(
					350,
					70,
					30,
					Soldier::arbalester,
					0,
					90,
					900,
					5,
					Side::side_1);
				sp->set_Skin(&RecruithBmp, 0);
				break;

			case Soldier::surgeon:
				//sp = new Infantry(100, 10, 5, Soldier::recruit, 5, 20, 200);
				break;
			}
			if (sp != nullptr)
				return sp;
		}
	return nullptr;
}

bool SetCell(
	Solclass* _soldier,
	const LPARAM _coord)
{
	for (int i = 0; i < BLOCKS_H_COUNT * BLOCKS_W_COUNT; i++)
	{
		if (LOWORD(_coord) >= LOWORD(bloks_coords[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]) &&
			LOWORD(_coord) <= LOWORD(bloks_coords[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]) + BLOCK_W &&
			HIWORD(_coord) >= HIWORD(bloks_coords[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]) &&
			HIWORD(_coord) <= HIWORD(bloks_coords[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]) + BLOCK_H &&
			Battlefield[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT] == nullptr)
		{
			Battlefield[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT] = _soldier;
			Battlefield[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]->moveSolider(bloks_coords[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]);
			return true;
		}
			
	}
	return false;
}

void eraseBattlefield()
{
	for (int i = 0; i < BLOCKS_H_COUNT*BLOCKS_W_COUNT; i++)
		if (Battlefield[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT] != nullptr)
		{
			delete Battlefield[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT];
			Battlefield[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT] = nullptr;
		}
}

void hit(const int _damage, LPARAM _coord, const Side _side)
{
	for (int i = 0; i < BLOCKS_H_COUNT * BLOCKS_W_COUNT; i++)
	{
		if (LOWORD(_coord) >= LOWORD(bloks_coords[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]) &&
			LOWORD(_coord) <= LOWORD(bloks_coords[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]) + BLOCK_W &&
			HIWORD(_coord) >= HIWORD(bloks_coords[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]) &&
			HIWORD(_coord) <= HIWORD(bloks_coords[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]) + BLOCK_H &&
			Battlefield[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT] != nullptr &&
			Battlefield[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]->getSide() != _side)
		{
			Battlefield[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]->s_hit((double)_damage);
		}
	}
}

int*  wave_algorithm(
	const int _start, 
	LPARAM _finish, 
	int& _size)
{
	int BuffBattlefield[BLOCKS_H_COUNT][BLOCKS_W_COUNT];
	const int MaxN = BLOCKS_W_COUNT * BLOCKS_H_COUNT;
	int N = 0;
	int w, h;
	if (!(LOWORD(_start) <= LOWORD(_finish) &&
		LOWORD(_start) + BLOCK_W >= LOWORD(_finish) &&
		HIWORD(_start) <= HIWORD(_finish) &&
		HIWORD(_start) + BLOCK_H >= HIWORD(_finish)))
	{
		for (int i = 0; i < MaxN; i++)
		{
			if (Battlefield[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT] != nullptr)
			{
				if (LOWORD(Battlefield[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]->getCoords()) <= LOWORD(_finish) &&
					LOWORD(Battlefield[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]->getCoords()) + BLOCK_W >= LOWORD(_finish) &&
					HIWORD(Battlefield[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]->getCoords()) <= HIWORD(_finish) &&
					HIWORD(Battlefield[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]->getCoords()) + BLOCK_H >= HIWORD(_finish))
					BuffBattlefield[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT] = 0;
				else
					BuffBattlefield[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT] = 87;
			}
			else
			{
				if (LOWORD(bloks_coords[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]) <= LOWORD(_finish) &&
					LOWORD(bloks_coords[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]) + BLOCK_W >= LOWORD(_finish) &&
					HIWORD(bloks_coords[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]) <= HIWORD(_finish) &&
					HIWORD(bloks_coords[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT]) + BLOCK_H >= HIWORD(_finish))
					BuffBattlefield[i / BLOCKS_W_COUNT][i % BLOCKS_W_COUNT] = 0;
				else
					if (LOWORD(bloks_coords[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT]) == LOWORD(_start)
						&& HIWORD(bloks_coords[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT]) == HIWORD(_start))
					{
						BuffBattlefield[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT] = 85;
						h = i / BLOCKS_W_COUNT;
						w = i % BLOCKS_W_COUNT;
					}
					else
						if (Battlefield[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT] == nullptr)
							BuffBattlefield[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT] = 86;
			}
		}

		bool find = false;

		while (N < MaxN && !find)
		{
			for (int i = 0; i < MaxN; i++)
			{
				if (BuffBattlefield[i / BLOCKS_W_COUNT][i%BLOCKS_W_COUNT] == N)
				{
					if (BuffBattlefield[(i / BLOCKS_W_COUNT) + 1][i%BLOCKS_W_COUNT] == 86 && i / BLOCKS_W_COUNT < BLOCKS_H_COUNT - 1)
						BuffBattlefield[(i / BLOCKS_W_COUNT) + 1][i%BLOCKS_W_COUNT] = N + 1;

					if (BuffBattlefield[(i / BLOCKS_W_COUNT) - 1][i%BLOCKS_W_COUNT] == 86 && i / BLOCKS_W_COUNT != 0)
						BuffBattlefield[(i / BLOCKS_W_COUNT) - 1][i%BLOCKS_W_COUNT] = N + 1;

					if (BuffBattlefield[i / BLOCKS_W_COUNT][(i%BLOCKS_W_COUNT) + 1] == 86 && i%BLOCKS_W_COUNT < BLOCKS_W_COUNT - 1)
						BuffBattlefield[i / BLOCKS_W_COUNT][(i%BLOCKS_W_COUNT) + 1] = N + 1;

					if (BuffBattlefield[i / BLOCKS_W_COUNT][(i%BLOCKS_W_COUNT) - 1] == 86 && i%BLOCKS_W_COUNT != 0)
						BuffBattlefield[i / BLOCKS_W_COUNT][(i%BLOCKS_W_COUNT) - 1] = N + 1;
				}
				if ((BuffBattlefield[h][w] > BuffBattlefield[h + 1][w] && h != BLOCKS_H_COUNT - 1) ||
					(BuffBattlefield[h][w] > BuffBattlefield[h - 1][w] && h != 0) ||
					(BuffBattlefield[h][w] > BuffBattlefield[h][w + 1] && w != BLOCKS_W_COUNT - 1) ||
					(BuffBattlefield[h][w] > BuffBattlefield[h][w - 1] && w != 0))
				{
					find = true;
					break;
				}

			}
			++N;
		}

		if (find)
		{
			_size = N + 2;
			BuffBattlefield[h][w] = N + 1;
			int* way{ new int[N + 2] };
			way[0] = MAKELONG(h, w);
			int i = 1;
			while (i < N + 2)
			{
				if (BuffBattlefield[h][w] > BuffBattlefield[h + 1][w] && h != BLOCKS_H_COUNT - 1)
				{
					++h;
					way[i] = MAKELONG(h, w);
					if (BuffBattlefield[h][w] == 0)
						i = N + 2;
					++i;
				}
				else
					if (BuffBattlefield[h][w] > BuffBattlefield[h - 1][w] && h != 0)
					{
						--h;
						way[i] = MAKELONG(h, w);
						if (BuffBattlefield[h][w] == 0)
							i = N + 2;
						++i;
					}
					else
						if (BuffBattlefield[h][w] > BuffBattlefield[h][w + 1] && w != BLOCKS_W_COUNT - 1)
						{
							++w;
							way[i] = MAKELONG(h, w);
							if (BuffBattlefield[h][w] == 0)
								i = N + 2;
							++i;
						}
						else
							if (BuffBattlefield[h][w] > BuffBattlefield[h][w - 1] && w != 0)
							{
								--w;
								way[i] = MAKELONG(h, w);
								if (BuffBattlefield[h][w] == 0)
									i = N + 2;
								++i;
							}
			}
			return way;
		}
	}
		return nullptr;
}


void Draw_Way(
	HDC _hdc, 
	int* _way, 
	const int _num_of_moves,
	const int _size)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(225, 0, 0));
		for (int i = 0; i < _size && i < _num_of_moves; i++)
	{
		SelectObject(_hdc, hBrush);
		Rectangle(_hdc, LOWORD(bloks_coords[LOWORD(_way[i])][HIWORD(_way[i])]), HIWORD(bloks_coords[LOWORD(_way[i])][HIWORD(_way[i])]),
			LOWORD(bloks_coords[LOWORD(_way[i])][HIWORD(_way[i])]) + BLOCK_W, HIWORD(bloks_coords[LOWORD(_way[i])][HIWORD(_way[i])]) + BLOCK_H);
	}
	DeleteObject(hBrush);

}
//--------Player----------------------------------------------------------------------------------------------------------------------------------------
Hero Player(
	200,
	40,
	20,
	Soldier::knight,
	20,
	50,
	200,
	0,
	5,
	6,
	Side::side_1);