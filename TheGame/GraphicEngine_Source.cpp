#include"GraphicEngine.hpp"

void DrawBitmap(HDC hdc, HBITMAP _hbmp, int _x, int _y)
{
	static HDC hdcBit;
	BITMAP bm;
	hdcBit = CreateCompatibleDC(hdc);
	SelectObject(hdcBit, _hbmp);
	GetObject(_hbmp, sizeof(BITMAP), (LPSTR)&bm);
	BitBlt(hdc, _x, _y, bm.bmWidth, bm.bmHeight, hdcBit, 0, 0, SRCCOPY);
	DeleteObject(hdcBit);
}

void DrawTransperentBitmap(HDC hdc, HBITMAP hBitmap, short xStart,
	short yStart, COLORREF cTransparentColor)
{
	BITMAP     bm;
	COLORREF   cColor;
	HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
	HBITMAP    bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
	HDC        hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
	POINT      ptSize;

	hdcTemp = CreateCompatibleDC(hdc);
	SelectObject(hdcTemp, hBitmap);   // Выбираем битмап

	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;            // Получаем ширину битмапа
	ptSize.y = bm.bmHeight;           // Получаем высоту битмапа
	DPtoLP(hdcTemp, &ptSize, 1);      // Конвертируем из координат
									  // устройства в логические
									  // точки

									  // Создаём несколько DC для хранения временных данных.
	hdcBack = CreateCompatibleDC(hdc);
	hdcObject = CreateCompatibleDC(hdc);
	hdcMem = CreateCompatibleDC(hdc);
	hdcSave = CreateCompatibleDC(hdc);

	// Создаём битмап для каждого DC.

	// Монохромный DC
	bmAndBack = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

	// Монохромный DC
	bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

	bmAndMem = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	bmSave = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

	// В каждом DC должен быть выбран объект битмапа для хранения
	// пикселей.
	bmBackOld = (HBITMAP)SelectObject(hdcBack, bmAndBack);
	bmObjectOld = (HBITMAP)SelectObject(hdcObject, bmAndObject);
	bmMemOld = (HBITMAP)SelectObject(hdcMem, bmAndMem);
	bmSaveOld = (HBITMAP)SelectObject(hdcSave, bmSave);

	// Устанавливаем режим маппинга.
	SetMapMode(hdcTemp, GetMapMode(hdc));

	// Сохраняем битмап, переданный в параметре функции, так как
	// он будет изменён.
	BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	// Устанавливаем фоновый цвет (в исходном DC) тех частей,
	// которые будут прозрачными.
	cColor = SetBkColor(hdcTemp, cTransparentColor);

	// Создаём маску для битмапа путём вызова BitBlt из исходного
	// битмапа на монохромный битмап.
	BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0,
		SRCCOPY);

	// Устанавливаем фоновый цвет исходного DC обратно в
	// оригинальный цвет.
	SetBkColor(hdcTemp, cColor);

	// Создаём инверсию маски.
	BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0,
		NOTSRCCOPY);

	// Копируем фон главного DC в конечный.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, xStart, yStart,
		SRCCOPY);

	// Накладываем маску на те места, где будет помещён битмап.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);

	// Накладываем маску на прозрачные пиксели битмапа.
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

	// XOR-им битмап с фоном на конечном DC.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);

	// Копируем на экран.
	BitBlt(hdc, xStart, yStart, ptSize.x, ptSize.y, hdcMem, 0, 0,
		SRCCOPY);

	// Помещаем оригинальный битмап обратно в битмап, переданный в
	// параметре функции.
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

	// Удаляем битмапы из памяти.
	DeleteObject(SelectObject(hdcBack, bmBackOld));
	DeleteObject(SelectObject(hdcObject, bmObjectOld));
	DeleteObject(SelectObject(hdcMem, bmMemOld));
	DeleteObject(SelectObject(hdcSave, bmSaveOld));

	// Удаляем DC из памяти.
	DeleteDC(hdcMem);
	DeleteDC(hdcBack);
	DeleteDC(hdcObject);
	DeleteDC(hdcSave);
	DeleteDC(hdcTemp);
}

void Play_Sound()
{
	//PlaySound(TEXT("neizvesten-muzyka-srednevekov-ya.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}