#pragma once
#include "Preparat.h"

class Bautura : public Preparat
{
private:
	bool are_alcool = false;
	int nr_sticle = 0;
public:
	Bautura(const char* nume, int nr_sticle)
		: Preparat(nume), nr_sticle(nr_sticle){}

	Bautura& operator= (const Bautura& other)
	{
		if (this == &other)
			return *this;
		
		Preparat::operator=(other);

		are_alcool = other.are_alcool;
		return *this;
	}

	void setAlcoolTrue()
	{
		are_alcool = true;
	}

	int getNrSticle()
	{
		return nr_sticle;
	}

	bool getAlcool()
	{
		return are_alcool;
	}

	void subNr()
	{
		nr_sticle--;
	}

	void addIngredient(MateriePrima ingredient)
	{
		getIngrediente().push_back(ingredient);
	}

	void afiseazaDetalii() const {
		cout << getNumePreparat() << endl;
		cout << (are_alcool ? "Contine alcool!\n" : "Nu contine alcool.\n");
		cout << "Ingrediente: ";
		for (const auto& ing : getIngrediente())
			cout << ing.getNumeIngredient() << ' ';
		cout << endl << endl;
	}
};