#include "TransData.h"

TransData::TransData()
{
	_bTeletext = false;
	_bSubtitle = false;
	_bMHP = false;
	_bMHEG5 = false;
}

bool TransData::getTeletext()
{
	return _bTeletext;
}

bool TransData::getSubtitle()
{
	return _bSubtitle;
}

bool TransData::getMHP()
{
	return _bMHP;
}

bool TransData::getMHEG5()
{
	return _bMHEG5;
}

void TransData::setTeletext(bool b)
{
	_bTeletext = b;

}
void TransData::setSubtitle(bool b)
{
	_bSubtitle = b;
}

void TransData::setMHP(bool b)
{
	_bMHP = b;
}

void TransData:: setMHEG5(bool b)
{
	_bMHEG5 = b;
}