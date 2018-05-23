#ifndef ZOMBIE_MONSTER_H
#define ZOMBIE_MONSTER_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "AbstractMonster.h"
class GeneralPlayer;

using namespace std;

class ZombieMonster :public AbstractMonster
{
public:
	ZombieMonster();
	~ZombieMonster();
	void attackTo(GeneralPlayer*);

	static int count;

	friend ostream& operator <<(ostream&, const ZombieMonster&);
};

#endif