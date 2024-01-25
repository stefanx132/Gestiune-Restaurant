#pragma once
#include <string>
#include "Preparat.h";
class Comanda
{
	string nume;
	vector<Preparat*> preparate;

public:
	Comanda(string nume) : nume(nume) {}

	void setName(string new_nume){
		nume = new_nume;
	}

	string getNume()
	{
		return nume;
	}

	void addPreparat(Preparat* prep)
	{
		preparate.push_back(prep);
	}

	void afisareComanda()
	{
		for (auto prep : preparate)
			std::cout<< prep->getNumePreparat() << endl;
	}

	vector<Preparat*> getPreparate()
	{
		return preparate;
	}
};

