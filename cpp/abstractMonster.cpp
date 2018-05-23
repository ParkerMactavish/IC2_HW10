#include "..\header\abstractMonster.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void AbstractMonster::setHP(int HP)
{
	if(HP>=0&&HP<=this->max_hp)
	{
		this->hp=HP;
	}
	else if(this->max_hp<HP)
	{
		this->hp=max_hp;
		//cout<<"Warning: HP has exceeded, HP is max."<<endl;
	}
	else
	{
		cout<<"Error: HP of "<<this->name<<" is smaller than zero."<<endl;
		this->hp=0;
	}
}

int AbstractMonster::getHP()const {return this->hp;}

void AbstractMonster::setMP(int MP)
{
	if(MP>=0&&MP<=this->max_mp)
	{
		this->mp=MP;
	}
	else if(this->max_mp<MP)
	{		
		this->mp=this->max_mp;
		//cout<<"Warning: MP has exceeded, MP is max."<<endl;
	}
	else
	{
		cout<<"Error: MP of "<<this->name<<" is smaller than zero."<<endl;
		this->mp=0;
	}
}

int AbstractMonster::getMP() const{return this->mp;}

int AbstractMonster::count=0;

AbstractMonster::AbstractMonster(string name, int attack, int defense, int exp, int max_hp, int max_mp, int money):name(name), attack(attack), defense(defense), exp(exp), max_hp(max_hp), max_mp(max_mp), money(money)
{
	setHP(max_hp);
	setMP(max_mp);
	count++;
}

AbstractMonster::~AbstractMonster()
{
	count--;
}

string AbstractMonster::serialize() const
{
	string output;
	output += "@";
	output += this->getHP(); output += ":";
	output += this->getMP(); output += ":";
	return output;
}

void AbstractMonster::unserialize(string input)
{
	string::iterator it = input.begin(); it++; 

	int hp=0;
	for (; *it != ':'; it++) { hp *= 10; hp += *it - '0'; }
	it++; this->setHP(hp);

	int mp = 0;
	for (; it!=input.end(); it++) { mp *= 10; mp += *it - '0'; }
	it++; this->setMP(mp);
}

ostream& operator<< (ostream& os, const  AbstractMonster& rhs)
{
	cout << "Monster: " << rhs.name << endl;
	cout << "HP: " << rhs.getHP() << "/" << rhs.max_hp << endl;
	cout << "MP: " << rhs.getMP() << "/" << rhs.max_mp << endl;
	cout << "Exp: " << rhs.exp << endl;
	cout << "Att: " << rhs.attack << endl;
	cout << "Def: " << rhs.defense << endl;
	return os;
}