#ifndef SOLDIER_CLASS_HPP
#define SOLDIER_CLASS_HPP
#include"soldier.hpp"
#include<cmath>
#include<Windows.h>

enum class Side
{
	side_1,
	side_2
};

class Solclass
{
public:
	Solclass(
		int _health, 
		int _damage, 
		int _armor, 
		Soldier _type, 
		int _critical_hit, 
		int _next_lvl,
		int _num_of_move,
		Side _side)
		: s_helth( _health),
		max_health(_health), 
		s_damage(_damage), 
		s_armor(_armor), 
		s_type(_type), 
		s_critical_hit(_critical_hit),
		s_next_lvl(_next_lvl),
		s_num_of_moves(_num_of_move),
		s_side(_side)
	{
		s_experience = 0;
		s_skin = nullptr;
	}
	Solclass() = default;
	~Solclass() = default;

//------------------Geters-------------------------------------------------------------------------------------------------------------------------------------------------
	int getHelth() const { return s_helth; }
	int getDamage() const { return s_damage; }
	int getArmor() const { return s_armor; }
	Soldier getType() const { return s_type; }
	int getExp() const { return s_experience; }
	int getExpForNextLvl() const { return s_next_lvl; }
	int getCoords() { return s_coords; }
	const HBITMAP getSkin();
	Side getSide()const { return s_side; }
	const int GetNumOfMove()const { return s_num_of_moves; }

//------------------Seters-------------------------------------------------------------------------------------------------------------------------------------------------
	virtual void s_hit(const double);
	void s_lelvelUp() { s_experience += 20; }
	void set_helth(const int _helth) { s_helth = _helth; }
	void set_ExpForNextLvl(){ s_next_lvl *=2; }
	void moveSolider(const int);
	void set_Skin(HBITMAP*, int);
	void set_NumofMoves(const int _num) { s_num_of_moves = _num; }
		
private:
	int s_helth, s_damage, s_armor, max_health,
		s_experience, s_critical_hit, s_next_lvl,
		s_coords, s_cads, s_max_cad, s_num_of_moves;
	HBITMAP* s_skin;
	Soldier s_type;
	Side s_side;
};

inline void Solclass::moveSolider(const int _coord)
{ 
		s_coords = _coord;
};


inline const HBITMAP Solclass::getSkin()
{
	s_cads++;
	if (s_cads >= s_max_cad)
		s_cads = 0;
	return s_skin[s_cads];
}

inline void Solclass::set_Skin(HBITMAP* _hbmp, int _cad)
{
	s_skin = _hbmp;
	s_max_cad = _cad;
	s_cads = 0;
}




//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Infantry
	:public Solclass
{
public:
	Infantry(
		int _health,
		int _damage,
		int _armor,
		Soldier _type,
		int _block,
		int _critical_hit,
		int _next_lvl,
		int _num_of_move,
		Side _side)
		:Solclass(
			_health, 
			_damage,
			_armor, 
			_type,
			_critical_hit,
			_next_lvl, 
			_num_of_move,
			_side),
		i_block(_block)
	{}
	Infantry() = default;
	~Infantry() = default;

	//------------------Geters-------------------------------------------------------------------------------------------------------------------------------------------------
	int getBlock() const { return i_block; }
	virtual void s_hit(const double);
	//------------------Seters-------------------------------------------------------------------------------------------------------------------------------------------------


private:
	int i_block;
};

inline void Infantry::s_hit(const double _damage)
{
	double one_proc = _damage / 100,
		fractpart,                   // дробная часть
		intpart;                     // целая часть;

	fractpart = modf(one_proc * i_block, &intpart);
	if (fractpart >= 0.5)
		++intpart;

	double newhelth = _damage - intpart;

	one_proc = newhelth / 100;

	fractpart = modf(one_proc * getArmor(), &intpart);
	if (fractpart >= 0.5)
		++intpart;

	newhelth = getHelth() - _damage + intpart;

	set_helth((const int)newhelth);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Archer
	:public Solclass
{
public:
	Archer(int _health,
		int _damage,
		int _armor,
		Soldier _type,
		int _block,
		int _critical_hit,
		int _next_lvl,
		int _num_of_move,
		Side _side)
		:Solclass(
			_health,
			_damage,
			_armor,
			_type,
			_critical_hit,
			_next_lvl,
			_num_of_move,
			_side)
	{}
	Archer() = default;
	~Archer() = default;


private:
	int a_shoot_range;
};


#endif // !SOLDIER_CLASS_HPP
