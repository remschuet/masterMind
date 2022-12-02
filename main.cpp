#include <conio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include "cvm 21.h"

using namespace std;

int main()
{
	// Constante
	const int CONSOLE_MAX_X = 120;
	const int CONSOLE_MAX_Y = 30;
	const int NBR_CHOIX_COULEURS = 6;
	const int NBR_CHANCE_JOUEUR = 10;
	const int NBR_VALEUR_CODE = 4;
	const string TITRE_DU_JEU = "JEU DES COULEURS";
	const string TITRE_REGLAGE = "R\220GLAGE DE LA PARTIE";

	// Variable
	bool choixValide = false;
	bool debogage = false;
	char choixCodeJoueur[NBR_VALEUR_CODE] = { ' ', ' ' , ' ', ' ' };
	char codeSecret[NBR_VALEUR_CODE] = { 'R', 'R' , 'V' , 'V' };	
	char evaluer;
	char joueursChoix;
	char choixLettreEnCours = ' ';
	int margeGauche, margeHaut;
	int espace_1, espace_2, espace_3;
	int nbrUtiliseChance = 0;
	int bienPlace = 0, malPlace = 0;
	bool dejaPrisCacher[NBR_VALEUR_CODE] = {};
	bool dejaPrisUser[NBR_VALEUR_CODE] = {};
	string choixCouleur[NBR_CHOIX_COULEURS] = { "Rouge", "Vert", "Bleu", "Jaune", "Mauve", "Cyan" };
	char lettre;
	char couleurLettre_1[NBR_CHOIX_COULEURS] = { 'R', 'V', 'B', 'J', 'M', 'C' };
	string couleurLettreSauf_1[NBR_CHOIX_COULEURS] = { "ouge", "ert", "leu", "aune", "auve", "yan" };

	// Affichage des titres
	gotoxy((CONSOLE_MAX_X / 2 - TITRE_DU_JEU.size() / 2), 2);
	cout << TITRE_DU_JEU;

	gotoxy((CONSOLE_MAX_X / 2 - TITRE_REGLAGE.size() / 2), 5);
	cout << TITRE_REGLAGE;

	// Choix configuration
	cout << "\n\n" << "\t" <<
		"Activer le mode en d\202bogage ? (O/N) : ";
	do
	{
		joueursChoix = _getch();
		joueursChoix = toupper(joueursChoix);
	} while (joueursChoix != 'O' && joueursChoix != 'N');

	if (joueursChoix == 'O')
		debogage = true;

	clrscr();

	// Affichage de la partie
	gotoxy((CONSOLE_MAX_X / 2 - TITRE_DU_JEU.size() / 2), 2);
	cout << TITRE_DU_JEU;

	margeGauche = 9;
	margeHaut = 5;
	gotoxy(margeGauche, margeHaut);

	for (int i = 0; i < NBR_CHOIX_COULEURS; i++)
	{
		lettre = choixCouleur[i][0];
		cout << "(" << lettre << ")";

		for (int j = 1; j < choixCouleur[i].size(); j++)
		{
			lettre = choixCouleur[i][j];
			cout << lettre;
		}
		if (i < NBR_CHOIX_COULEURS - 1)
			cout << " , ";
	}
	
	espace_1 = 4;
	espace_2 = 8;
	espace_3 = 4;
	
	gotoxy(margeGauche, margeHaut += 3);
	cout << '#' << setw(espace_1) << ""  << "Essais" << setw(espace_2) << "" << "Bien plac\202e(s)" << setw(espace_3) << "" << "Mal plac\202e(s)";

	int departPremierChiffreY = wherey() + 2;

	gotoxy(0, departPremierChiffreY);

	for (int i = 1; i <= NBR_CHANCE_JOUEUR; i++)
	{	
		cout << setw(margeGauche) << right << i << ")" << "\n";
	}

	// Affichage du code secret
	if (debogage)
	{
		gotoxy(55, 25);
		cout << "Code Secret : ";
		for (int i = 0; i < NBR_VALEUR_CODE; i++)
			cout << codeSecret[i] << " ";
	}

	margeGauche = 14;
	margeHaut = 10;

	// Partie de l'utilisateur 
	do {
		bienPlace = malPlace = 0;
		gotoxy(margeGauche, margeHaut);
		clreol();

		// Choix du code de l'utilisateur
		for (int i = 0; i < NBR_VALEUR_CODE; i++)
		{
			do {
				choixValide = false;
				choixLettreEnCours = _getch();
				
				if (choixLettreEnCours == 8 && i > 0) // Backspace
				{
					i--;
					cout << "\b\b";
					clreol();

				}
				
				choixLettreEnCours = toupper(choixLettreEnCours);

				for (int j = 0; j < NBR_CHOIX_COULEURS; j++)
				{

					if (choixLettreEnCours == couleurLettre_1[j])
					{
						choixValide = true;
						cout << choixLettreEnCours << " ";
						choixCodeJoueur[i] = choixLettreEnCours;
					}
				}
				

			} while (!(choixValide));
		}
		gotoxy(1, 10 + NBR_CHANCE_JOUEUR + 3);
		cout << "\220vsluer ? (O/N) : ";

		do
		{
			evaluer = _getch();
			evaluer = toupper(evaluer);
		} while (evaluer != 'O' && evaluer != 'N');

		if (evaluer == 'N')
			continue;
		else
			++margeHaut;

		// Bien placé
		for (int i = 0; i < NBR_VALEUR_CODE; i++)
		{
			if (codeSecret[i] == choixCodeJoueur[i])
				++bienPlace;
			else
			{
				dejaPrisCacher[i] = true;
				dejaPrisUser[i] = true;
			}
		}
		//mal placé
		for (int i = 0; i < NBR_VALEUR_CODE; i++) // i = code utilisateur
		{
			for (int j = 0; j < NBR_VALEUR_CODE; j++) // j = code secret
			{
				if (i != j)	// Pour ne pas avoir les biens placés
				{
					if (choixCodeJoueur[i] == codeSecret[j])
					{
						if (dejaPrisCacher[j] == true && dejaPrisUser[i] == true)
						{		
							malPlace+=1;
							dejaPrisCacher[j] = false;
							dejaPrisUser[i] = false;
						}
					}
				}
			}
		}

		// Affichage es resultat
		gotoxy(30, departPremierChiffreY + nbrUtiliseChance);
		cout << bienPlace;
		gotoxy(50, departPremierChiffreY + nbrUtiliseChance);
		cout << malPlace;
		nbrUtiliseChance++;

	} while(nbrUtiliseChance < NBR_CHANCE_JOUEUR);

	gotoxy(0, 25);
	cout << "Vous avez perdu ! :(";

_getch();

}
