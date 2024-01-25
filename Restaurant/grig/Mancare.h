#pragma once
#include "Preparat.h"

class Mancare : public Preparat
{
private:
	bool vegan = false;
public:
	Mancare(const char* nume)
		: Preparat(nume){}

	Mancare& operator=(const Mancare& other)
	{
		if (this == &other)
			return *this;

		Preparat::operator=(other);

		vegan = other.vegan;
		return *this;
	}

	void afiseazaDetalii() const {
		cout << getNumePreparat() << endl;
		cout << (vegan ? "Preparat vegan!\n" : "Preparat non-vegan\n");
		cout << "Ingrediente: ";
		for (const auto& ing : getIngrediente())
			cout << ing.getNumeIngredient() << " ";
		cout << endl << endl;
	}

	void setVegan()
	{
		vegan = true;
	}

	bool getVegan()
	{
		return vegan;
	}

	void addIngredient(MateriePrima ingredient)
	{
		getIngrediente().push_back(ingredient);
	}

};