#pragma once
#include "Preparat.h"

class Desert : public Preparat
{
private:
	bool zahar = false;
public:
	Desert(const char* nume)
		: Preparat(nume) {}

	Desert& operator=(const Desert& other)
	{
		if (this == &other)
			return *this;

		Preparat::operator=(other);

		zahar = other.zahar;
		return *this;
	}

	void setZahar()
	{
		zahar = true;
	}

	bool getZahar()
	{
		return zahar;
	}

	void addIngredient(MateriePrima ingredient)
	{
		getIngrediente().push_back(ingredient);
	}

	void afiseazaDetalii() const {
		cout << getNumePreparat() << endl;
		cout << (zahar ? "Contine zahar!\n" : "Nu contine zahar.\n");
		cout << "Ingrediente: ";
		for (const auto& ing : getIngrediente())
			cout << ing.getNumeIngredient() << ' ';
		cout << endl << endl;
	}
};