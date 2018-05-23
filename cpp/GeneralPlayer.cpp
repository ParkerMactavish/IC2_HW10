#include <string>
#include <cmath>
#include <iostream>
#include "..\header\GeneralPlayer.h"
#include <cstdlib>
#include "..\header\abstractMonster.h"

using namespace std;

void GeneralPlayer::setName(string Name){this->name=Name;}

void GeneralPlayer::setHP(int HP)
{
	if(HP>=0&&HP<=this->max_hp)
	{
		this->hp=HP;
	}
	else if(this->max_hp<HP)
	{
		this->hp=max_hp;
		cout<<"Warning: HP has exceeded, HP is max."<<endl;
	}
	else
	{
		cout<<"Error: HP of "<<this->getName()<<" is smaller than zero."<<endl;
		this->hp=0;
	}
}

void GeneralPlayer::setMP(int MP)
{
	if(MP>=0&&MP<=this->max_mp)
	{
		this->mp=MP;
	}
	else if(this->max_mp<MP)
	{		
		this->mp=this->max_mp;
		cout<<"Warning: MP has exceeded, MP is max."<<endl;
	}
	else
	{
		cout<<"Error: MP of "<<this->getName()<<" is smaller than zero."<<endl;
		this->mp=0;
	}
}

void GeneralPlayer::setExp(int Exp)
{
	if(Exp>=0)
	{
		if(Exp<=ceil(pow(10, log2(this->level))))
		{
			this->exp=ceil(pow(10, log2(this->level)));
		}
		else 
		{
			this->exp=Exp;
			int tmpLevel=this->getLevel();
			for(; ceil(pow(10, log2(tmpLevel+1)))<=Exp; tmpLevel++);
			this->setLevel(tmpLevel);
		}
	}
	else
	{
		cout<<"Error: Exp of "<<this->getName()<<" is smaller than zero."<<endl;
	}
}

void GeneralPlayer::levelUp()
{
	this->setLevel(this->level+1);
}

void GeneralPlayer::setLevel(int Level)
{
	if(Level>0&&(Level>this->level||this->constructFlag==0))
	{
		this->level=Level;
		this->setAttr(Level);		
		this->setExp(ceil(pow(10, log2(this->level))));
	}
	else if (Level > 0 && Level == this->level);
	else if (Level<this->level)
	{
		cout << "Error: Level of " << this->getName() << " is smaller than or equal to previous." << endl;
	}
	else
	{
		cout<<"Error: Level of "<<this->getName()<<" is smaller than one."<<endl;
	}
}

void GeneralPlayer::setAttr(int Level)
{
	this->max_hp=100+10*Level;
	this->hp=this->max_hp;
	this->max_mp=40+5*Level;
	this->mp=this->max_mp;
	this->lvup_exp=ceil(pow(10, log2(this->level+1)));
	this->attack=20+5*Level;
	this->defense=20+5*Level;
}

void GeneralPlayer::setMoney(int money)
{
	if (money >= 0) this->money = money;
	else
	{
		cout << "Error: Player " << this->getName() << " has debt?" << endl;
		this->money = 0;
	}
}

GeneralPlayer::GeneralPlayer()
{
	this->constructFlag=0;
	this->setLevel(1);
	this->setName("anonymous");
	this->setMoney(0);
	this->constructFlag=1;
}

GeneralPlayer::GeneralPlayer(int level)
{
	this->constructFlag=0;
	this->setLevel(level);
	this->setName("anonymous");
	this->setMoney(0);
	this->constructFlag=1;
}

GeneralPlayer::GeneralPlayer(int level, string name)
{
	this->constructFlag=0;
	this->setLevel(level);
	this->setName(name);
	this->setMoney(0);
	this->constructFlag=1;
}

GeneralPlayer::GeneralPlayer(const GeneralPlayer& outer)
{
	this->constructFlag=0;
	this->setLevel(outer.getLevel());
	this->setHP(outer.getHP());
	this->setMP(outer.getMP());
	this->setExp(outer.getExp());
	this->setName(outer.getName());
	this->setMoney(outer.getMoney());
	this->constructFlag=1;
}

string GeneralPlayer::getName() const{return this->name;}

int GeneralPlayer::getHP() const{return this->hp;}

int GeneralPlayer::getMP() const{return this->mp;}

int GeneralPlayer::getExp() const{return this->exp;}

int GeneralPlayer::getLevel() const{return this->level;}

int GeneralPlayer::getAtt() const{return this->attack;}

int GeneralPlayer::getDef() const{return this->defense;}

int GeneralPlayer::getMoney() const { return this->money; }

void GeneralPlayer::increaseHP(int num)
{
	this->setHP(this->getHP() + num);
}

void GeneralPlayer::increaseMP(int num)
{
	this->setMP(this->getMP() + num);
}

void GeneralPlayer::increaseExp(int num)
{
	if(num>=0) this->setExp(this->exp+num);
	else cout<<"Error: the increment of Exp should be a positive integer."<<endl;
}

void GeneralPlayer::recoverHP(){this->setHP(this->max_hp);}

void GeneralPlayer::recoverMP(){this->setMP(this->max_mp);}

ostream& operator<< (ostream& os, GeneralPlayer& rhs)
{
	cout<<"Player: "<<rhs.name<<endl;
	cout<<"Level: "<<rhs.level<<endl;
	cout<<"HP: "<<rhs.hp<<"/"<<rhs.max_hp<<endl;
	cout<<"MP: "<<rhs.mp<<"/"<<rhs.max_mp<<endl;
	cout<<"Exp: "<<rhs.exp<<endl;
	cout<<rhs.lvup_exp-rhs.exp<<" to go to level up"<<endl;
	cout<<"Att: "<<rhs.attack<<endl;
	cout<<"Def: "<<rhs.defense<<endl;
	cout << "Money: " << rhs.money << endl;
	return os;
}

void GeneralPlayer::attackTo(AbstractMonster* AM)
{
	float dice = rand() % 200;
	float damage = -((dice - 100.0 + 1000.0) / 1000.0)*(float)(this->getAtt()) + (float)AM->defense;
	damage = damage <= 0 ? damage : 0;
	AM->setHP(AM->getHP() + damage);

	if (damage == 0) cout << "Defense of " << AM->name << " has TOTALLY blocked the attack from " << this->getName() << endl;
	else if (dice>105)cout << "You crits~" << endl;
	else if (dice<95) cout << "You have missed a little bit" << endl;

	cout << "Monster " << AM->name << " has received a normal attack " << (int)-damage << " points." << endl
		<< "Now " << AM->name << " only has " << AM->getHP() << " health points left." << endl;
	if (AM->getHP() == 0)
	{
		cout << "Player " << this->getName() << " has killed " << AM->name << "~" << endl;
		this->increaseExp(AM->exp);
		this->setMoney(this->getMoney() + AM->money);
		AM = NULL;
		//delete AM;
		//cout << "There are only " << AbstractMonster::count << " left."<<endl;
	}
	cout << endl;
}

void GeneralPlayer::specialSkill() {}

string GeneralPlayer::serialize() const
{
	string output;
	output += "#";
	output += this->getName(); output += ":";
	output += this->getHP(); output += ":";
	output += this->getMP(); output += ":";
	output += this->getExp(); output += ":";
	output += this->getMoney(); output += "@";
	return output;
}

void GeneralPlayer::unserialize(string input)
{
	string::iterator it = input.begin(); it++;

	string name = "";
	for (; *it != ':'; it++) name += *it;
	it++; this->setName(name);

	int hp = 0;
	for (; *it != ':'; it++) { hp *= 10; hp += *it - '0'; }
	it++; this->setHP(hp);

	int mp = 0;
	for (; *it != ':'; it++) { mp *= 10; mp += *it - '0'; }
	it++; this->setMP(mp);

	int exp = 0;
	for (; *it != ':'; it++) { exp *= 10; exp += *it - '0'; }
	it++; this->setExp(exp);

	int money = 0;
	for (; it != input.end(); it++) { money *= 10; money += *it - '0'; }
	it++; this->setMoney(money);
}