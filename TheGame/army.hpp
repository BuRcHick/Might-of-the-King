#ifndef ARMY_HPP
#define ARMY_HPP
#define ARMY_COUNT 6
#include<Windows.h>
#include"Soldier.hpp"

class Army
{
public:
	Army(int _count, int _mcount)
		: a_count(_count), a_max_count(_mcount)
	{
		for (int i = 0; i < ARMY_COUNT; i++)
			a_army[i] = 0;
	}
	~Army() = default;

//--------------Getters---------------------------------------------------------------------------------------------------------------------------------------------------------
	const int* getInfo() const { return a_army; }
	const int getcurrCount() const { return a_count; }

//--------------Setters---------------------------------------------------------------------------------------------------------------------------------------------------------
	bool updateArmy(const Soldier);
	bool setArmy(const int*);
	bool replenishArmy(const Soldier);
	void changeMaxCount(int _count) { a_max_count = _count; }

private:
	int a_count, a_max_count;
	int a_army[ARMY_COUNT];

};

inline bool Army::updateArmy(const Soldier _soilder)
{
	a_army[(int)_soilder];
	switch (_soilder)
	{
	case Soldier::soldier:
		a_army[(int)Soldier::recruit]--;
		break;
	case Soldier::knight:
		a_army[(int)Soldier::soldier]--;
		break;
	case Soldier::archer:
		a_army[(int)Soldier::soldier]--;
		break;
	case Soldier::arbalester:
		a_army[(int)Soldier::archer]--;
		break;
	case Soldier::surgeon:
		a_army[(int)Soldier::soldier]--;
		break;
	}
	return true;
}

inline bool Army::replenishArmy(const Soldier _soilder)
{
	if (a_count <= a_max_count)
	{
		a_army[(int)_soilder] ++;
		a_count ++;
	}

	else
		return false;
	return true;
}

#endif // !ARMY_HPP
