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
	const int NBR_CHOICE_COLORS = 6;
	const int NBR_CHANCE_PLAYER = 10;
	const int LENGTH_PASS_CODE = 4;
	const string GAME_TITLE = "JEU DES COULEURS";
	const string GAME_MODE_TITLE = "R\220GLAGE DE LA PARTIE";

	// Variable
	bool validChoice = false;
	bool showPassCode = false;

	char playerPassCodeTry[LENGTH_PASS_CODE];
	char passCode[LENGTH_PASS_CODE];
	char letterPossibility[NBR_CHOICE_COLORS];
	char answerEvaluateCode;
	char playerChoice;
	char LetterChoiceInProgress = ' ';
	char letter;
	
	int margeGauche, margeHaut;
	int espace_1, espace_2, espace_3;
	
	int nbrAttemptPassCode = 0;
	int nbrAtGoodPlace = 0, nbrWrongPlace = 0;
	bool alreadyTookPassCode[LENGTH_PASS_CODE] = {};	// init a false
	bool alreadyTookPlayerCode[LENGTH_PASS_CODE] = {};	// init a false
	string colorChoice[NBR_CHOICE_COLORS] = { "Rouge", "Vert", "Bleu", "Jaune", "Mauve", "Cyan"};

	// Copy in array the first letter of each colors
	for (int i = 0; i < NBR_CHOICE_COLORS; i++)
	{
		letter = colorChoice[i][0];
		// letter = toupper(letter);
		letterPossibility[i] = toupper(letter);
	}

	// Random Pass Code
	srand(time(0));
	for (int i = 0; i < LENGTH_PASS_CODE; i++)
		passCode[i] = letterPossibility[(rand() % NBR_CHOICE_COLORS)];

	// Display titles
	gotoxy((CONSOLE_MAX_X / 2 - GAME_TITLE.size() / 2), 2);
	cout << GAME_TITLE;

	gotoxy((CONSOLE_MAX_X / 2 - GAME_MODE_TITLE.size() / 2), 5);
	cout << GAME_MODE_TITLE;

	// Player choice Game Mode he want
	cout << "\n\n" << "\t" <<
		"Activer le mode en d\202bogage ? (O/N) : ";
	do
	{
		playerChoice = _getch();
		playerChoice = toupper(playerChoice);
	} while (playerChoice != 'O' && playerChoice != 'N');

	if (playerChoice == 'O')
		showPassCode = true;

	clrscr();

	// Display title of the game
	gotoxy((CONSOLE_MAX_X / 2 - GAME_TITLE.size() / 2), 2);
	cout << GAME_TITLE;

	margeGauche = 9;
	margeHaut = 5;
	gotoxy(margeGauche, margeHaut);
	
	// Display colors name
	for (int i = 0; i < NBR_CHOICE_COLORS; i++)
	{
		letter = colorChoice[i][0];
		cout << "(" << letter << ")";

		for (int j = 1; j < colorChoice[i].size(); j++)
		{
			letter = colorChoice[i][j];
			cout << letter;
		}
		if (i < NBR_CHOICE_COLORS - 1)
			cout << " , ";
	}
	
	espace_1 = 4;
	espace_2 = 8;
	espace_3 = 4;
	
	// Display game informations
	gotoxy(margeGauche, margeHaut += 3);
	cout << '#' << setw(espace_1) << ""  << "Essais" << setw(espace_2) << "" << "Bien plac\202e(s)" << setw(espace_3) << "" << "Mal plac\202e(s)";

	int departPremierChiffreY = wherey() + 2;

	gotoxy(0, departPremierChiffreY);

	for (int i = 1; i <= NBR_CHANCE_PLAYER; i++)
	{	
		cout << setw(margeGauche) << right << i << ")" << "\n";
	}

	// Display game Pass Code
	if (showPassCode)
	{
		gotoxy(55, 25);
		cout << "Code Secret : ";
		for (int i = 0; i < LENGTH_PASS_CODE; i++)
			cout << passCode[i] << " ";
	}

	margeGauche = 14;
	margeHaut = 10;

	// Display game informations
	do {
		nbrAtGoodPlace = nbrWrongPlace = 0;
		gotoxy(margeGauche, margeHaut);
		clreol();

		// Player choice patern to try Pass Code
		for (int i = 0; i < LENGTH_PASS_CODE; i++)
		{
			do {
				validChoice = false;
				LetterChoiceInProgress = _getch();
				
				// If press Backspace
				if (LetterChoiceInProgress == 8 && i > 0)
				{
					i--;
					cout << "\b\b";
					clreol();

				}
				
				LetterChoiceInProgress = toupper(LetterChoiceInProgress);

				// If choice is in possibility
				for (int j = 0; j < NBR_CHOICE_COLORS; j++)
				{

					if (LetterChoiceInProgress == letterPossibility[j])
					{
						validChoice = true;
						cout << LetterChoiceInProgress << " ";
						playerPassCodeTry[i] = LetterChoiceInProgress;
					}
				}
				
			} while (!(validChoice));
		}

		// Player Pass Code Evaluation
		gotoxy(1, 10 + NBR_CHANCE_PLAYER + 3);
		cout << "\220vsluer ? (O/N) : ";

		do
		{
			answerEvaluateCode = _getch();
			answerEvaluateCode = toupper(answerEvaluateCode);
		} while (answerEvaluateCode != 'O' && answerEvaluateCode != 'N');

		if (answerEvaluateCode == 'N')
			continue;
		else
			++margeHaut;

		// Patern at good place
		for (int i = 0; i < LENGTH_PASS_CODE; i++)
		{
			if (passCode[i] == playerPassCodeTry[i])
			{
				++nbrAtGoodPlace;
				alreadyTookPassCode[i] = false;
				alreadyTookPlayerCode[i] = false;
			}
			else
			{
				alreadyTookPassCode[i] = true;
				alreadyTookPlayerCode[i] = true;
			}
		}
		// Patern wrong place
		for (int i = 0; i < LENGTH_PASS_CODE; i++) // i = player patern
		{
			for (int j = 0; j < LENGTH_PASS_CODE; j++) // j = Pass Code
			{
				if (i != j)
				{
					if (playerPassCodeTry[i] == passCode[j])
					{
						if (alreadyTookPassCode[j] == true && alreadyTookPlayerCode[i] == true)
						{		
							nbrWrongPlace+=1;
							alreadyTookPassCode[j] = false;
							alreadyTookPlayerCode[i] = false;
						}
					}
				}
			}
		}

		// Diplay number of good / wrong +
		gotoxy(30, departPremierChiffreY + nbrAttemptPassCode);
		cout << nbrAtGoodPlace;
		gotoxy(50, departPremierChiffreY + nbrAttemptPassCode);
		cout << nbrWrongPlace;
		nbrAttemptPassCode++;

	} while(nbrAttemptPassCode < NBR_CHANCE_PLAYER);

	gotoxy(0, 25);
	cout << "Vous avez perdu ! :(";
	_getch();

}