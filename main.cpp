#include <conio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include "cvm 21.h"

using namespace std;

int main()
{
	// CONSTANTE (Could be changed to modify the game context)
	const int CONSOLE_MAX_X = 120; // FIXME
	const int CONSOLE_MAX_Y = 30;
	const int LENGTH_COLORS_POSSIBILITY = 6;
	const int MAX_PLAYER_TRY = 10;
	const int PASS_CODE_LENGTH = 4;
	const string GAME_TITLE = "JEU DES COULEURS"; // FIXME
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
	const short TEXT_EVALUATION_POS_Y = STARTING_PLACE_COUNT_TRY + MAX_PLAYER_TRY + 3;
	// FIXME : TRY Vers ATTEMPT et Passcode
	// Variable
	bool playerAttemptValidOption = false;
	bool showPasscode = false;
	bool alreadyTookPasscode[PASS_CODE_LENGTH] = {};	// Array of False
	bool alreadyTookPlayerAttempt[PASS_CODE_LENGTH] = {};	// Array of False
	short playerLetterAttemptPosY = STARTING_PLACE_COUNT_TRY;

	char playerPasscode[PASS_CODE_LENGTH];
	char passcode[PASS_CODE_LENGTH];
	char passcodeOptions[LENGTH_COLORS_POSSIBILITY];
	
	int attemptCount = 0;
	int wellPlacedCount = 0, wrongPlacedCount = 0;

	// Create array of passcode options
	for (int i = 0; i < LENGTH_COLORS_POSSIBILITY; i++)
		passcodeOptions[i] = toupper(COLOR_CHOICE[i][0]);

	// Create passcode randomly
	srand(time(0));
	for (int i = 0; i < PASS_CODE_LENGTH; i++)
		passcode[i] = passcodeOptions[(rand() % LENGTH_COLORS_POSSIBILITY)];

	// Display titles
	gotoxy((CONSOLE_MAX_X / 2 - GAME_TITLE.size() / 2), GAME_TITLE_POS_Y);
	cout << GAME_TITLE;

	gotoxy((CONSOLE_MAX_X / 2 - GAME_MODE_TITLE.size() / 2), SETTINGS_POS_Y);
	cout << GAME_MODE_TITLE;

	// Enable debugging mode
	gotoxy(0,TEXT_DEBUG_POS_Y);
	cout << "\t" << "Activer le mode en d\202bogage ? (O/N) : ";
	char letterPlayerChoice;
	do
	{
		letterPlayerChoice = _getch();
		letterPlayerChoice = toupper(letterPlayerChoice);
	} while (letterPlayerChoice != 'O' && letterPlayerChoice != 'N');

	if (letterPlayerChoice == 'O')
		showPasscode = true;

	clrscr();

	// Display game title 
	gotoxy((CONSOLE_MAX_X / 2 - GAME_TITLE.size() / 2), GAME_TITLE_POS_Y);
	cout << GAME_TITLE;

	gotoxy(MARGIN_START_POS_X, TEXT_INFOS_POS_Y);
	
	// Display colors name
	for (int i = 0; i < LENGTH_COLORS_POSSIBILITY; i++)
	{
		char letterInProgress = toupper(COLOR_CHOICE[i][0]);
		cout << "(" << letterInProgress << ")";

		for (int j = 1; j < COLOR_CHOICE[i].size(); j++)
		{
			letterInProgress = COLOR_CHOICE[i][j];
			cout << letterInProgress;
		}
		if (i < LENGTH_COLORS_POSSIBILITY - 1)
			cout << " , ";
	}
	
	// Display game rules
	gotoxy(MARGIN_START_POS_X, MARGIN_START_POS_Y);
	cout << '#' << setw(SPACING_INFOS_1) << ""  << "Essais" << setw(SPACING_INFOS_2) << "" << "Bien plac\202e(s)" << setw(SPACING_INFOS_3) << "" << "Mal plac\202e(s)";

	gotoxy(0, STARTING_PLACE_COUNT_TRY);
	for (int i = 1; i <= MAX_PLAYER_TRY; i++)
		cout << setw(MARGIN_START_POS_X) << right << i << ")" << "\n";

	// Display game Passcode
	if (showPasscode)
	{
		gotoxy(PASS_CODE_POS_X, PASS_CODE_POS_Y);
		cout << "Code Secret : ";
		for (int i = 0; i < PASS_CODE_LENGTH; i++)
			cout << passcode[i] << " ";
	}

	// Display game informations
	do {
		wellPlacedCount = wrongPlacedCount = 0;
		gotoxy(TRY_CURSOR_PLACE_POS_X, playerLetterAttemptPosY);
		clreol();

		char letterChoiceInProgress;
		// Player choice patern to try passcode
		for (int i = 0; i < PASS_CODE_LENGTH; i++)
		{
			do {
				playerAttemptValidOption = false;
				letterChoiceInProgress = _getch();
				
				// If press Backspace
				if (letterChoiceInProgress == 8 && i > 0) // FIXME : 
				{
					i--;
					cout << "\b\b";
					clreol();
				}
				
				letterChoiceInProgress = toupper(letterChoiceInProgress);

				// If choice is in possibility
				for (int j = 0; j < LENGTH_COLORS_POSSIBILITY; j++)
					if (letterChoiceInProgress == passcodeOptions[j])
					{
						playerAttemptValidOption = true;
						cout << letterChoiceInProgress << " ";
						playerPasscode[i] = letterChoiceInProgress;
					}
			} while (!(playerAttemptValidOption));
		}

		// Player passcode evaluation
		gotoxy(1, TEXT_EVALUATION_POS_Y);
		cout << "\220valuer ? (O/N) : ";
		char answerEvaluateCode;
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

		playerLetterAttemptPosY++;

		// Find well placed letters
		for (int i = 0; i < PASS_CODE_LENGTH; i++)
			if (passcode[i] == playerPasscode[i])
			{
				++wellPlacedCount;
				alreadyTookPasscode[i] = false;
				alreadyTookPlayerAttempt[i] = false;
			}
			else
			{
				alreadyTookPasscode[i] = true;
				alreadyTookPlayerAttempt[i] = true;
			}

		// Find wrong placed letter
		for (int i = 0; i < PASS_CODE_LENGTH; i++) // i = player letters iterator
			for (int j = 0; j < PASS_CODE_LENGTH; j++) // j = passcode letters iterator
				if (i != j)
					if (playerPasscode[i] == passcode[j])
						if (alreadyTookPasscode[j] == true && alreadyTookPlayerAttempt[i] == true)
						{		
							wrongPlacedCount+=1;
							alreadyTookPasscode[j] = false;
							alreadyTookPlayerAttempt[i] = false;
						}

		// FIXME
		// Diplay number of good / wrong +
		gotoxy(TEXT_GOOD_PLACE_POS_X, STARTING_PLACE_COUNT_TRY + attemptCount);
		cout << wellPlacedCount;
		gotoxy(TEXT_WRONG_PLACE_POS_X, STARTING_PLACE_COUNT_TRY + attemptCount);
		cout << wrongPlacedCount;
		attemptCount++;

	} while((attemptCount < MAX_PLAYER_TRY) && wellPlacedCount != PASS_CODE_LENGTH);

	gotoxy(FINAL_MESSAGE_POS_X, FINAL_MESSAGE_POS_Y);
	if (wellPlacedCount == PASS_CODE_LENGTH)
		cout << "Vous avez gagner ! :(";		// FIXME
	else
		cout << "Vous avez perdu ! :(";

	_getch();
}