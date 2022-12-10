#include <conio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include "cvm 21.h"

using namespace std;

int main()
{
	// CONSTANTE
	const int CONSOLE_MAX_X = 120;
	const int CONSOLE_MAX_Y = 30;
	const int LENGTH_COLORS_POSSIBILITY = 6;
	const int MAX_PLAYER_TRY = 10;
	const int PASS_CODE_LENGTH = 4;
	const string GAME_TITLE = "JEU DES COULEURS";
	const string GAME_MODE_TITLE = "R\220GLAGES DE LA PARTIE";
	string COLOR_CHOICE[LENGTH_COLORS_POSSIBILITY] = { "Rouge", "Vert", "Bleu", "Jaune", "Mauve", "Cyan"};
	
	// CONSTANTE position
	const short GAME_TITLE_POS_Y = 1;
	const short SETTINGS_POS_Y = GAME_TITLE_POS_Y + 3;
	const short TEXT_INFOS_POS_Y = GAME_TITLE_POS_Y + 4;
	const short TEXT_DEBUG_POS_Y = SETTINGS_POS_Y + 3;
	const short MARGIN_START_POS_X = 9;
	const short MARGIN_START_POS_Y = TEXT_INFOS_POS_Y + 3;
	const short PASS_CODE_POS_X = 55;
	const short PASS_CODE_POS_Y = 24;
	const short SPACING_INFOS_1 = 4, SPACING_INFOS_2 = 8, SPACING_INFOS_3 = 4;
	const short TEXT_GOOD_PLACE_POS_X = 30;
	const short TEXT_WRONG_PLACE_POS_X = 50;
	const short STARTING_PLACE_COUNT_TRY = MARGIN_START_POS_Y + 2;
	const short TRY_CURSOR_PLACE_POS_X = 14;
	const short FINAL_MESSAGE_POS_X = 0;
	const short FINAL_MESSAGE_POS_Y = 25;

	short tryPlayerPosY = STARTING_PLACE_COUNT_TRY;
	const short TEXT_EVALUATION_POS_Y = tryPlayerPosY + MAX_PLAYER_TRY + 3;

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
	char letterInProgress;
	
	int countAttemptPassCode = 0;
	int nbrAtGoodPlace = 0, nbrWrongPlace = 0;

	// Copy in array the first letter of each colors
	for (int i = 0; i < LENGTH_COLORS_POSSIBILITY; i++)
	{
		letterInProgress = COLOR_CHOICE[i][0];
		letterPossibility[i] = toupper(letterInProgress);
	}

	// Random Pass Code
	srand(time(0));
	for (int i = 0; i < PASS_CODE_LENGTH; i++)
		passCode[i] = letterPossibility[(rand() % LENGTH_COLORS_POSSIBILITY)];

	// Display titles
	gotoxy((CONSOLE_MAX_X / 2 - GAME_TITLE.size() / 2), GAME_TITLE_POS_Y);
	cout << GAME_TITLE;

	gotoxy((CONSOLE_MAX_X / 2 - GAME_MODE_TITLE.size() / 2), SETTINGS_POS_Y);
	cout << GAME_MODE_TITLE;

	// Player choice Game Mode he want
	gotoxy(0,TEXT_DEBUG_POS_Y);
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
	gotoxy((CONSOLE_MAX_X / 2 - GAME_TITLE.size() / 2), GAME_TITLE_POS_Y);
	cout << GAME_TITLE;

	gotoxy(MARGIN_START_POS_X, TEXT_INFOS_POS_Y);
	
	// Display colors name
	for (int i = 0; i < LENGTH_COLORS_POSSIBILITY; i++)
	{
		letterInProgress = COLOR_CHOICE[i][0];
		cout << "(" << letterInProgress << ")";

		for (int j = 1; j < COLOR_CHOICE[i].size(); j++)
		{
			letterInProgress = COLOR_CHOICE[i][j];
			cout << letterInProgress;
		}
		if (i < LENGTH_COLORS_POSSIBILITY - 1)
			cout << " , ";
	}
	
	// Display game informations
	gotoxy(MARGIN_START_POS_X, MARGIN_START_POS_Y);
	cout << '#' << setw(SPACING_INFOS_1) << ""  << "Essais" << setw(SPACING_INFOS_2) << "" << "Bien plac\202e(s)" << setw(SPACING_INFOS_3) << "" << "Mal plac\202e(s)";

	gotoxy(0, STARTING_PLACE_COUNT_TRY);
	for (int i = 1; i <= MAX_PLAYER_TRY; i++)
	{	
		cout << setw(MARGIN_START_POS_X) << right << i << ")" << "\n";
	}

	// Display game Pass Code
	if (showPassCode)
	{
		gotoxy(PASS_CODE_POS_X, PASS_CODE_POS_Y);
		cout << "Code Secret : ";
		for (int i = 0; i < PASS_CODE_LENGTH; i++)
			cout << passCode[i] << " ";
	}

	// Display game informations
	do {
		nbrAtGoodPlace = nbrWrongPlace = 0;
		gotoxy(TRY_CURSOR_PLACE_POS_X, tryPlayerPosY);
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
		gotoxy(1, TEXT_EVALUATION_POS_Y);
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
		gotoxy(TEXT_GOOD_PLACE_POS_X, STARTING_PLACE_COUNT_TRY + countAttemptPassCode);
		cout << nbrAtGoodPlace;
		gotoxy(TEXT_WRONG_PLACE_POS_X, STARTING_PLACE_COUNT_TRY + countAttemptPassCode);
		cout << nbrWrongPlace;
		countAttemptPassCode++;

	} while((countAttemptPassCode < MAX_PLAYER_TRY) && nbrAtGoodPlace != PASS_CODE_LENGTH);

	gotoxy(FINAL_MESSAGE_POS_X, FINAL_MESSAGE_POS_Y);
	if (nbrAtGoodPlace == PASS_CODE_LENGTH)
		cout << "Vous avez gagner ! :(";		// a verifier
	else
		cout << "Vous avez perdu ! :(";

	_getch();
}