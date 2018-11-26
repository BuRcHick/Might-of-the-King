#include"army.hpp"

bool Army::setArmy(const int* _army)
{
	a_count = 0;
	for (int i = 0; i < ARMY_COUNT; i++)
	{
		a_army[i] = _army[i];
		a_count += _army[i];
	}
	return true;
}