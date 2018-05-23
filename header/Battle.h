#ifndef BATTLE_H_
#define BATTLE_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include "GeneralPlayer.h"
#include "abstractMonster.h"

using namespace std;

struct Character
{
	char type;
	bool alive;
	void *instance;
};

class Battle
{
	public:
		Battle(GeneralPlayer*[], AbstractMonster*[], int, int);
		Battle(GeneralPlayer*[], AbstractMonster*[], int, int, int);
		bool nextActor();
		int getTurnCount() const;
		int getTurnLimit() const;
		int getPlayerCount() const;
		int getPlayerCount(bool) const;
		int getMonsterCount() const;
		int getMonsterCount(bool) const;
		Character getCurrentActor();
		Character* getPlayers();
		Character* getMonsters();

		friend ostream& operator<<(ostream&, Battle&);

	private:
		Character *ActionList;
		int monsterNum;
		int playerNum;
		int currentCharIndex;
		int turn;
		int turnLimit;
};

#endif