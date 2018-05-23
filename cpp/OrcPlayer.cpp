#include "..\header\OrcPlayer.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

OrcPlayer::OrcPlayer()
{
	this->constructFlag=0;
	this->setLevel(1);
	this->setName("anonymous");
	this->constructFlag=1;
}

OrcPlayer::OrcPlayer(int level)
{
	this->constructFlag=0;
	this->setLevel(level);
	this->setName("anonymous");
	this->constructFlag=1;
}

OrcPlayer::OrcPlayer(int level, string name)
{
	this->constructFlag=0;
	this->setLevel(level);
	this->setName(name);
	this->constructFlag=1;
}

OrcPlayer::OrcPlayer(const OrcPlayer& outer)
{
	this->constructFlag=0;
	this->setLevel(outer.getLevel());
	this->setHP(outer.getHP());
	this->setMP(outer.getMP());
	this->setExp(outer.getExp());
	this->setName(outer.getName());
	this->constructFlag=1;
}

/*void OrcPlayer::setExp(int Exp)
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

void OrcPlayer::increaseExp(int num)
{
	cout<<this->getExp()+num<<endl;
	if(num>=0) this->setExp(this->getExp()+num);
	else cout<<"Error: the increment of Exp should be a positive integer."<<endl;
}

//int OrcPlayer::getExp()const{return this->exp;}

void OrcPlayer::setLevel(int Level)
{
	if(Level>0&&(Level>this->level||this->constructFlag==0))
	{
		this->level=Level;
		this->setAttr(Level);		
		this->setExp(ceil(pow(10, log2(this->level))));
	}
	else if (Level > 0 && Level == this->level);
	else if(Level<this->level)
	{
		cout<<"Error: Level of "<<this->getName()<<" is smaller than or equal to previous."<<endl;
	}
	else
	{
		cout<<"Error: Level of "<<this->getName()<<" is smaller than one."<<endl;
	}
}

void OrcPlayer::setAttr(int Level)
{
	this->max_hp=200+20*level;
	this->setHP(this->max_hp);
	this->max_mp=50+5*level;
	this->setMP(this->max_mp);
	this->attack=50+12*level;
	this->defense=30+10*level;
	this->lvup_exp=ceil(pow(10, log2(this->level+1)));
}

void OrcPlayer::levelUp()
{
	this->setLevel(this->level+1);
}

ostream& operator<< (ostream& os, OrcPlayer& rhs)
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