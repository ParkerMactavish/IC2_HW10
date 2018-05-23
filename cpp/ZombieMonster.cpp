#include "..\header\ZombieMonster.h"
#include "..\header\GeneralPlayer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

ZombieMonster::ZombieMonster() :AbstractMonster("Zombie", 50, 65, 17, 150, 30, 100)
{
	setHP(max_hp);
	setMP(max_mp);
	count++;
}

ZombieMonster::~ZombieMonster()
{
	count--;
}

int ZombieMonster::count = 0;

void ZombieMonster::attackTo(GeneralPlayer* Player)
{
	srand(time(NULL));
	if (rand() % 4 == 0 && this->getMP() > 9)
	{
		int damage = -2 * this->attack + Player->getDef();
		damage = damage <= 0 ? damage : 0;
		Player->increaseHP(damage);
		this->setMP(this->getMP() - 10);
		
		cout << "It's a SUPER attack"<<endl;
		if (damage == 0) cout << "Yet Player " << Player->getName() << " has TOTALLY blocked it by his defense." << endl;

		cout << "Player " << Player->getName() << " has received a SUPER attack " << -damage << " points." << endl
			<< "Now " << Player->getName() << " only has " << Player->getHP() << " health points left." << endl;
	}
	else
	{
		float dice = rand()%200;
		float damage = -((dice - 100.0 + 1000.0) / 1000.0)*(float)this->attack+(float) Player->getDef();
		damage = damage <= 0 ? damage : 0;
		Player->increaseHP(damage);

		if (damage == 0) cout << "Defense of " << Player->getName() << " has TOTALLY blocked the attack from " << this->name << endl;
		else if (dice>105)cout << "It crits~" << endl;
		else if (dice<95) cout << this->name << " has missed a little bit" << endl;

		cout << "Player " << Player->getName() << " has received a normal attack " << (int)-damage << " points." << endl
			<< "Now " << Player->getName() << " only has " << Player->getHP() << " health points left." << endl;
	}	
}

ostream& operator<< (ostream& os, const  ZombieMonster& rhs)
{
	cout << "Monster: " << rhs.name << endl;
	cout << "HP: " << rhs.getHP() << "/" << rhs.max_hp << endl;
	cout << "MP: " << rhs.getMP() << "/" << rhs.max_mp << endl;
	cout << "Exp: " << rhs.exp << endl;
	cout << "Att: " << rhs.attack << endl;
	cout << "Def: " << rhs.defense << endl;
	return os;
}