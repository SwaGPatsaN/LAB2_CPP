#include <string>
#include "ks.h"
#include <sstream>
using namespace std;

ks::ks() : name(""), NumFac(0), NumWorkFac(0), eff(0) {}

ks::ks(string n, int nf, int nwf, int e)
{
	name = n;
	NumFac = nf;
	NumWorkFac = nwf;
	eff = e;
}

string ks::GetName()
{
	return name;
}

int ks::GetNumFac()
{
	return NumFac;
}

int ks::GetNumWorkFac()
{
	return NumWorkFac;
}

int ks::GetEff()
{
	return eff;
}

void ks::SetNumWorkFac(int A)
{
	NumWorkFac = A;
}

string ks::ToString() const {
	ostringstream oss;
	oss << "Название: " << name << "\n"
		<< "Количество цехов: " << NumFac << "\n"
		<< "Работающих цехов: " << NumWorkFac << "\n"
		<< "Эффективность: " << eff << "%\n";
	return oss.str();
}