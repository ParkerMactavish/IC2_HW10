#ifndef JW_MONSTER_H
#define JW_MONSTER_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "AbstractMonster.h"
class GeneralPlayer;

using namespace std;

class JWMonster :public AbstractMonster
{
public:
	JWMonster();
	~JWMonster();
	void attackTo(GeneralPlayer*);

	static int count;

	friend ostream& operator <<(ostream&, const JWMonster&);
};

#endif