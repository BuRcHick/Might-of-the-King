#include"Soldier_class.hpp"
void Solclass::s_hit(const double _damage)
{
	double one_proc = _damage / 100,
		fractpart,                   // ������� �����
		intpart;                     // ����� �����;

	fractpart = modf(one_proc * getArmor(), &intpart);
	if (fractpart >= 0.5)
		++intpart;
	double newDamage = _damage - intpart;
	set_helth(getHelth() - (const int)newDamage);
}