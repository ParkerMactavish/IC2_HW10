#include "..\header\KnightPlayer.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

KnightPlayer::KnightPlayer()
{
	this->constructFlag=0;
	this->setLevel(1);
	this->setName("anonymous");
	this->constructFlag=1;
}

KnightPlayer::KnightPlayer(int level)
{
	this->constructFlag=0;
	this->setLevel(level);
	this->setName("anonymous");
	this->constructFlag=1;
}

KnightPlayer::KnightPlayer(int level, string name)
{
	this->constructFlag=0;
	this->setLevel(level);
	this->setName(name);
	this->constructFlag=1;
}

KnightPlayer::KnightPlayer(const KnightPlayer& outer)
{
	this->constructFlag=0;
	this->setLevel(outer.getLevel());
	this->setHP(outer.getHP());
	this->setMP(outer.getMP());
	this->setExp(outer.getExp());
	this->setName(outer.getName());
	this->constructFlag=1;
}

/*void KnightPlayer::setExp(int Exp)
{
	if(Exp>=0)
	{
		if(Exp<ceil(pow(10, log2(this->level))))
		{
			this->exp=ceil(pow(10, log2(this->level)));
		}
		else 
		{
			this->exp=Exp;
			
			while(this->exp>this->lvup_exp)
			{
				this->levelUp();
			}
		}
	}
	else
	{
		cout<<"Error: Exp of "<<this->getName()<<" is smaller than zero."<<endl;
	}
}*/

void KnightPlayer::increaseExp(int num)
{
	if(num>=0) this->setExp(this->getExp()+num);
	else cout<<"Error: the increment of Exp should be a positive integer."<<endl;
}

//int KnightPlayer::getExp()const{return this->exp;}

void KnightPlayer::setLevel(int Level)
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

void KnightPlayer::setAttr(int Level)
{
	this->max_hp=150+25*level;
	this->setHP(this->max_hp);
	this->max_mp=70+10*level;
	this->setMP(this->max_mp);
	this->attack=40+10*level;
	this->defense=20+12*level;
	this->lvup_exp=ceil(pow(10, log2(this->level+1)));
}

void KnightPlayer::levelUp()
{
	this->setLevel(this->level+1);
}

void KnightPlayer::heal()
{
	if(this->getMP()>=this->getLevel()*5)
	{
		this->setMP(this->getMP()-this->getLevel()*5);
		this->setHP(this->getHP()+this->getLevel()*10);
	}
	else
	{
		cout<<"Error: Not enough MP for healing."<<endl;
	}
}

ostream& operator<< (ostream& os, KnightPlayer& rhs)
{
	cout<<"Player: "<<rhs.getName()<<endl;
	cout<<"Level: "<<rhs.level<<endl;
	cout<<"HP: "<<rhs.getHP()<<"/"<<rhs.max_hp<<endl;
	cout<<"MP: "<<rhs.getMP()<<"/"<<rhs.max_mp<<endl;
	cout<<"Exp: "<<rhs.getExp()<<endl;
	cout<<rhs.lvup_exp-rhs.getExp()<<" to go to level up"<<endl;
	cout<<"Att: "<<rhs.attack<<endl;
	cout<<"Def: "<<rhs.defense<<endl;
	cout << "Money: " << rhs.money << endl;
	return os;
}

void KnightPlayer::specialSkill() { this->heal(); }