#ifndef GENERALPLAYER_H_
#define GENERALPLAYER_H_

#include <string>
#include <iostream>
class AbstractMonster;

using namespace std;

class GeneralPlayer
{
	public:		
		void setName(string);
		void setHP(int);
		void setMP(int);
		void setExp(int);
		void setLevel(int);
		void setMoney(int);
		GeneralPlayer();
		GeneralPlayer(int);
		GeneralPlayer(int, string);
		GeneralPlayer(const GeneralPlayer&);
		
		string getName() const;
		int getHP() const;
		int getMP() const;
		int getExp() const;
		int getLevel() const;
		int getAtt() const;
		int getDef() const;
		int getMoney() const;
		void increaseHP(int);
		void increaseMP(int);
		void increaseExp(int);
		void recoverHP();
		void recoverMP();
		virtual void levelUp();
		friend ostream& operator<< (ostream&, GeneralPlayer&);
		
		void attackTo(AbstractMonster*);
		virtual void specialSkill();

		string serialize() const;
		void unserialize(string);

	protected:
		int money;
		int level;
		int attack;
		int defense;
		int max_hp;
		int max_mp;		
		int lvup_exp;
		int constructFlag;
	
	private:
		string name;
		int hp;
		int mp;
		int exp;
		virtual void setAttr(int);
};


#endif