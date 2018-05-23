#ifndef ORCPLAYER_H_
#define ORCPLAYER_H_

#include "GeneralPlayer.h"
#include <iostream>
#include <string>

using namespace std;

class OrcPlayer: public GeneralPlayer
{
	public:
		OrcPlayer();
		OrcPlayer(int);
		OrcPlayer(int, string);
		OrcPlayer(const OrcPlayer&);
		friend ostream& operator<<(ostream& os, OrcPlayer& rhs);
		void setLevel(int);
		//void setExp(int);
		void increaseExp(int);
		void levelUp();
		
		//int getExp()const;
		
	private:
		void setAttr(int);
		//int exp;
};


#endif