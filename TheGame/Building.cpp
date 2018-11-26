#include"Building.hpp"

const HBITMAP Building::get_hBmp()
{
	if (b_cad >= b_limit)
		b_cad = 0;
	return b_hBmp[b_cad];
}

void Building::set_Sprite_list(HBITMAP* _spritelist, int _limit)
{
	set_to_zero();
	b_hBmp = _spritelist;
	b_limit = _limit;
}