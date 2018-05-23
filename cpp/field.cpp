#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <set>
#include "..\header\field.h"

using namespace std;

field:: field(fstream& fs)
{
	char SkipChar;
	fs >> Size.first >> SkipChar >> Size.second;
	
	vector<int> TmpCol(Size.second, 0);
	for(int i=0; i<Size.first; i++)
	{
		fieldMask.push_back(TmpCol);
		fieldMap.push_back(TmpCol);
	}
	
	for (int col = 0; col<Size.second; col++)
	{
		for (int row = 0; row < Size.first - 1; row++)
		{
			fs >> fieldMap[row][col] >> SkipChar;
			if (fieldMap[row][col] == 200) this->Start = make_pair(row, col);
			else if (fieldMap[row][col] == 201) this->End = make_pair(row, col);
		}
		fs >> fieldMap[Size.first - 1][col];
	}

	this->Player = this->Start;
	setMask();
	setView();
}

int field::move(char dir)
{
	switch (dir)
	{
		case 'U':
			if (Player.second > 0)
			{
				Player.second--;
				setMask();
				setView();
			}
			break;

		case 'D':
			if (Player.second < Size.second - 1)
			{
				Player.second++;
				setMask();
				setView();
			}
			break;

		case 'L':
			if (Player.first > 0)
			{
				Player.first--;
				setMask();
				setView();
			}
			break;

		case'R':
			if (Player.first < Size.first - 1)
			{
				Player.first++;
				setMask();
				setView();
			}
	}
	return this->fieldMap[Player.first][Player.second];
}

void field::setMask()
{
	this->fieldMask[this->Player.first][this->Player.second] = 1;
	if (Player.first > 0)this->fieldMask[this->Player.first - 1][this->Player.second] = 1;
	if (Player.first < this->Size.first - 1)this->fieldMask[this->Player.first + 1][this->Player.second] = 1;
	if (Player.second > 0)this->fieldMask[this->Player.first][this->Player.second - 1] = 1;
	if (Player.second < this->Size.second - 1)this->fieldMask[this->Player.first][this->Player.second + 1] = 1;
	if (Player.first > 0 && Player.second > 0)this->fieldMask[this->Player.first - 1][this->Player.second - 1] = 1;
	if (Player.first > 0 && Player.second < this->Size.second - 1)this->fieldMask[this->Player.first - 1][this->Player.second + 1] = 1;
	if (Player.first < this->Size.first - 1 && Player.second > 0)this->fieldMask[this->Player.first + 1][this->Player.second - 1] = 1;
	if (Player.first < this->Size.first - 1 && Player.second < this->Size.second - 1)this->fieldMask[this->Player.first + 1][this->Player.second + 1] = 1;
}

void field::setView()
{
	if (Player.first < 2) UpperLeft.first = 0;
	else if (Player.first > Size.first - 3) UpperLeft.first = Size.first - 5;
	else UpperLeft.first = Player.first - 2;
	if (Player.second < 2) UpperLeft.second = 0;
	else if (Player.second > Size.second - 3) UpperLeft.second = Size.second - 5;
	else UpperLeft.second = Player.second - 2;
}

ostream& operator<<(ostream& os, field& F)
{
	for (int col = F.UpperLeft.second; col < F.UpperLeft.second+5; col++)
	{
		for (int row = F.UpperLeft.first; row < F.UpperLeft.first+5; row++)
		{
			if (row == F.Player.first&&col == F.Player.second) cout << " P";
			else if (F.fieldMask[row][col] == 0)
				cout << "█";
			else if (F.fieldMap[row][col] > 201) cout << "Ⅴ";
			else if (F.fieldMap[row][col] == 200 || F.fieldMap[row][col] == 201) cout << "▲";
			else cout << "□";
		}
		cout << endl;
	}
	return os;
}




