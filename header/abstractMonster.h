#ifndef ABSTRACT_MONSTER_H
#define ABSTRACT_MONSTER_H

#include <iostream>
#include <cstdlib>
#include <string>
class GeneralPlayer;

using namespace std;

class AbstractMonster
{
	public:
		const string name;
		const int attack;
		const int defense;
		const int exp;
		const int max_hp;
		const int max_mp;
		const int money;
		
		AbstractMonster(string, int, int, int, int, int, int);
		virtual ~AbstractMonster();
		
		void setHP(int);
		int getHP()const;
		void setMP(int);
		int getMP()const;
		
		virtual void attackTo(GeneralPlayer*)=0;

		string serialize() const;
		void unserialize(string);
		
		static int count;

		friend ostream& operator<<(ostream&, AbstractMonster&);
		
	private:
		int hp;
		int mp;
};

#endif