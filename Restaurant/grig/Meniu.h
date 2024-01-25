#pragma once
#include "MateriePrima.h"
#include "Bautura.h"
#include "Mancare.h"
#include "Desert.h"
#include <list>
class Meniu
{
private:
	vector<MateriePrima> ing_disponibile;
	vector<Preparat*> fel_principal;
	vector<Preparat*> deserturi;
	list<Preparat*> bauturi;

public:

	void afisareIngredienteDisponibile()
	{
		std::cout << "Ingrediente Disponibile:\n";
		for (const auto& ing : ing_disponibile)
			ing.afisare();
		std::cout << endl;
	}

	void afisareMeniu() {
		cout << "-------------------MENIU-------------------\n\n";
		cout << "Feluri Principale:\n";
		for (const auto& fel : fel_principal)
			fel->afiseazaDetalii();

		cout << "-------------------------------------------\n\n";
		
		cout << "Deserturi:\n";
		for (const auto& desert : deserturi)
			desert->afiseazaDetalii();

		cout << "-------------------------------------------\n\n";
		
		cout << "Bauturi:\n";
		for (const auto& b : bauturi)
			b->afiseazaDetalii();
	
		cout << "-------------------------------------------\n\n";
	}

	void addMancare(Mancare* mancare)
	{
		fel_principal.push_back(mancare);
	}

	void addDesert(Desert* desert)
	{

		deserturi.push_back(desert);
	}

	void addBautura(Bautura* bautura)
	{
		bauturi.push_back(bautura);
	}

	void addIngredient(MateriePrima ingredient)
	{
		ing_disponibile.push_back(ingredient);
	}

	vector<Mancare*> getFelPrincipal()
	{
		vector<Mancare*> mancare;
		for (Preparat* prep : fel_principal)
		{
			Mancare* m = dynamic_cast<Mancare*>(prep);
			if (m != nullptr)
			{
				mancare.push_back(m);
			}
		}

		return mancare;
	}

	vector<Desert*> getDeserturi()
	{
		vector<Desert*> deserts;
		for (Preparat* prep : deserturi)
		{
			Desert* d = dynamic_cast<Desert*>(prep);
			if (d != nullptr)
			{
				deserts.push_back(d);
			}
		}
		return deserts;
	}

	list<Bautura*> getBauturi()
	{
		std::list<Bautura*> blist;

		for (Preparat* prep : bauturi) {
			Bautura* baut = dynamic_cast<Bautura*>(prep);
			if (baut != nullptr) {
				blist.push_back(baut);
			}
		}

		return blist;
	}

	vector<MateriePrima>& getIngredienteMeniu()
	{
		return ing_disponibile;
	}

	~Meniu() {
		for (Preparat* prep : fel_principal) {
			delete prep;
		}

		for (Preparat* prep : deserturi) {
			delete prep;
		}

		for (Preparat* prep : bauturi) {
			delete prep;
		}
	}

};

