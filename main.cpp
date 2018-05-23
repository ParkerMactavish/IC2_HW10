#include <iostream>
#include <fstream>
#include <cstdlib>
#include <Windows.h>
#include "header\GeneralPlayer.h"
#include "header\OrcPlayer.h"
#include "header\MagicianPlayer.h"
#include "header\KnightPlayer.h"
#include "header\AbstractMonster.h"
#include "header\GoblinMonster.h"
#include "header\ZombieMonster.h"
#include "header\JWMonster.h"
#include "header\Battle.h"
#include "header\field.h"

#define fight 5
#define end 100

using namespace std;

int main()
{
	fstream fs;
	fs.open("maze4.txt", fstream::in);
	field F1(fs);
	cout << F1;
	int flag = 1;
	while (flag != 0)
	{
		if (flag == 1 && ((GetKeyState(0x57) & 0x8000) == 0x8000 || (GetKeyState(0x57) & 0x7FFF) == 0x7FFF))
		{
			flag = 21;
		}

		if (flag == 21 && ((GetKeyState(0x57) | 0x0001) == 0x0001 || (GetKeyState(0x57) | 0x0000) == 0x0000))
		{
			flag = 31;
		}

		if (flag == 31)
		{
			if (F1.move('U') > 201) flag = fight;
			system("CLS");
			cout << F1;
			if (flag == fight) cout << "Into a battle" << endl;
			flag = 1;
		}

		if (flag == 1 && ((GetKeyState(0x41) & 0x8000) == 0x8000 || (GetKeyState(0x41) & 0x7FFF) == 0x7FFF))
		{
			flag = 22;
		}

		if (flag == 22 && ((GetKeyState(0x41) | 0x0001) == 0x0001 || (GetKeyState(0x41) | 0x0000) == 0x0000))
		{
			flag = 32;
		}

		if (flag == 32)
		{
			if(F1.move('L')>201)flag=fight;
			system("CLS");
			cout << F1;
			if (flag == fight) cout << "Into a battle" << endl;
			flag = 1;
		}
		
		if (flag == 1 && ((GetKeyState(0x53) & 0x8000) == 0x8000 || (GetKeyState(0x53) & 0x7FFF) == 0x7FFF))
		{
			flag = 23;
		}

		if (flag == 23 && ((GetKeyState(0x53) | 0x0001) == 0x0001 || (GetKeyState(0x53) | 0x0000) == 0x0000))
		{
			flag = 33;
		}

		if (flag == 33)
		{
			if(F1.move('D')>201)flag=fight;
			system("CLS");
			cout << F1;
			if (flag == fight) cout << "Into a battle" << endl;
			flag = 1;
		}


		if (flag == 1 && ((GetKeyState(0x44) & 0x8000) == 0x8000 || (GetKeyState(0x44) & 0x7FFF) == 0x7FFF))
		{
			flag = 24;
		}

		if (flag == 24 && ((GetKeyState(0x44) | 0x0001) == 0x0001 || (GetKeyState(0x44) | 0x0000) == 0x0000))
		{
			flag = 34;
		}

		if (flag == 34)
		{
			if(F1.move('R')>201)flag=fight;
			system("CLS");
			cout << F1;
			if (flag == fight) cout << "Into a battle" << endl;
			flag = 1;
		}
	}
	return 0;
}