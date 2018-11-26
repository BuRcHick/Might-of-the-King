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
	SelectObject(hdcTemp, hBitmap);   // �������� ������

	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;            // �������� ������ �������
	ptSize.y = bm.bmHeight;           // �������� ������ �������
	DPtoLP(hdcTemp, &ptSize, 1);      // ������������ �� ���������
									  // ���������� � ����������
									  // �����

									  // ������ ��������� DC ��� �������� ��������� ������.
	hdcBack = CreateCompatibleDC(hdc);
	hdcObject = CreateCompatibleDC(hdc);
	hdcMem = CreateCompatibleDC(hdc);
	hdcSave = CreateCompatibleDC(hdc);

	// ������ ������ ��� ������� DC.

	// ����������� DC
	bmAndBack = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

	// ����������� DC
	bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

	bmAndMem = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	bmSave = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

	// � ������ DC ������ ���� ������ ������ ������� ��� ��������
	// ��������.
	bmBackOld = (HBITMAP)SelectObject(hdcBack, bmAndBack);
	bmObjectOld = (HBITMAP)SelectObject(hdcObject, bmAndObject);
	bmMemOld = (HBITMAP)SelectObject(hdcMem, bmAndMem);
	bmSaveOld = (HBITMAP)SelectObject(hdcSave, bmSave);

	// ������������� ����� ��������.
	SetMapMode(hdcTemp, GetMapMode(hdc));

	// ��������� ������, ���������� � ��������� �������, ��� ���
	// �� ����� ������.
	BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	// ������������� ������� ���� (� �������� DC) ��� ������,
	// ������� ����� �����������.
	cColor = SetBkColor(hdcTemp, cTransparentColor);

	// ������ ����� ��� ������� ���� ������ BitBlt �� ���������
	// ������� �� ����������� ������.
	BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0,
		SRCCOPY);

	// ������������� ������� ���� ��������� DC ������� �
	// ������������ ����.
	SetBkColor(hdcTemp, cColor);

	// ������ �������� �����.
	BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0,
		NOTSRCCOPY);

	// �������� ��� �������� DC � ��������.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, xStart, yStart,
		SRCCOPY);

	// ����������� ����� �� �� �����, ��� ����� ������� ������.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);

	// ����������� ����� �� ���������� ������� �������.
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

	// XOR-�� ������ � ����� �� �������� DC.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);

	// �������� �� �����.
	BitBlt(hdc, xStart, yStart, ptSize.x, ptSize.y, hdcMem, 0, 0,
		SRCCOPY);

	// �������� ������������ ������ ������� � ������, ���������� �
	// ��������� �������.
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

	// ������� ������� �� ������.
	DeleteObject(SelectObject(hdcBack, bmBackOld));
	DeleteObject(SelectObject(hdcObject, bmObjectOld));
	DeleteObject(SelectObject(hdcMem, bmMemOld));
	DeleteObject(SelectObject(hdcSave, bmSaveOld));

	// ������� DC �� ������.
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