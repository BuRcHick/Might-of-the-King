#include"MoK.hpp"

HINSTANCE hInst;
LPCTSTR szWindowClass = "MainWind";
LPCTSTR szCompWindowClass = "CompWind";
LPCTSTR szFightWindowClass = "FightWind";
LPCTSTR szPreFightWindowClass = "PreFightWind";
LPCTSTR szTitle = "Might of the King";

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;
	
	HWND hWndMain = CreateWindow(
		szWindowClass,
		szTitle,
		WS_POPUP,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWndMain)
		return false;

	ShowWindow(hWndMain, SW_SHOWMAXIMIZED);
	UpdateWindow(hWndMain);

	return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------
HBITMAP BattInActive, BattActive;
void MainWndRegisterClass(HINSTANCE hInstance)
{
	WNDCLASS wc;
	memset(&wc, 0, sizeof(WNDCLASS));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GRAY_BRUSH;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szWindowClass;

	RegisterClass(&wc);
}

void CompWndRegisterClass(HINSTANCE hInstance)
{
	WNDCLASS wc;
	memset(&wc, 0, sizeof(WNDCLASS));
	wc.lpfnWndProc = CompWndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GRAY_BRUSH;
	wc.lpszClassName = szCompWindowClass;

	RegisterClass(&wc);
}

void FightWndRegisterClass(HINSTANCE hInstance)
{
	WNDCLASS wc;
	memset(&wc, 0, sizeof(WNDCLASS));
	wc.lpfnWndProc = FightWndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GRAY_BRUSH;
	wc.lpszClassName = szFightWindowClass;

	RegisterClass(&wc);
}

void PreFightRegisterClass(HINSTANCE hInstance)
{
	WNDCLASS wc;
	memset(&wc, 0, sizeof(WNDCLASS));
	wc.lpfnWndProc = PreFightWndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GRAY_BRUSH;;
	wc.lpszClassName = szPreFightWindowClass;

	RegisterClass(&wc);
}

//----------------------------------------------------------------------------------------------------------------------------------------------

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	
	BattInActive = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BUTTON_INACTIVE));
	BattActive = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BUTTON_ACTIVE));

	MSG msg;
	
	MainWndRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
		return false;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	DeleteObject(BattInActive);
	DeleteObject(BattActive);
	delete[] Villages_PTR;
	delete[] Camps_PTR;
	delete[] Caves_PTR;
	delete[] Tombs_PTR;
	delete[] Villages_Anime_PTR;
	delete[] Camps_Anime_PTR;
	delete[] Caves_Anime_PTR;
	delete[] Tombs_Anime_PTR;
	delete[] Castle_1_Anime_PTR;
	delete[] Castle_2_Anime_PTR;
	delete[] Castle_3_Anime_PTR;
	delete[] Castle_4_Anime_PTR;
	return (int)msg.wParam;
}

//----------------------------------------------------------------------------------------------------------------------------------------------

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Button butComp(1), butPreFastFight(2), butExit(3);
	enum Buttons
	{
		others,
		Comp,
		PreFastFight,
		Exit
	};
	HDC hdc, memdc;
	HBITMAP hBitmap;
	HANDLE hOld;
	RECT rect;
		switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd,TIMER_REDRAW, TIMREDRSPEED, NULL);
		butComp.CreateButton(
			hWnd,
			MAKELONG((SX >> 1) - 150, 250),
			MAKELONG(300, 100),
			true,
			&BattInActive,
			&BattActive,
			"Кампания");

		butPreFastFight.CreateButton(
			hWnd,
			MAKELONG((SX >> 1) - 150, 350),
			MAKELONG(300, 100),
			true,
			&BattInActive,
			&BattActive,
			"Быстрый бой");

		butExit.CreateButton(
			hWnd,
			MAKELONG((SX >> 1) - 150, 450),
			MAKELONG(300, 100),
			true,
			&BattInActive,
			&BattActive,
			"Выход");
		
		break;

	case WM_PAINT:
		PAINTSTRUCT p;
		hdc = BeginPaint(hWnd, &p); /*Создаётся hdc*/
		memdc = CreateCompatibleDC(hdc); /*Создаётся memDC*/
		hBitmap = CreateCompatibleBitmap(hdc, SX, SY); /*создаётся изображение, которое подходит hdc? А зачем?*/
		hOld = SelectObject(memdc, hBitmap); /*Что-то неведомое*/
		butComp.DrawButton(memdc);/*Функция, в которой всё рисуется в memDC*/
		butPreFastFight.DrawButton(memdc);
		butExit.DrawButton(memdc);
		BitBlt(hdc, 0, 0, SX, SY, memdc, 0, 0, SRCCOPY); /*Всё копируется из memDC в hdc*/
		SelectObject(memdc, hOld); /*Опять что-то неведомое*/
		DeleteObject(hBitmap); /*Совместимая с hdc картинка удаляется*/
		DeleteDC(memdc); /*memDC удаляется*/
		EndPaint(hWnd, &p); /*hdc удаляется*/
		break;

	case SET_TIMER:
		SetTimer(hWnd, TIMER_REDRAW, TIMREDRSPEED, NULL);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TIMER_REDRAW:
			GetClientRect(hWnd, &rect);
			InvalidateRect(hWnd, &rect, FALSE);
			break;
		}
		break;
	case WM_MOUSEMOVE:
		butComp.checkActive(lParam);
		butPreFastFight.checkActive(lParam);
		butExit.checkActive(lParam);
		break;

	case WM_LBUTTONDOWN:
		butComp.pushButton(lParam);
		butPreFastFight.pushButton(lParam);
		butExit.pushButton(lParam);
		break;

	case WM_BUTTON:
		switch (wParam)
		{
		case Buttons::Comp:
		{
			KillTimer(hWnd,TIMER_REDRAW);
			CompWndRegisterClass(hInst);
			HWND hWndComp = CreateWindow(
			szCompWindowClass,
			"Company",
			WS_CHILDWINDOW | WS_VISIBLE | WS_POPUP,
			0,
			0,
			SX,
			SY,
			hWnd,
			NULL,
			hInst,
			NULL);
			SendMessage(hWndComp, SW_SHOWMAXIMIZED, NULL, NULL);
			UpdateWindow(hWndComp);
		}
			break;

		case Buttons::PreFastFight:
		{	
		Player.getArmy()->replenishArmy(Soldier::recruit);
		Player.getArmy()->replenishArmy(Soldier::soldier);
		Player.getArmy()->replenishArmy(Soldier::knight);
		Player.getArmy()->replenishArmy(Soldier::archer);	
		KillTimer(hWnd, TIMER_REDRAW);
		PreFightRegisterClass(hInst);
		HWND hWndPreFight = CreateWindow(
			szPreFightWindowClass,
			"PreFastFight",
			WS_CHILDWINDOW | WS_VISIBLE | WS_POPUP,
			0,
			0,
			SX,
			SY,
			hWnd,
			NULL,
			hInst,
			NULL);

		SendMessage(hWndPreFight, SW_SHOWMAXIMIZED, NULL, NULL);
		UpdateWindow(hWndPreFight);
		}
			break;

		case Buttons::Exit:
			SendMessage(hWnd, WM_DESTROY, NULL, NULL);
			break;
		}
		break;

	case WM_DESTROY:
		SendMessage(GetParent(hWnd), SET_TIMER, NULL, NULL);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK CompWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memdc;
	static int map_x, map_y;
	static int old_x, old_y;
	static bool SetMapFocus;
	static int i;
	Building *pB = nullptr;
	HBITMAP hBitmap;
	HANDLE hOld;
	RECT rect;
	switch (message)
	{
	case WM_CREATE:
		map_x = map_y = 0;
		SetMapFocus = false;
//		DownloadSave();
		CreateWorld(hInst, hWnd);
		break;

	case WM_PAINT:
		PAINTSTRUCT p;
		hdc = BeginPaint(hWnd, &p); /*Создаётся hdc*/
		memdc = CreateCompatibleDC(hdc); /*Создаётся memDC*/
		hBitmap = CreateCompatibleBitmap(hdc, SX, SY); /*создаётся изображение, которое подходит hdc? А зачем?*/
		hOld = SelectObject(memdc, hBitmap); /*Что-то неведомое*/
		
		DrawMap(memdc); /*Функция, в которой всё рисуется в memDC*/
		
		BitBlt(hdc, 0, 0, SX, SY, memdc, 0, 0, SRCCOPY); /*Всё копируется из memDC в hdc*/
		SelectObject(memdc, hOld); /*Опять что-то неведомое*/
		DeleteObject(hBitmap); /*Совместимая с hdc картинка удаляется*/
		DeleteDC(memdc); /*memDC удаляется*/
		EndPaint(hWnd, &p); /*hdc удаляется*/

		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TIMER_REDRAW:
			GetClientRect(hWnd, &rect);
			InvalidateRect(hWnd, &rect, FALSE);
			break;

		case TIMER_ANIMATION:
			for (int i = 0; i < VILLAGES_COUNT; i++)
				Villages_PTR[i].updateCad();

			for (int i = 0; i < CAMPS_COUNT; i++)
				Camps_PTR[i].updateCad();

			for (int i = 0; i < TOMBS_COUNT; i++)
			{
				Tombs_PTR[i].updateCad();
				Tombs_PTR[i].CheckTomb(TOMBS_CADS);
			}
			
			for (int i = 0; i < CAVES_COUNT; i++)
			{
				Caves_PTR[i].updateCad();
				Caves_PTR[i].ChaeckCave(CAVES_CADS);
			}
		
			Castle_1.updateCad();
			Castle_2.updateCad();

			Castle_1.ChaeckCastle(CASTLE_1_CADS);
			Castle_2.ChaeckCastle(CASTLE_2_CADS);
			break;

		case TIMER_TOMB:
			for (int i = 0; i < TOMBS_COUNT; i++)
				Tombs_PTR[i].setEnable();
			break;

		case TIMER_CAVE:
			for (int i = 0; i < CAVES_COUNT; i++)
				Caves_PTR[i].setEnable();
			break;

		case TIMER_CASTLE_1:
			Castle_1.setEnable();
			Castle_3.setEnable();
			break;

		case TIMER_CASTLE_2:
			Castle_2.setEnable();
			break;

		case TIMER_CASTLE_3:
			Castle_3.updateCad();
			Castle_3.ChaeckCastle(CASTLE_3_CADS);
			break;

		case TIMER_CASTLE_4:
			Castle_4.updateCad();
			break;
		}
			break;


	case WM_LBUTTONDOWN:
		old_x = LOWORD(lParam);
		old_y = HIWORD(lParam);
		pB = SelectBuild(old_x, old_y); // выбираем постройку на которую нажали
		if (pB != nullptr)
		{  // каждая постройка имеет свою диалоговую процедуру
			switch (pB->getType())
			{
			case Build::Village:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DLGVILLAGE), hWnd, VillageDlgProc);
				pB = nullptr;
				break;

			case Build::Camp:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DLGCAMP), hWnd, CampDlgProc);
				pB = nullptr;
				break;

			case Build::Cave:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DLGCAVE), hWnd, CaveDlgProc);
				pB = nullptr;
				break;

			case Build::Tomb:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DLGTOMB), hWnd, TombDlgProc);
				pB = nullptr;
				break;

			case Build::Castle_1:
				//DialogBox(hInst, MAKEINTRESOURCE(IDD_DLGVILLAGE), hWnd, VillageDlgProc);
				//pB = nullptr;
				break;

			case Build::Castle_2:
				//DialogBox(hInst, MAKEINTRESOURCE(IDD_DLGVILLAGE), hWnd, VillageDlgProc);
				//pB = nullptr;
				break;

			case Build::Castle_3:
				//DialogBox(hInst, MAKEINTRESOURCE(IDD_DLGVILLAGE), hWnd, VillageDlgProc);
				//pB = nullptr;
				break;

			case Build::Castle_4:
				//DialogBox(hInst, MAKEINTRESOURCE(IDD_DLGVILLAGE), hWnd, VillageDlgProc);
				//pB = nullptr;
				break;
			}
			SetFocus(hWnd);
		}
		break;

	case WM_RBUTTONDOWN:
		break;

	case WM_MOUSEMOVE:
		int cur_x, cur_y;
		if (SetMapFocus)
		{
			cur_x = LOWORD(lParam);
			cur_y = HIWORD(lParam);
			if (Map.getX() - (cur_x - old_x) < 0 && Map.getX() - (cur_x - old_x) >= -1540)
			Map.setX(Map.getX() - (cur_x - old_x));
			if (Map.getY() - (cur_y - old_y) < 0 && Map.getY() - (cur_y - old_y) >= -1160)
			Map.setY(Map.getY() - (cur_y - old_y));
		}
		break;

	case WM_KEYDOWN:
		// перемещение карты 
		MoveCam(wParam);
		break;

	case WM_COMMAND:
		break;

	case WM_DESTROY:
	//	SaveProgress();
		SendMessage(GetParent(hWnd), SET_TIMER, NULL, NULL);
		DestroyWindow(hWnd);
		delete pB;
		break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK FightWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memdc;
	static Solclass* soldier_ptr1; //указател` на выбраных солдат
	HBITMAP hBitmap;
	HANDLE hOld;
	RECT rect;
	static int w_size;
	static Button butReady(1);

	enum Butoons
	{
		others,
		Ready
	};

	static bool isReady, select;// завершение расстановки солдат/ выбор совершён
	static int enable_count;//число доступных бойцов
	static int* way;
	
	switch (message)
	{
	
	case WM_CREATE:
		isReady = select = false;
		enable_count = w_size = 0;
		soldier_ptr1 = nullptr;
		way = nullptr;
		Create_Battlefield(hInst, hWnd);
		butReady.CreateButton(
			hWnd,
			MAKELONG(LOWORD(constr_coords[5]) + 150, HIWORD(constr_coords[5]) + 10 ),
			MAKELONG(200, 100),
			false,
			&BattInActive,
			&BattActive,
			"Начать");
		
		break;

	case WM_PAINT:
		PAINTSTRUCT p;
		hdc = BeginPaint(hWnd, &p); //Создаётся hdc
		memdc = CreateCompatibleDC(hdc); //Создаётся memDC
		hBitmap = CreateCompatibleBitmap(hdc, SX, SY); //создаётся изображение, которое подходит hdc? А зачем?
		hOld = SelectObject(memdc, hBitmap); //Что-то неведомое
		DrawBattlefield(memdc);

		if (way != nullptr)
		{
			Draw_Way(memdc, way, soldier_ptr1->GetNumOfMove(), w_size);
		}
		if (isReady && soldier_ptr1)
		{
			DrawTransperentBitmap(
				memdc,
				soldier_ptr1->getSkin(),
				LOWORD(soldier_ptr1->getCoords()),
				HIWORD(soldier_ptr1->getCoords()),
				0x0000FF00);
		}

		butReady.DrawButton(memdc);
		BitBlt(hdc, 0, 0, SX, SY, memdc, 0, 0, SRCCOPY); //Всё копируется из memDC в hdc
		SelectObject(memdc, hOld); //Опять что-то неведомое
		DeleteObject(hBitmap); //Совместимая с hdc картинка удаляется
		DeleteDC(memdc); //memDC удаляется
		EndPaint(hWnd, &p); //hdc удаляется
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TIMER_REDRAW:
			GetClientRect(hWnd, &rect);
			InvalidateRect(hWnd, &rect, FALSE);
			break;
		}
		break;

	case WM_MOUSEMOVE:
		if (isReady && soldier_ptr1)
		{
				if (way)
				{
					delete way;
					way = nullptr;
				}
				way = wave_algorithm(
					soldier_ptr1->getCoords(),
					lParam,
					w_size);
		}
		butReady.checkActive(lParam);
		break;

	case WM_LBUTTONDOWN:
		if (enable_count == Player.getArmy()->getcurrCount())
		{
			isReady = true;
			butReady.setEnable();
		}
		if (!isReady)
			if (!select) // расстановка солдат по полю боя 
			{
				soldier_ptr1 = Construct_Soldier(
					Player.getArmy(),
					lParam);
				if (soldier_ptr1)
				{
					//soldier_ptr1->moveSolider(lParam);
					select = !select;
				}
			}
			else
			{
				if (SetCell(soldier_ptr1, lParam))
				{
					soldier_ptr1 = nullptr;
					select = !select;
					enable_count++;
				}
			}
		else
		{
			if (!select) // бой
			{
				soldier_ptr1 = CellSelect(lParam);
				if(soldier_ptr1)
				select = !select;
			}
			else
			{
				if (soldier_ptr1->GetNumOfMove() >= w_size)
				{
					if (SetCell(soldier_ptr1, lParam))
					{
						if (way)
						{
							delete way;
							way = nullptr;
						}
						soldier_ptr1 = nullptr;
						select = !select;
					}
					else
					{
						if (way)
						{
							delete way;
							way = nullptr;
						}
						hit(soldier_ptr1->getDamage(), lParam, soldier_ptr1->getSide());
					}
				}
				
			}
		}
		
		break;

	case WM_DESTROY:

		isReady = select = false;
		enable_count = 0;
		soldier_ptr1 = nullptr;
		if (way)
		{
			delete way;
			way = nullptr;
		}
		eraseBattlefield();
		KillTimer(hWnd, TIMER_REDRAW);
		SendMessage(GetParent(hWnd), SET_TIMER, NULL, NULL);
		DestroyWindow(hWnd);
		break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK PreFightWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memdc;
	HBITMAP hBitmap;
	HANDLE hOld;
	RECT rect;

	enum Butoons
	{
		Ready,
		Recruit,
		Soldier,
		Knight,
		Archer,
		Arbaleser,
		other
	};
	static Button butReady(Ready);

	switch (message)
	{

	case WM_CREATE:
		butReady.CreateButton(
			hWnd,
			MAKELONG((SX >> 1) - 100 , SY - 100), 
			MAKELONG(200, 100),
			false,
			&BattInActive,
			&BattActive,
			"Начать");
		break;

	case WM_PAINT:
		PAINTSTRUCT p;
		hdc = BeginPaint(hWnd, &p); //Создаётся hdc
		memdc = CreateCompatibleDC(hdc); //Создаётся memDC
		hBitmap = CreateCompatibleBitmap(hdc, SX, SY); //создаётся изображение, которое подходит hdc? А зачем?
		hOld = SelectObject(memdc, hBitmap); //Что-то неведомое
		butReady.DrawButton(memdc);
		BitBlt(hdc, 0, 0, SX, SY, memdc, 0, 0, SRCCOPY); //Всё копируется из memDC в hdc
		SelectObject(memdc, hOld); //Опять что-то неведомое
		DeleteObject(hBitmap); //Совместимая с hdc картинка удаляется
		DeleteDC(memdc); //memDC удаляется
		EndPaint(hWnd, &p); //hdc удаляется
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TIMER_REDRAW:
			GetClientRect(hWnd, &rect);
			InvalidateRect(hWnd, &rect, FALSE);
			break;
		}
		break;
	case WM_BUTTON:
		break;
	case WM_MOUSEMOVE:
		
		break;

	case WM_LBUTTONDOWN:
		
		break;

	case WM_DESTROY:
		KillTimer(hWnd, TIMER_REDRAW);
		SendMessage(GetParent(hWnd), SET_TIMER, NULL, NULL);
		DestroyWindow(hWnd);
		break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


BOOL CALLBACK VillageDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hPic;
	static HBITMAP hBitmap;
	HDC hdc;
	HDC hdcMem;
	HGDIOBJ hbmOld;


	switch (message)
	{
	// подгружаем картинку фона диалогового окна
	case WM_INITDIALOG:
		hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_VILLAGE_DLG));
		hPic = GetDlgItem(hWnd, IDC_VILLAGE);
		break;

	case WM_PAINT:
		BITMAP bm;
		PAINTSTRUCT ps;

		hdc = BeginPaint(hPic, &ps);
		hdcMem = CreateCompatibleDC(hdc);
		hbmOld = SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(bm), &bm);
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, hbmOld);
		DeleteDC(hdcMem);
		EndPaint(hPic, &ps);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hWnd, TRUE);
			return TRUE;
		case IDCANCEL:
			EndDialog(hWnd, FALSE);
			DestroyWindow(hWnd);
			return TRUE;

		}
	return FALSE;
}
	return TRUE;
}

BOOL CALLBACK CampDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hPic;
	static HBITMAP hBitmap;
	HDC hdc;
	HDC hdcMem;
	HGDIOBJ hbmOld;


	switch (message)
	{


		// подгружаем картинку фона диалогового окна
	case WM_INITDIALOG:
		hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CAMP_DLG));
		hPic = GetDlgItem(hWnd, IDC_CAMP);
		break;

	case WM_PAINT:
		BITMAP bm;
		PAINTSTRUCT ps;

		hdc = BeginPaint(hPic, &ps);
		hdcMem = CreateCompatibleDC(hdc);
		hbmOld = SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(bm), &bm);
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, hbmOld);
		DeleteDC(hdcMem);
		EndPaint(hPic, &ps);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hWnd, FALSE);
			DestroyWindow(hWnd);
			return TRUE;

		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK TombDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hPic;
	static HBITMAP hBitmap;
	HDC hdc;
	HDC hdcMem;
	HGDIOBJ hbmOld;

	// подгружаем картинку фона диалогового окна
	switch (message)
	{



	case WM_INITDIALOG:
		hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_TOMB_DLG));
		hPic = GetDlgItem(hWnd, IDC_TOMB);
		break;

	case WM_PAINT:
		BITMAP bm;
		PAINTSTRUCT ps;

		hdc = BeginPaint(hPic, &ps);
		hdcMem = CreateCompatibleDC(hdc);
		hbmOld = SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(bm), &bm);
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, hbmOld);
		DeleteDC(hdcMem);
		EndPaint(hPic, &ps);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hWnd, FALSE);
			DestroyWindow(hWnd);
			return TRUE;

		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK CaveDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hPic;
	static HBITMAP hBitmap;
	HDC hdc;
	HDC hdcMem;
	HGDIOBJ hbmOld;


	switch (message)
	{


	// подгружаем картинку фона диалогового окна
	case WM_INITDIALOG:
		hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CAVE_DLG));
		hPic = GetDlgItem(hWnd, IDC_CAVE);
		break;

	case WM_PAINT:
		BITMAP bm;
		PAINTSTRUCT ps;

		hdc = BeginPaint(hPic, &ps);
		hdcMem = CreateCompatibleDC(hdc);
		hbmOld = SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(bm), &bm);
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, hbmOld);
		DeleteDC(hdcMem);
		EndPaint(hPic, &ps);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hWnd, FALSE);
			DestroyWindow(hWnd);
			return TRUE;

		}
		return FALSE;
	}
	return TRUE;
}