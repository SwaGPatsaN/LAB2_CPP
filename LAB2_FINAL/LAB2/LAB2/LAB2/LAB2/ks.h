#pragma once
#include <string>
using namespace std;
struct ks
{
	string name;
	int NumFac;
	int NumWorkFac;
	int eff;
	ks(string n, int nf, int nwf, int e);
	ks();
	string GetName();
	int GetNumFac();
	int GetNumWorkFac();
	int GetEff();
	void SetNumWorkFac(int A);
	string ToString() const;
};