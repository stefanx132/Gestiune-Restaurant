#pragma once
#include "MateriePrima.h"
#include <vector>
#include <string.h>
#include <iostream>
using namespace std;
class Preparat {
private:
	char* nume = nullptr;
	vector<MateriePrima> ingrediente;

public:
	Preparat() {}

	Preparat(const char* nume)
	{
		if (nume != nullptr) {
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
	}
	 
	Preparat(const char* nume, const vector<MateriePrima> ing) : ingrediente(ing) {
		if (nume != nullptr) {
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
	}

	Preparat(const Preparat& p) : ingrediente(p.ingrediente) {
		if (p.nume != nullptr) {
			this->nume = new char[strlen(p.nume) + 1];
			strcpy(this->nume, p.nume);
		}
	}

	friend ostream& operator<<(ostream& out, const Preparat& p) {
		if (p.nume != nullptr) {
			out << "Preparat: " << p.nume << "\n";
		}
		else {
			out << "Preparat: -\n";
		}
		for (const auto& ing : p.ingrediente)
			out << ing.getNumeIngredient() << ' ';
		out << '\n';
		return out;
	}

	friend istream& operator>>(istream& in, Preparat& p) {
		cout << "\nIntroduceti nume: ";
		string buffer;
		in >> buffer;
		delete[] p.nume;
		p.nume = new char[buffer.size() + 1];
		strcpy(p.nume, buffer.data());

		cout << "\nCate ingrediente are reteta? ";
		int numIngredients;
		in >> numIngredients;
		p.ingrediente.clear(); // Clear existing ingredients

		for (int i = 0; i < numIngredients; ++i) {
			MateriePrima mp;
			cout << "\nIngredient " << i + 1 << ":\n";
			in >> mp;
			p.ingrediente.push_back(mp);
		}

		return in;
	}

	vector<MateriePrima>& getIngrediente() 
	{
		return ingrediente;
	}

	void setNumePreparat(const char* nume) {
		delete[] this->nume;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
	}

	const char* getNumePreparat() const{
		return nume;
	}

	const vector<MateriePrima> getIngrediente() const {
		return ingrediente;
	}
	
	virtual void afiseazaDetalii() const = 0;

	Preparat& operator=(const Preparat& other) {
		if (this != &other) {
			delete[] nume;

			if (other.nume != nullptr) {
				nume = new char[strlen(other.nume) + 1];
				strcpy(nume, other.nume);
			}
			else {
				nume = nullptr;
			}

			ingrediente = other.ingrediente;
		}
		return *this;
	}

	~Preparat() {
		delete[] this->nume;
		nume = nullptr;
	}

};

