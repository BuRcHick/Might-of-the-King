#ifndef HERO_HPP
#define HERO_HPP
#include"Soldier_class.hpp"
#include"army.hpp"
class Hero
	:public Solclass
{
public:
	Hero(
		int _health, 
		int _damage,
		int _armor,
		Soldier _type,
		int _block,
		int _critical_hit, 
		int _next_lvl,
		int _arm_count,
		int max_arm,
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
		h_army(_arm_count, max_arm), h_respect(0)
	{}

	Hero() = default;

	~Hero() = default;

//-------------Getters------------------------------------------------------------------------------------------------------------------------------------------------------
	const Army* getArmy() const { return &h_army; }
	Army* getArmy(){ return &h_army; }
	const int getResp() const { return h_respect; }

//-------------Setters------------------------------------------------------------------------------------------------------------------------------------------------------
	void upResp();
	void Hero::s_hit(double const);

private:
	Army h_army;
	int h_respect;
};

inline void Hero::upResp()
{
	if (getExp() > getExpForNextLvl())
	{
		h_respect += 20;
		h_army.changeMaxCount(h_army.getcurrCount() + 5);
		set_ExpForNextLvl();
	}
}

inline void Hero::s_hit(double const _damage)
{
	double one_proc = _damage / 100,
		fractpart,                   // дробная часть
		intpart;                     // целая часть;

	fractpart = modf(one_proc * getArmor(), &intpart);
	if (fractpart >= 0.5)
		++intpart;
	double newDamage = _damage - intpart;
	set_helth(getHelth() - (const int)newDamage);
}


#endif // !HERO_HPP
