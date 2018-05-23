#ifndef MAGICIANPLAYER_H_
#define MAGICIANPLAYER_H_

#include "GeneralPlayer.h"
#include <iostream>
#include <string>

using namespace std;

class MagicianPlayer: public GeneralPlayer
{
	public:
		MagicianPlayer();
		MagicianPlayer(int);
		MagicianPlayer(int, string);
		MagicianPlayer(const MagicianPlayer&);
		friend ostream& operator<<(ostream& os, MagicianPlayer& rhs);
		void setLevel(int);
		//void setExp(int);
		void increaseExp(int);
		void levelUp();
		
		//int getExp()const;
		
		void pray();
		void specialSkill();
		
	private:
		void setAttr(int);
		//int exp;
};


#endif