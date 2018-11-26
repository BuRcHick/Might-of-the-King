#ifndef BUILDING_HPP
#define BUILDING_HPP
#include<Windows.h>
#include"Build.hpp"
class Building
{
public:
	Building()
	{
		b_hBmp = nullptr;
		b_en_an = false;
	}
	//---------Geters-----------------------------------------------------------------------------------------------------------------------------------
	int getX() const { return b_x; }
	int getY() const { return b_y; }
	Build getType() const { return b_type; }
	const HBITMAP get_hBmp();
	int getCad() const { return b_cad; }
	const char* getName() { return b_name; }

	//---------Setters-----------------------------------------------------------------------------------------------------------------------------------
	void setX(int _x) { b_x = _x; }
	void setY(int _y) { b_y = _y; }
	void setEnable();
	void set_Sprite_list(HBITMAP*, int);
	void updateCad() { if (b_en_an)b_cad++; }
	void set_to_zero() { b_cad = 0; }
	void setName(const char*);
	void setType(Build _type) { b_type = _type; }
	void setEnable(bool _state) { b_en_an = _state; }

private:
	int b_x, b_y, b_cad, b_limit;
	bool b_en_an; //enable animation
	HBITMAP* b_hBmp;
	Build b_type;
	char b_name[50];

};

inline void Building::setEnable() 
{ 
	b_cad = 0;
	b_en_an = !b_en_an;
}

inline void Building::setName(const char* _name)
{
	strcpy_s(b_name, _name);
}

class Village
	:public Building
{
public:
	Village()
		:Building()
	{
		v_cursants_count = 0;
		v_food_count = 0;
	}

private:
	int v_cursants_count, v_food_count;

};

class Camp
	:public Building
{
public:


};

class Cave
	:public Building
{
public:


	void ChaeckCave(int);


private:

};

inline void Cave::ChaeckCave(int _cad)
{
	if (getCad() == _cad)
		setEnable();
}

class Tomb
	:public Building
{
public:

	void CheckTomb(int);

};

inline void Tomb::CheckTomb(int _cad)
{
	if (getCad() == _cad)
		setEnable();
}

class Castle
	:public Building
{
public:
	Castle()
		:Building()
	{};

	void ChaeckCastle(int);

	~Castle() = default;

private:

};

inline void Castle::ChaeckCastle(int _cad)
{
	if (getCad() == _cad)
		setEnable();
}


#endif // !BUILDING_HPP

