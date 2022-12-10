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
	const int LENGTH_COLORS_POSSIBILITY = 6;
	const int MAX_PLAYER_TRY = 10;
	const int PASS_CODE_LENGTH = 4;
	const string GAME_TITLE = "JEU DES COULEURS";
	const string GAME_MODE_TITLE = "R\220GLAGES DE LA PARTIE";
	string COLOR_CHOICE[LENGTH_COLORS_POSSIBILITY] = { "Rouge", "Vert", "Bleu", "Jaune", "Mauve", "Cyan" };

	// Variable
	bool playerTryValidPossibility = false;
	bool showPassCode = false;
	bool alreadyTookPassCode[PASS_CODE_LENGTH] = {};	// init a false
	bool alreadyTookPlayerTry[PASS_CODE_LENGTH] = {};	// init a false

	char playerPassCodeTry[PASS_CODE_LENGTH];
	char passCode[PASS_CODE_LENGTH];
	char letterPossibility[LENGTH_COLORS_POSSIBILITY];
	char answerEvaluateCode;
	char playerChoice;
	char LetterChoiceInProgress = ' ';
	char letter;
	
	int margeGauche, margeHaut;

	int nbrAttemptPassCode = 0;
	int nbrAtGoodPlace = 0, nbrWrongPlace = 0;

	// variable position
	const short gameTitlePosY = 1;
	const short secondInformationPosY = gameTitlePosY + 3;
	const short textInformationPosY = gameTitlePosY + 4;
	const short debogModePosY = secondInformationPosY + 3;
	const short leftMarginColorPosX = 9;
	const short leftMarginInformationGamePosY = textInformationPosY + 3;
	const short passCodePosX = 55;
	const short passCodePosY = 24;
	const short espace_1 = 4, espace_2 = 8, espace_3 = 4;
	const short goodPlacePosX = 30;
	const short wrongPlacePosX = 50;
	const short placeStartFirstTryPosY = leftMarginInformationGamePosY+2;
	const short tryPlayerPosX = 14;
	short tryPlayerPosY = placeStartFirstTryPosY;
	const short evaluatePosY = tryPlayerPosY + MAX_PLAYER_TRY + 3;
	const short FINAL_MESSAGE_POS_X = 0;
	const short FINAL_MESSAGE_POS_Y = 25;


	// Copy in array the first letter of each colors
	for (int i = 0; i < LENGTH_COLORS_POSSIBILITY; i++)
	{
		letter = COLOR_CHOICE[i][0];
		letterPossibility[i] = toupper(letter);
	}

	// Random Pass Code
	srand(time(0));
	for (int i = 0; i < PASS_CODE_LENGTH; i++)
		passCode[i] = letterPossibility[(rand() % LENGTH_COLORS_POSSIBILITY)];

	// Display titles
	gotoxy((CONSOLE_MAX_X / 2 - GAME_TITLE.size() / 2), gameTitlePosY);
	cout << GAME_TITLE;

	gotoxy((CONSOLE_MAX_X / 2 - GAME_MODE_TITLE.size() / 2), secondInformationPosY);
	cout << GAME_MODE_TITLE;

	// Player choice Game Mode he want
	gotoxy(0,debogModePosY);
	cout << "\t" <<
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
	gotoxy((CONSOLE_MAX_X / 2 - GAME_TITLE.size() / 2), gameTitlePosY);
	cout << GAME_TITLE;

	gotoxy(leftMarginColorPosX, textInformationPosY);
	
	// Display colors name
	for (int i = 0; i < LENGTH_COLORS_POSSIBILITY; i++)
	{
		letter = COLOR_CHOICE[i][0];
		cout << "(" << letter << ")";

		for (int j = 1; j < COLOR_CHOICE[i].size(); j++)
		{
			letter = COLOR_CHOICE[i][j];
			cout << letter;
		}
		if (i < LENGTH_COLORS_POSSIBILITY - 1)
			cout << " , ";
	}
	
	// Display game informations
	gotoxy(leftMarginColorPosX, leftMarginInformationGamePosY);
	cout << '#' << setw(espace_1) << ""  << "Essais" << setw(espace_2) << "" << "Bien plac\202e(s)" << setw(espace_3) << "" << "Mal plac\202e(s)";

	gotoxy(0, placeStartFirstTryPosY);
	for (int i = 1; i <= MAX_PLAYER_TRY; i++)
	{	
		cout << setw(leftMarginColorPosX) << right << i << ")" << "\n";
	}

	// Display game Pass Code
	if (showPassCode)
	{
		gotoxy(passCodePosX, passCodePosY);
		cout << "Code Secret : ";
		for (int i = 0; i < PASS_CODE_LENGTH; i++)
			cout << passCode[i] << " ";
	}

	// Display game informations
	do {
		nbrAtGoodPlace = nbrWrongPlace = 0;
		gotoxy(tryPlayerPosX, tryPlayerPosY);
		clreol();

		// Player choice patern to try Pass Code
		for (int i = 0; i < PASS_CODE_LENGTH; i++)
		{
			do {
				playerTryValidPossibility = false;
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
				for (int j = 0; j < LENGTH_COLORS_POSSIBILITY; j++)
				{
					if (LetterChoiceInProgress == letterPossibility[j])
					{
						playerTryValidPossibility = true;
						cout << LetterChoiceInProgress << " ";
						playerPassCodeTry[i] = LetterChoiceInProgress;
					}
				}
			} while (!(playerTryValidPossibility));
		}

		// Player Pass Code Evaluation
		gotoxy(1, evaluatePosY);
		cout << "\220valuer ? (O/N) : ";
		do
		{
			answerEvaluateCode = _getch();
			answerEvaluateCode = toupper(answerEvaluateCode);
		} while (answerEvaluateCode != 'O' && answerEvaluateCode != 'N');

		if (answerEvaluateCode == 'N')
			continue;
		else
		{
			//++evaluatePosY;
		}

		tryPlayerPosY++;

		// Patern at good place
		for (int i = 0; i < PASS_CODE_LENGTH; i++)
		{
			if (passCode[i] == playerPassCodeTry[i])
			{
				++nbrAtGoodPlace;
				alreadyTookPassCode[i] = false;
				alreadyTookPlayerTry[i] = false;
			}
			else
			{
				alreadyTookPassCode[i] = true;
				alreadyTookPlayerTry[i] = true;
			}
		}
		// Patern wrong place
		for (int i = 0; i < PASS_CODE_LENGTH; i++) // i = player patern
		{
			for (int j = 0; j < PASS_CODE_LENGTH; j++) // j = Pass Code
			{
				if (i != j)
				{
					if (playerPassCodeTry[i] == passCode[j])
					{
						if (alreadyTookPassCode[j] == true && alreadyTookPlayerTry[i] == true)
						{		
							nbrWrongPlace+=1;
							alreadyTookPassCode[j] = false;
							alreadyTookPlayerTry[i] = false;
						}
					}
				}
			}
		}

		// Diplay number of good / wrong +
		gotoxy(goodPlacePosX, placeStartFirstTryPosY + nbrAttemptPassCode);
		cout << nbrAtGoodPlace;
		gotoxy(wrongPlacePosX, placeStartFirstTryPosY + nbrAttemptPassCode);
		cout << nbrWrongPlace;
		nbrAttemptPassCode++;

	} while((nbrAttemptPassCode < MAX_PLAYER_TRY) && nbrAtGoodPlace != PASS_CODE_LENGTH);

	gotoxy(FINAL_MESSAGE_POS_X, FINAL_MESSAGE_POS_Y);
	if (nbrAtGoodPlace == PASS_CODE_LENGTH)
		cout << "Vous avez gagner ! :(";
	else
		cout << "Vous avez perdu ! :(";

	_getch();
}