#ifndef BUTTON_HEAD_HPP
#define BUTTON_HEAD_HPP
#include<Windows.h>

#include"GraphicEngine.hpp"
#include"resource.h"
#define WM_BUTTON (WM_USER + 0)
#define BMP_PARAM 59
#define Count(a) (ceil((double)LOWORD(a) / (double)BMP_PARAM))
class Button
{
public:
	Button(const int _id)
		:b_id(_id)
	{}

	void CreateButton(HWND,	const int, const int, bool, 
					HBITMAP*, HBITMAP*, const char*);
	void DrawButton(HDC);
	~Button();

	bool checkActive(LPARAM);

	void pushButton(LPARAM);

	void setEnable() { b_enable = !b_enable; }

	const int getID() const { return b_id; }

private:
	int b_coords, b_params, b_count;
	const int b_id;
	bool  b_enable;
	char b_text[50];
	HWND b_parenthWnd;
	HBITMAP* b_cur_skin;
	HBITMAP* b_inact_skin; 
	HBITMAP* b_act_skin;
};


inline void Button::CreateButton(
	HWND _hWnd,
	const int _coords,
	const int _params,
	bool _enable,
	HBITMAP* _inaktskin,
	HBITMAP* __aktskin,
	const char* _text)
{
	b_parenthWnd = _hWnd;
	b_coords = _coords;
	b_params = _params;
	b_enable = _enable;
	b_enable = _enable;
	b_inact_skin = _inaktskin;
	b_cur_skin = b_inact_skin;
	b_act_skin = __aktskin;
	b_count = Count(b_params);
	strcpy_s(b_text,_text);
}

inline Button::~Button()
{
	//delete b_text;
}

inline bool Button::checkActive(LPARAM _lParam)
{
	if (LOWORD(_lParam) >= LOWORD(b_coords)
		&& LOWORD(_lParam) <= LOWORD(b_coords) + LOWORD(b_params)
		&& HIWORD(_lParam) >= HIWORD(b_coords)
		&& HIWORD(_lParam) <= HIWORD(b_coords) + HIWORD(b_params)
		&& b_enable)
	{
		b_cur_skin = b_act_skin;
		return true;
	}
	b_cur_skin = b_inact_skin;
	return false;
}

inline void Button::DrawButton(HDC _hdc)
{
	HFONT Font = CreateFont(BMP_PARAM, 20, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, ("Montresor"));
	HFONT hOldFont;
	for (int i = 0; i < b_count ; i++)
	{
		DrawTransperentBitmap(
			_hdc,
			*b_cur_skin,
			LOWORD(b_coords) + i*BMP_PARAM,
			HIWORD(b_coords),
			0x0000FF00);
	}


	if (hOldFont = (HFONT)SelectObject(_hdc, Font))
	{
		RECT rect;
		rect.left = LOWORD(b_coords);
		rect.top = HIWORD(b_coords);
		rect.right = rect.left + b_count*BMP_PARAM;
		rect.bottom = rect.top +  BMP_PARAM;
		SetBkMode(_hdc, TRANSPARENT);
		SetTextColor(_hdc, 0x00FFFFFF);
		// Display the text string 
		DrawText(_hdc,b_text, strlen(b_text),&rect,DT_CENTER | DT_VCENTER);
		// Restore the original font   
		SelectObject(_hdc, hOldFont);
	}
	DeleteObject(hOldFont);
	DeleteObject(Font);
}

inline void Button::pushButton(LPARAM _lParam)
{
	if (checkActive(_lParam))
		SendMessage(b_parenthWnd, WM_BUTTON, b_id, NULL);
}

#endif // !BUTTON_HEAD_HPP
