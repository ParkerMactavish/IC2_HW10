#include "..\header\GoblinMonster.h"
#include "..\header\GeneralPlayer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

GoblinMonster::GoblinMonster():AbstractMonster("Goblin", 60, 40, 12, 100, 50, 50)
{
	setHP(max_hp);
	setMP(max_mp);
	count++;
}

GoblinMonster::~GoblinMonster()
{
	count--;
}

int GoblinMonster::count=0;

void GoblinMonster::attackTo(GeneralPlayer* Player)
{
	srand(time(NULL));
	float damage = -((rand() % 200 - 100.0 + 1000.0) / 1000.0)*(float)this->attack + (float) Player->getDef();
	damage = damage <= 0 ? damage : 0;
	Player->increaseHP(damage);

	if (damage == 0) cout << "Defense of " << Player->getName() << " has TOTALLY blocked the attack from " << this->name << endl;
	else if (damage > this->attack*1.05)cout << "It crits~" << endl;
	else if (damage < this->attack*0.95) cout << this->name << " has missed a little bit"<<endl;

	cout << "Player " << Player->getName() << " has received a normal attack " << (int)-damage << " points." << endl
		<< "Now " << Player->getName() << " only has " << Player->getHP() << " health points left." << endl;
}

ostream& operator<< (ostream& os, const  GoblinMonster& rhs)
{
	cout << "Monster: " << rhs.name << endl;
	cout << "HP: " << rhs.getHP() << "/" << rhs.max_hp << endl;
	cout << "MP: " << rhs.getMP() << "/" << rhs.max_mp << endl;
	cout << "Exp: " << rhs.exp << endl;
	cout << "Att: " << rhs.attack << endl;
	cout << "Def: " << rhs.defense << endl;
	return os;
}