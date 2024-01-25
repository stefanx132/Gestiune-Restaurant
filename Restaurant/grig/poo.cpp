#define _CRT_SECURE_NO_WARNINGS
#include "Meniu.h"
#include "Comanda.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

Meniu meniu;
vector<Comanda> comenzi;
void comanda() {

	//nume + adaugare produse la comanda
	std::cout << "Introduceti numele: ";
	string name;
	cin.get();
	getline(cin, name);

	Comanda c(name);

	std::cout << "Introduceti numele felurilor principale, \"finish\" pentru a termina lista\n";
	std::cin >> name;
	while (name != "finish")
	{
		bool found = false;
		for (auto m : meniu.getFelPrincipal())
			if (strcmp(name.c_str(), m->getNumePreparat()) == 0)
			{
				found = true;
				c.addPreparat(m);
				std::cout << "Produs adaugat in cos cu succes.\n";
			}

		if (!found)
			std::cout << "Acest fel principal nu este in meniu.\n";
		std::cin >> name;
	}

	std::cout << "Introduceti numele deserturilor, \"finish\" pentru a termina lista\n";
	std::cin >> name;
	while (name != "finish")
	{
		bool found = false;
		for (auto d : meniu.getDeserturi())
			if (strcmp(name.c_str(), d->getNumePreparat()) == 0)
			{
				found = true;
				c.addPreparat(d);
				std::cout << "Produs adaugat in cos cu succes.\n";
			}

		if (!found)
			std::cout << "Acest desert nu este in meniu.\n";
		std::cin >> name;
	}

	std::cout << "Introduceti numele bauturilor, \"finish\" pentru a termina lista\n";
	std::cin >> name;
	while (name != "finish")
	{
		bool found = false;
		for (auto b : meniu.getBauturi())
			if (strcmp(name.c_str(), b->getNumePreparat()) == 0)
			{
				found = true;
				c.addPreparat(b);
				std::cout << "Produs adaugat in cos cu succes.\n";
			}

		if (!found)
			std::cout << "Aceasta bautura nu este in meniu.\n";
		std::cin >> name;
	}

	//confirmare comanda
	std::cout << "Produsele din cosul dumneavoastra sunt:\n";
	for(auto p : c.getPreparate())
		std::cout << p->getNumePreparat() << endl;

	string answer;
	std::cout << "Confirmare comanda (y/n): ";
	std::cin >> answer;
	if (answer == "n")
	{
		std::cout << "comanda abandonata.\n";
		return;
	}
	else if (answer == "y")
	{
		//verficare stoc
		for (auto* produs : c.getPreparate())
		{
			Bautura* b = dynamic_cast<Bautura *>(produs);
			if (b != nullptr)
			{

				if (b->getNrSticle() == 0)
				{
					std::cout << "Nu putem satisface comanda. Bautura " << b->getNumePreparat() << " lipseste din stoc.\n";
					return;
				}
				else b->subNr();
			}

			Mancare* m = dynamic_cast<Mancare*>(produs);
			if (m != nullptr)
			{
				for (auto ingredient : m->getIngrediente())
				{
					bool found = false;
					for (auto i : meniu.getIngredienteMeniu())
					{
						if (strcmp(ingredient.getNumeIngredient(), i.getNumeIngredient()) == 0)
						{
							found = true;
							if (i.getCantitate() >= ingredient.getCantitate())
							{
								i.subNr(ingredient.getCantitate());
							}
							else {
								std::cout << "Nu putem satisface comanda. Ingredientul: " << i.getNumeIngredient() << " pentru produsul: " << m->getNumePreparat() << " nu este de ajuns.\n";
								return;
							}
						}
					}
					if (found == false)
					{
						std::cout << "Nu putem satisface comanda. Ingredientul: " << ingredient.getNumeIngredient() << " pentru produsul: " << m->getNumePreparat() << " nu se afla in stoc.\n";
						return;
					}
				}
			}

			Desert* d = dynamic_cast<Desert*>(produs);
			if (d != nullptr)
			{
				for (auto ingredient : d->getIngrediente())
				{
					bool found = false;
					for (auto i : meniu.getIngredienteMeniu())
					{
						if (strcmp(ingredient.getNumeIngredient(), i.getNumeIngredient()) == 0)
						{
							found = true;
							if (i.getCantitate() >= ingredient.getCantitate())
								i.subNr(ingredient.getCantitate());
							else {
								std::cout << "Nu putem satisface comanda. Ingredientul: " << i.getNumeIngredient() << " pentru produsul: " << d->getNumePreparat() << " nu este de ajuns.\n";
								return;
							}
						}
					}
					if (found == false)
					{
						std::cout << "Nu putem satisface comanda. Ingredientul: " << ingredient.getNumeIngredient() << " pentru produsul: " << d->getNumePreparat() << " nu se afla in stoc.\n";
						return;
					}
				}
			}
		}
		std::cout << "Comanda plasata cu succes!\n";
		comenzi.push_back(c);
	}
	else std::cout << "raspuns invalid.\n";
}

void writetobins()
{
	FILE* file = fopen("stocbackup.bin", "w+");
	if (!file) {
		std::cerr << "Error opening file!" << std::endl;
		exit(1);
	}

	for (auto ing : meniu.getIngredienteMeniu())
		fprintf(file, "%s %d\n", ing.getNumeIngredient(), ing.getCantitate());

	fclose(file);

	FILE* file2 = fopen("meniubackup.bin", "w+");
	if (!file2)
	{
		std::cerr << "Error opening file!" << std::endl;
		exit(1);
	}


	//list<Bautura*> blist = meniu.getBauturi();
	for (auto b : meniu.getBauturi())
	{
		fprintf(file2, "%s %d\n", b->getNumePreparat(), b->getNrSticle());
		for (auto i : b->getIngrediente())
			fprintf(file2, "%s %d\n", i.getNumeIngredient(), i.getCantitate());
		b->getAlcool() ? fprintf(file2, "%s %d\n\n", "alcool", 1) : fprintf(file2, "%s %d\n\n", "alcool", 0);
	}
	fprintf(file2, "ENDDRINKS !\n\n");

	for (auto m : meniu.getFelPrincipal())
	{
		fprintf(file2, "%s !\n", m->getNumePreparat());
		for (auto i : m->getIngrediente())
			fprintf(file2, "%s %d\n", i.getNumeIngredient(), i.getCantitate());
		m->getVegan() ? fprintf(file2, "%s %d\n\n", "vegan", 1) : fprintf(file2, "%s %d\n\n", "vegan", 0);
	}
	fprintf(file2, "ENDFOOD !\n\n");
	
	for (auto d : meniu.getDeserturi())
	{
		fprintf(file2, "%s !\n", d->getNumePreparat());
		for (auto i : d->getIngrediente())
			fprintf(file2, "%s %d\n", i.getNumeIngredient(), i.getCantitate());
		d->getZahar() ? fprintf(file2, "%s %d\n\n", "are_zahar", 1) : fprintf(file2, "%s %d\n\n", "are_zahar", 0);
	}
	fprintf(file2, "ENDDESERTS !");

	FILE* file3 = fopen("comenzi.bin", "w+");
	if (!file3)
	{
		std::cerr << "Error opening file!" << std::endl;
		exit(1);
	}

	fprintf(file3, "LISTA COMENZI:\n");
	for (auto comanda : comenzi)
	{
		fprintf(file3, "nume: %s\n", comanda.getNume().c_str());
		fprintf(file3, "Produse:\n");
		for (auto prep : comanda.getPreparate())
			fprintf(file3, "%s\n", prep->getNumePreparat());
		fprintf(file3, "\n");
	}

}

void readfromtxt(char* name1, char* name2)
{
	char filepath1[30]; strcpy(filepath1, name1);
	FILE* file1;
	if ((file1 = fopen(filepath1, "r")) == NULL)
	{
		std::cout << "fisierul nu exista.\n";
		exit(1);
	}
	else
	{
		fclose(file1);
		ifstream f1(filepath1);
		string ingredient;
		int cantitate;

		while (f1 >> ingredient >> cantitate)
		{
			MateriePrima ing = MateriePrima(ingredient.c_str(), cantitate);
			meniu.addIngredient(ing);
		}
		f1.close();
	}

	char filepath2[30]; strcpy(filepath2, name2);
	FILE* file2;
	if ((file2 = fopen(filepath2, "r")) == NULL)
	{
		std::cout << "fisierul nu exista.\n";
		exit(1);
	}
	else
	{
		fclose(file2);
		ifstream f2(filepath2);
		string nume;
		string cantitate;
		while (f2 >> nume >> cantitate)
		{
			if (nume == "ENDDRINKS")
				break;
			Bautura* b = new Bautura(nume.c_str(), stoi(cantitate));
			while (f2 >> nume >> cantitate)
			{
				if (nume == "alcool")
				{
					if (stoi(cantitate) == 1)
						b->setAlcoolTrue();
					break;
				}
				else
				{
					MateriePrima ingredient(nume.c_str(), stoi(cantitate));
					b->addIngredient(ingredient);
				}
			}
			meniu.addBautura(b);
		}

		while (f2 >> nume >> cantitate)
		{
			if (nume == "ENDFOOD")
				break;
			Mancare* mancare = new Mancare(nume.c_str());
			while (f2 >> nume >> cantitate)
			{
				if (nume == "vegan")
				{
					if (stoi(cantitate) == 1)
						mancare->setVegan();
					break;
				}
				else
				{
					MateriePrima ingredient(nume.c_str(), stoi(cantitate));
					mancare->addIngredient(ingredient);
				}
			}
			meniu.addMancare(mancare);
		}

		while (f2 >> nume >> cantitate)
		{
			if (nume == "ENDDESERTS")
			{
				f2.close();
				break;
			}
			Desert* desert = new Desert(nume.c_str());
			while (f2 >> nume >> cantitate)
			{
				if (nume == "are_zahar")
				{
					if (stoi(cantitate) == 1)
						desert->setZahar();
					break;
				}
				else
				{
					MateriePrima ingredient(nume.c_str(), stoi(cantitate));
					desert->addIngredient(ingredient);
				}
			}
			meniu.addDesert(desert);
		}

	}
}

void readfromcsv(char* name1, char* name2)
{
	char filepath1[30]; strcpy(filepath1, name1);
	FILE* file1;
	if ((file1 = fopen(filepath1, "r")) == NULL)
	{
		std::cout << "fisierul nu exista.\n";
		exit(1);
	}
	else
	{
		fclose(file1);
		ifstream f1(filepath1);
		string content;
		string ingredient;
		int cantitate;

		while (f1 >> content)
		{
			char array[50] = "";
			strcpy(array, content.c_str());
			char* token = strtok(array, ",");
			ingredient = string(token);
			token = strtok(NULL, ",");
			cantitate = stoi(token);
			MateriePrima ing = MateriePrima(ingredient.c_str(), cantitate);
			meniu.addIngredient(ing);
		}
		f1.close();
	}


	char filepath2[30]; strcpy(filepath2, name2);
	FILE* file2;
	if ((file2 = fopen(filepath2, "r")) == NULL)
	{
		std::cout << "fisierul nu exista.\n";
		exit(1);
	}
	else
	{
		fclose(file2);
		ifstream f2(filepath2);
		string content;
		string nume;
		string cantitate;
		while (f2 >> content)
		{
			char array[50] = "";
			strcpy(array, content.c_str());
			char* token = strtok(array, ",");
			nume = string(token);
			token = strtok(NULL, ",");
			cantitate = string(token);
			if (nume == "ENDDRINKS")
				break;
			Bautura* b = new Bautura(nume.c_str(), stoi(cantitate));
			while (f2 >> content)
			{
				char array[50] = "";
				strcpy(array, content.c_str());
				char* token = strtok(array, ",");
				nume = string(token);
				token = strtok(NULL, ",");
				cantitate = string(token);
				if (nume == "alcool")
				{
					if (stoi(cantitate) == 1)
						b->setAlcoolTrue();
					break;
				}
				else
				{
					MateriePrima ingredient(nume.c_str(), stoi(cantitate));
					b->addIngredient(ingredient);
				}
			}
			meniu.addBautura(b);
		}

		while (f2 >> content)
		{
			char array[50] = "";
			strcpy(array, content.c_str());
			char* token = strtok(array, ",");
			nume = string(token);
			token = strtok(NULL, ",");
			cantitate = string(token);
			if (nume == "ENDFOOD")
				break;
			Mancare* mancare = new Mancare(nume.c_str());
			while (f2 >> content)
			{
				char array[50] = "";
				strcpy(array, content.c_str());
				char* token = strtok(array, ",");
				nume = string(token);
				token = strtok(NULL, ",");
				cantitate = string(token);
				if (nume == "vegan")
				{
					if (stoi(cantitate) == 1)
						mancare->setVegan();
					break;
				}
				else
				{
					MateriePrima ingredient(nume.c_str(), stoi(cantitate));
					mancare->addIngredient(ingredient);
				}
			}
			meniu.addMancare(mancare);
		}

		while (f2 >> content)
		{
			char array[50] = "";
			strcpy(array, content.c_str());
			char* token = strtok(array, ",");
			nume = string(token);
			token = strtok(NULL, ",");
			cantitate = string(token);
			if (nume == "ENDDESERTS")
			{
				f2.close();
				break;
			}
			Desert* desert = new Desert(nume.c_str());
			while (f2 >> content)
			{
				char array[50] = "";
				strcpy(array, content.c_str());
				char* token = strtok(array, ",");
				nume = string(token);
				token = strtok(NULL, ",");
				cantitate = string(token);
				if (nume == "are_zahar")
				{
					if (stoi(cantitate) == 1)
						desert->setZahar();
					break;
				}
				else
				{
					MateriePrima ingredient(nume.c_str(), stoi(cantitate));
					desert->addIngredient(ingredient);
				}
			}
			meniu.addDesert(desert);
		}
	}
}

void adaugare_preparat()
{
	std::cout << "Tip produs (bautura, mancare, desert): ";
	string answer;
	if(!(std::cin >> answer))
	{
		std::cout << "\nCTRL+C.\n";
		exit(0);
	}
	if (answer == "bautura")
	{
		string nume;
		int cantitate;

		std::cout << "Introduceti numele_bauturii: ";
		std::cin >> nume;
		std::cout << "Introduceti numarul de sticle: ";
		std::cin >> cantitate;
		Bautura* b = new Bautura(nume.c_str(), cantitate);
		std::cout << "Introduceti numele ingredientelor si cantitatea (\"nume_ingredient cantitate\"), tastati \"finish\" pentru a termina lista\n";
		std::cin >> nume;
		while (nume != "finish")
		{
			std::cin >> cantitate;

			MateriePrima i = MateriePrima(nume.c_str(), cantitate);
			b->addIngredient(i);
			std::cin >> nume;

		}
		std::cout << "Bautura dvs. contine alcool? (y/n): ";
		std::cin >> answer;
		if (answer == "y")
			b->setAlcoolTrue();
		
		std::cout << "Aceasta este bautura creata: \n";
		b->afiseazaDetalii();
		std::cout << "Doriti sa o adaugati la meniu? (y/n): ";
		std::cin >> answer;
		if (answer == "y")
		{
			bool found = false;
			for (auto drink : meniu.getBauturi())
				if (strcmp(b->getNumePreparat(),drink->getNumePreparat()) == 0)
					found = true;
			if (found == false)
			{
				meniu.addBautura(b);
				std::cout << "Bautura adaugata cu succes!\n";
			}
			else std::cout << "Bautura exista deja in meniu!\n";
		}
	}
	else if(answer == "mancare")
	{
		string nume;
		int cantitate;

		std::cout << "Introduceti numele_preparatului: ";
		std::cin >> nume;
		Mancare* m = new Mancare(nume.c_str());
		std::cout << "Introduceti numele ingredientelor si cantitatea (\"nume_ingredient cantitate\"), tastati \"finish\" pentru a termina lista\n";
		std::cin >> nume;
		while (nume != "finish")
		{
			std::cin >> cantitate;
			MateriePrima i = MateriePrima(nume.c_str(), cantitate);
			m->addIngredient(i);
			std::cin >> nume;
		}
		std::cout << "Este preparatul vegan? (y/n): ";
		std::cin >> answer;
		if (answer == "y")
			m->setVegan();

		std::cout << "Aceast este preparatul creat: \n";
		m->afiseazaDetalii();
		std::cout << "Doriti sa il adaugati la meniu? (y/n): ";
		std::cin >> answer;
		if (answer == "y")
		{
			bool found = false;
			for (auto food : meniu.getFelPrincipal())
				if (strcmp(food->getNumePreparat(), m->getNumePreparat()) == 0)
					found = true;
			if (found == false)
			{
				meniu.addMancare(m);
				std::cout << "Preparat adaugat cu succes!\n";
			}
			else std::cout << "Preparatul exista deja in meniu!\n";
		}
	}
	else if(answer == "desert")
	{
		string nume;
		int cantitate;

		std::cout << "Introduceti numele_desertului: ";
		std::cin >> nume;
		Desert* d = new Desert(nume.c_str());
		std::cout << "Introduceti numele ingredientelor si cantitatea (\"nume_ingredient cantitate\"), tastati \"finish\" pentru a termina lista\n";
		std::cin >> nume;
		while (nume != "finish")
		{
			std::cin >> cantitate;
			MateriePrima i = MateriePrima(nume.c_str(), cantitate);
			d->addIngredient(i);
			std::cin >> nume;
		}
		std::cout << "Desertul contine zahar? (y/n): ";
		std::cin >> answer;
		if (answer == "y")
			d->setZahar();

		std::cout << "Aceast este desertul creat: \n";
		d->afiseazaDetalii();
		std::cout << "Doriti sa il adaugati la meniu? (y/n): ";
		std::cin >> answer;
		if (answer == "y")
		{
			bool found = false;
			for (auto desert : meniu.getDeserturi())
				if (strcmp(desert->getNumePreparat(), d->getNumePreparat()) == 0)
					found = true;
			if (found == false)
			{
				meniu.addDesert(d);
				std::cout << "Preparat adaugat cu succes!\n";
			}
			else std::cout << "Preparatul exista deja in meniu!\n";
		}
	}
	else
	{
		std::cout << "Tip invalid.\n";
		return;
	}

}

int main(int argc, char ** argv) {
	if (argc == 2 || argc > 3)
	{
		std::cout << "Usage: poo.exe <file1> <file2> (both files shoud have the same extension, txt or csv)\n";
		return 0;
	}
	else if (argc == 3)
	{
		string file1 = string(argv[1]), file2 = string(argv[2]);

		char* token1 = strtok(argv[1], " .");
		token1 = strtok(NULL, " .");
		char* token2 = strtok(argv[2], " .");
		token2 = strtok(NULL, " .");

		cout << "token1: " << token1<< ' ' << "token2: " << token2 << endl;

		if (strcmp(token1,token2)!=0)
		{
			std::cout << "Extensions of files are different.";
			return 1;
		}
		if (strcmp(token1, "csv") == 0)
			readfromcsv((char*)file1.c_str(), (char*)file2.c_str());
		if (strcmp(token1, "txt") == 0)
			readfromtxt((char*)file1.c_str(), (char*)file2.c_str());
	}
	else
		readfromtxt((char*)"stoc.txt", (char*)"meniu.txt");

	
	//writetobins();

	//lista comenzi:
	//1 - comanda
	//2 - stoc
	//3 - meniu
	//4 - adaugare_preparat
	//5 - help

	char help[] = "Lista comenzi:\n1 - comanda\n2 - stoc\n3 - meniu\n4 - adaugare_preparat\n5 - help\n6 - exit\n\n";
	std::cout << help;

	string answer;
	while (answer != "exit")
	{
		std::cout << "client > ";
		if(!(std::cin >> answer))
		{
			std::cout << "\nCTRL+C.\n";
			break;
		}
		if (answer == "comanda")
		{
			comanda();
		}
		else if (answer == "stoc")
		{
			meniu.afisareIngredienteDisponibile();
		}
		else if (answer == "meniu")
		{
			meniu.afisareMeniu();
		}
		else if (answer == "adaugare_preparat")
		{
			adaugare_preparat();
		}
		else if (answer == "help")
			std::cout << help;
		else if (answer == "exit")
			continue;
		else std::cout << "comanda invalida. incearca \"help\".\n";
	}

	writetobins();

	return 0;
}


