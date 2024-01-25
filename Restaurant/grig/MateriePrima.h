#pragma once
#include <iostream>
#include <string.h>
using namespace std;
class MateriePrima {
private:
	char* nume = nullptr;
	int cantitate;

public:
	MateriePrima() : cantitate(0) {
	}

	MateriePrima(const char* nume, int cantitate) : cantitate(cantitate) {
		if (nume != nullptr) {
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
	}

	MateriePrima(const MateriePrima& m) : cantitate(m.cantitate) {
		if (m.nume != nullptr) {
			this->nume = new char[strlen(m.nume) + 1];
			strcpy(this->nume, m.nume);
		}
	}

	MateriePrima& operator=(const MateriePrima& m) {
		if (this != &m) {
			delete[] nume;

			if (m.nume != nullptr) {
				this->nume = new char[strlen(m.nume) + 1];
				strcpy(nume, m.nume);
				cantitate = m.cantitate;
			}
			else {
				this->nume = nullptr;
			}
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const MateriePrima& m) {
		if (m.nume != nullptr) {
			out << "\nIntroduceti Nume: " << m.nume;
		}
		else {
			out << "\nNume: -";
		}
		out << "\nIntroduceti cantitate: " << m.cantitate;
		out << "\n-----OSTREAM------------";
		return out;
	}

	friend istream& operator>>(istream& in, MateriePrima& m) {
		cout << "\nIntroduceti nume: ";
		string buffer;
		in >> buffer;
		delete[] m.nume;
		m.nume = new char[buffer.size() + 1];
		strcpy(m.nume, buffer.data());
		cout << "\nIntroduceti cantitate: ";
		in >> m.cantitate;
		return in;
	}

	const char* getNumeIngredient() const {
		return nume;
	}

	int getCantitate() const {
		return cantitate;
	}

	void setNumeIngredient(char* numeIngredient)
	{
		if (numeIngredient != nullptr)
		{
			nume = new char[strlen(numeIngredient) + 1];
			strcpy(nume, numeIngredient);
		}
	}

	void subNr(int nr)
	{
		cantitate -= nr;
	}

	void afisare() const {
		cout << "Ingredient: " << nume << ", Cantitate: " << cantitate << endl;
	}

	~MateriePrima() {
		delete[] this->nume;
	}
};