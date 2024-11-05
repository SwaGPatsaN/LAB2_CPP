#pragma once
#include <string>
using namespace std;
struct pipe
{
	string name;
	int length;
	int diametr;
	bool InRepair;
	pipe(string n, int l, int d, bool rep);
	pipe();
	string GetName() const;
	int GetLength() const;
	int GetDiameter() const;
	bool GetInRepair() const;
	void SetInRepair(bool s);
	string ToString() const;
};
