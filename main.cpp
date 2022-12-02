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
	bool choixvalide = false;
	bool debogage = false;
	char ChoixCodeJoueur[NBR_VALEUR_CODE] = { ' ', ' ' , ' ', ' ' };
	char codeSecret[NBR_VALEUR_CODE] = { 'R', 'R' , 'V' , 'V' };	
	char evaluer;
	char JoueursChoix;
	char ChoixLettreEnCours = ' ';
	int margeGauche, margeHaut;
	int espace_1, espace_2, espace_3;
	int bienPlace = 0, malPlace = 0;
	bool dejaprisCacher[NBR_VALEUR_CODE] = {true, true , true, true };	// mettre en bouclebbbb
	bool dejaprisUser[NBR_VALEUR_CODE] = { true, true, true, true };	// mettre en bouclebbbb
	string choixCouleur[NBR_CHOIX_COULEURS] = { "Rouge", "Vert", "Bleu", "Jaune", "Mauve", "Cyan" };
	char CouleurLettre_1[NBR_CHOIX_COULEURS] = { 'R', 'V', 'B', 'J', 'M', 'C' };
	string CouleurLettreSauf_1[NBR_CHOIX_COULEURS] = { "ouge", "ert", "leu", "aune", "auve", "yan" };

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
		JoueursChoix = _getch();
		JoueursChoix = toupper(JoueursChoix);
	} while (JoueursChoix != 'O' && JoueursChoix != 'N');

	clrscr();

	// Affichage de la partie
	gotoxy((CONSOLE_MAX_X / 2 - TITRE_DU_JEU.size() / 2), 2);
	cout << TITRE_DU_JEU;

	margeGauche = 9;
	margeHaut = 5;
	gotoxy(margeGauche, margeHaut);

	for (int i = 0; i < NBR_CHOIX_COULEURS; i++)
	{
		cout << "(" << CouleurLettre_1[i] << ")" << CouleurLettreSauf_1[i];
		if (i < NBR_CHOIX_COULEURS - 1)
			cout << " , ";
	}
	
	espace_1 = 4;
	espace_2 = 8;
	espace_3 = 4;
	
	gotoxy(margeGauche, margeHaut += 3);
	cout << '#' << setw(espace_1) << ""  << "Essais" << setw(espace_2) << "" << "Bien plac\202e(s)" << setw(espace_3) << "" << "Mal plac\202e(s)";
	cout << "\n\n";

	for (int i = 1; i <= NBR_CHANCE_JOUEUR; i++)
	{	
		cout << setw(margeGauche) << right << i << ")" << "\n";
	}

	margeGauche = 14;
	margeHaut = 10;

	// Partie de l'utilisateur 
	do {
		bienPlace = malPlace = 0;
		gotoxy(margeGauche, margeHaut);
		clreol();

		// Choix du code de l'utilisateur
		for (int i = 1; i <= NBR_VALEUR_CODE; i++)
		{
			do {
				choixvalide = false;
				ChoixLettreEnCours = _getch();
				ChoixLettreEnCours = toupper(ChoixLettreEnCours);
					
				for (int j = 0; j < NBR_CHOIX_COULEURS; j++)
					if (ChoixLettreEnCours == CouleurLettre_1[j])
					{
						choixvalide = true;
						cout << ChoixLettreEnCours << " ";
						ChoixCodeJoueur[i-1] = ChoixLettreEnCours;
					}
			} while (!(choixvalide));
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
			if (codeSecret[i] == ChoixCodeJoueur[i])
				++bienPlace;
			else
			{
				dejaprisCacher[i] = false;
				dejaprisUser[i] = false;
			}
		}
		//mal placé
		for (int i = 0; i < NBR_VALEUR_CODE; i++) // i = code utilisateur
		{
			for (int j = 0; j < NBR_VALEUR_CODE; j++) // j = code secret
			{
				if (i != j)	// Pour ne pas avoir les biens placés
				{
					if (ChoixCodeJoueur[i] == codeSecret[j])
					{
						if (dejaprisCacher[j] == false && dejaprisUser[i] == false)
						{		
							malPlace+=1;
							dejaprisCacher[j] = true;
							dejaprisUser[i] = true;
						}
					}
				}
			}
		}
		gotoxy(5, 29);
		cout << bienPlace << "\t" << malPlace;
	} while(true);

_getch();

}
