#include <iostream>
#include <cstdlib>
#include "..\header\GeneralPlayer.h"
#include "..\header\abstractMonster.h"
#include "..\header\Battle.h"
#include "..\header\GoblinMonster.h"
#include "..\header\JWMonster.h"
#include "..\header\ZombieMonster.h"

using namespace std;

Battle::Battle(GeneralPlayer* GP[], AbstractMonster* AM[], int playerNum, int monsterNum)
{
	if(monsterNum>=0)this->monsterNum = monsterNum;
	else this->monsterNum = 0;
	if(playerNum>=0) this->playerNum = playerNum;
	else this->playerNum = 0;
	this->turnLimit = -1;
	ActionList = new Character[this->playerNum + this->monsterNum];
	for (int i = 0; i < playerNum; i++)
	{
		ActionList[i].type = 'p';
		ActionList[i].alive = 1;
		ActionList[i].instance = GP[i];}
	for (int i = 0; i < monsterNum; i++)
	{
		ActionList[i + playerNum].type = 'm';
		ActionList[i + playerNum].alive = 1;
		ActionList[i + playerNum].instance = AM[i];}
	this->currentCharIndex = 0;
	this->turn = 0;
}

Battle::Battle(GeneralPlayer* GP[], AbstractMonster* AM[], int playerNum, int monsterNum, int turnLimit)
{
	if (monsterNum >= 0)this->monsterNum = monsterNum;
	else this->monsterNum = 0;
	if (playerNum >= 0) this->playerNum = playerNum;
	else this->playerNum = 0;
	if (turnLimit > 0) this->turnLimit = turnLimit;
	else this->turnLimit = 0;
	ActionList = new Character[this->playerNum + this->monsterNum];
	for (int i = 0; i < playerNum; i++)
	{
		ActionList[i].type = 'p';
		ActionList[i].alive = 1;
		ActionList[i].instance = GP[i];
	}
	for (int i = 0; i < monsterNum; i++)
	{
		ActionList[i + playerNum].type = 'm';
		ActionList[i + playerNum].alive = 1;
		ActionList[i + playerNum].instance = AM[i];
	}
	this->currentCharIndex = 0;
	this->turn = 0;
}

bool Battle::nextActor()
{
	if (this->getPlayerCount(1) == 0 || this->getMonsterCount(1) == 0)
	{
		return true;
	}
	else if (this->turn <= this->turnLimit||this->turnLimit==-1)
	{
		if (this->getCurrentActor().type == 'p')
		{
			if (static_cast<GeneralPlayer*>(this->getCurrentActor().instance)->getHP()>0)
			{
				int index = 0;
				for (int i = 1; i < monsterNum; i++)
				{
					if (static_cast <AbstractMonster*> (this->getMonsters()[i].instance)->getHP() < static_cast<AbstractMonster*>(this->getMonsters()[index].instance)->getHP()
						&& static_cast <AbstractMonster*> (this->getMonsters()[i].instance)->getHP() > 0)
						index = i;
				}
				static_cast<GeneralPlayer*> (this->getCurrentActor().instance)->attackTo(static_cast<AbstractMonster*> (getMonsters()[index].instance));
				if (static_cast<AbstractMonster*>(this->getMonsters()[index].instance)->getHP() == 0)
				{
					this->ActionList[playerNum+index].alive = false;
					cout << this->getMonsters()[index].alive << endl;
				}
			}
		}
		else
		{
			if (static_cast<AbstractMonster*>(this->getCurrentActor().instance)->getHP() > 0)
			{
				int index = 0;
				for (int i = 1; i < monsterNum; i++)
				{
					if (static_cast <GeneralPlayer*> (this->getPlayers()[i].instance)->getHP() < static_cast<GeneralPlayer*>(this->getPlayers()[index].instance)->getHP()
						&& static_cast <GeneralPlayer*> (this->getPlayers()[i].instance)->getHP() > 0)
						index = i;
				}
				static_cast<AbstractMonster*> (this->getCurrentActor().instance)->attackTo(static_cast<GeneralPlayer*> (getPlayers()[index].instance));
				if (static_cast<GeneralPlayer*>(this->getPlayers()[index].instance)->getHP() == 0)
				{
					this->ActionList[index].alive = false;
					cout << this->getPlayers()[index].alive << endl;
				}
			}			
		}
		if (this->getMonsterCount(1) < this->getMonsterCount())
		{
			Character* tmpActionList = new Character[this->getPlayerCount() + this->getMonsterCount(1)];
			int tmpIndex = 0;
			for (int i = 0; i < (this->getMonsterCount() + this->getPlayerCount()); i++)
			{
				if (this->ActionList[i].alive)
				{
					tmpActionList[tmpIndex] = this->ActionList[i];
					tmpIndex++;
				}
			}
			delete this->ActionList;
			this->ActionList = tmpActionList;
		}
		currentCharIndex++;
		if (this->currentCharIndex == this->monsterNum + this->playerNum)
		{
			this->currentCharIndex = 0;
			this->turn++;
		}
		if (this->turn == turnLimit) return true;
		else return false;
	}
}

int Battle::getTurnCount()const { return this->turn; }

int Battle::getTurnLimit()const { return this->turnLimit; }

int Battle::getPlayerCount()const { return this->playerNum; }

int Battle::getPlayerCount(bool flag)const
{
	if (flag)
	{
		int count = 0;
		for (int i = 0; i < playerNum; i++)
		{
			if (ActionList[i].alive)
				count++;
		}
		return count;
	}
	else return 0;
}

int Battle::getMonsterCount()const { return this->monsterNum; }

int Battle::getMonsterCount(bool flag)const
{
	if (flag)
	{
		int count = 0;
		for (int i = 0; i < monsterNum; i++)
		{
			if (ActionList[this->playerNum + i].alive)
				count++;
		}
		return count;
	}
	else return 0;
}

Character Battle::getCurrentActor()
{
	return this->ActionList[currentCharIndex];
}

Character* Battle::getPlayers()
{
	Character* result=new Character[playerNum];
	for (int i = 0; i < playerNum; i++) result[i] = ActionList[i];
	return result;
}

Character* Battle::getMonsters()
{
	Character* result = new Character[monsterNum];
	for (int i = 0; i < monsterNum; i++) result[i] = ActionList[i+this->playerNum];
	return result;
}

ostream& operator<<(ostream& os, Battle& B)
{
	cout << "Monster Number: " << B.getMonsterCount() << endl
		<< "Alive Monster Number: " << B.getMonsterCount(1) << endl
		<< "Player Number: " << B.getPlayerCount() << endl
		<< "Alive Player Number: " << B.getPlayerCount(1) << endl
		<< "Turn/Limit: " << B.getTurnCount() << "/" << B.getTurnLimit() << endl
		<< "Current Chracter: " << endl << endl;
	for (int i = 0; i < B.playerNum; i++) cout << *static_cast<GeneralPlayer*>(B.getPlayers()[i].instance) << endl;
	//cout << *(static_cast<GoblinMonster*>(B.getMonsters()[0].instance)) << endl;
	//for (int i = 0; i < B.monsterNum; i++)  cout << *(static_cast<AbstractMonster*>(B.getMonsters()[0].instance)) << endl;
	for (int i = 0; i < B.monsterNum; i++)
	{
		if (static_cast<AbstractMonster*>(B.getMonsters()[i].instance)->name == "Goblin")cout << *static_cast<GoblinMonster*>(B.getMonsters()[i].instance)<<endl;
		else if (static_cast<AbstractMonster*>(B.getMonsters()[i].instance)->name == "JW the Boss")cout << *static_cast<JWMonster*>(B.getMonsters()[i].instance)<<endl;
		else if (static_cast<AbstractMonster*>(B.getMonsters()[i].instance)->name == "Zombie")cout << *static_cast<ZombieMonster*>(B.getMonsters()[i].instance)<<endl;
	}
	return os;
}