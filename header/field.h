#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <cstdlib>
#include <fstream>
#include <stack>

using namespace std;


class field
{
	public:
		field(fstream&);//first is row 橫的數量, second is column直的數量
		int move(char);
		friend ostream& operator<<(ostream&, field&);
	private:
		void setView();
		void setMask();
		pair<int, int> Size;//initialized after this->read
		pair<int, int> Start;//initialized after this->read
		pair<int, int> End;//initialized after this->read
		pair<int, int> UpperLeft;//store the viewing's upper left position
		pair<int, int> Player;//store the player's position
		vector<vector<int>> fieldMap;//initialized after this->read, store the map
		vector<vector<int>> fieldMask;//initialized after this->read, store the mask
};

#endif