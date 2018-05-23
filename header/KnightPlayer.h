#ifndef KNIGHTPLAYER_H_
#define KNIGHTPLAYER_H_

#include "GeneralPlayer.h"
#include <iostream>
#include <string>

using namespace std;

class KnightPlayer: public GeneralPlayer
{
	public:
		KnightPlayer();
		KnightPlayer(int);
		KnightPlayer(int, string);
		KnightPlayer(const KnightPlayer&);
		friend ostream& operator<<(ostream& os, KnightPlayer& rhs);
		void setLevel(int);
		//void setExp(int);
		void increaseExp(int);
		void levelUp();
		
		//int getExp()const;
		
		void heal();

		void specialSkill();
		
	private:
		void setAttr(int);
		//int exp;
};


#endif