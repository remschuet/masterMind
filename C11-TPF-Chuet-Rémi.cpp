#include <conio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include "cvm 21.h"

using namespace std;

int main()
{
	// CONSTANTE (Could be changed to modify the game context)
	const string GAME_TITLE = "JEU DES COULEURS";
	const string GAME_MODE_TITLE = "R\220GLAGES DE LA PARTIE ";	
	const string WIN_FINAL_MESSAGE = "Bravo, vous avez gagn\202 !  :) ";
	const string LOSE_FINAL_MESSAGE = "Vous avez perdu !  :( ";

	const int MAX_PLAYER_ATTEMPT = 10;
	const int PASS_CODE_LENGTH = 4;
	const int LENGTH_COLORS_POSSIBILITY = 6;
	string COLOR_CHOICE[LENGTH_COLORS_POSSIBILITY] = { "rouge", "vert", "bleu", "jaune", "mauve", "cyan"};
	
	// CONSTANTE position
	const short CONSOLE_MAX_X = 120;
	const short CONSOLE_MAX_Y = 30;
	const short GAME_TITLE_POS_Y = 1;
	const short SETTINGS_POS_Y = GAME_TITLE_POS_Y + 3;
	const short TEXT_INFOS_POS_Y = GAME_TITLE_POS_Y + 4;
	const short TEXT_DEBUG_POS_X = 8;
	const short TEXT_DEBUG_POS_Y = SETTINGS_POS_Y + 3;
	const short MARGIN_START_POS_X = 9;
	const short MARGIN_START_POS_Y = TEXT_INFOS_POS_Y + 3;
	const short PASS_CODE_POS_X = 55;
	const short PASS_CODE_POS_Y = 24;
	const short SPACING_INFOS_1 = 4, SPACING_INFOS_2 = 8, SPACING_INFOS_3 = 4;
	const short TEXT_GOOD_PLACE_POS_X = 33;
	const short TEXT_WRONG_PLACE_POS_X = 50;
	const short STARTING_PLACE_COUNT_ATTEMPT = MARGIN_START_POS_Y + 2;
	const short ATTEMPT_CURSOR_PLACE_POS_X = 14;
	const short FINAL_MESSAGE_POS_X = 1;
	const short FINAL_MESSAGE_POS_Y = 23;
	const short TEXT_EVALUATION_POS_Y = STARTING_PLACE_COUNT_ATTEMPT + MAX_PLAYER_ATTEMPT + 3;

	// Variable
	bool playerAttemptValidOption = false;
	bool showPasscode = false;
	bool alreadyTookPasscode[PASS_CODE_LENGTH] = {};	// Array of False
	bool alreadyTookPlayerAttempt[PASS_CODE_LENGTH] = {};	// Array of False
	short playerLetterAttemptPosY = STARTING_PLACE_COUNT_ATTEMPT;

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

	gotoxy((CONSOLE_MAX_X / 2 - GAME_MODE_TITLE.size() / 2 ), SETTINGS_POS_Y);
	cout << GAME_MODE_TITLE;

	// Enable debugging mode
	gotoxy(TEXT_DEBUG_POS_X,TEXT_DEBUG_POS_Y);
	cout << "Activer le mode en d\202bogage ? (O/N) : ";
	char letterPlayerChoice;
	do
		letterPlayerChoice = toupper(_getch());
	while (letterPlayerChoice != 'O' && letterPlayerChoice != 'N');

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
		cout << "(" << char(toupper(COLOR_CHOICE[i][0])) << ")";

		for (int j = 1; j < COLOR_CHOICE[i].size(); j++)
			cout << COLOR_CHOICE[i][j];

		if (i < LENGTH_COLORS_POSSIBILITY - 1)
			cout << " , ";
	}
	
	// Display game rules
	gotoxy(MARGIN_START_POS_X, MARGIN_START_POS_Y);
	cout << '#' << setw(SPACING_INFOS_1) << ""  << "Essais" << setw(SPACING_INFOS_2) << "" << "Bien plac\202e(s)" << setw(SPACING_INFOS_3) << "" << "Mal plac\202e(s)";

	gotoxy(0, STARTING_PLACE_COUNT_ATTEMPT);
	for (int i = 1; i <= MAX_PLAYER_ATTEMPT; i++)
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
	do 
	{
		wellPlacedCount = wrongPlacedCount = 0;
		gotoxy(ATTEMPT_CURSOR_PLACE_POS_X, playerLetterAttemptPosY);
		clreol();

		char letterChoiceInProgress;
		// Player choice patern to attempt passcode
		for (int i = 0; i < PASS_CODE_LENGTH; i++)
		{
			do {
				playerAttemptValidOption = false;
				letterChoiceInProgress = _getch();
				
				// If press'Backspace' (8 in oct)
				if (letterChoiceInProgress == 8 && i > 0)
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
			clreol();
			answerEvaluateCode = toupper(_getch());
		} while (answerEvaluateCode != 'O' && answerEvaluateCode != 'N');
		
		cout << answerEvaluateCode;

		if (answerEvaluateCode == 'N')
			continue;

		// For the next attempt
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
				if (playerPasscode[i] == passcode[j])
					if (alreadyTookPasscode[j] == true && alreadyTookPlayerAttempt[i] == true)
					{		
						wrongPlacedCount+=1;
						alreadyTookPasscode[j] = false;
						alreadyTookPlayerAttempt[i] = false;
					}

		// Diplay number of well placed / wrong placed
		gotoxy(TEXT_GOOD_PLACE_POS_X, STARTING_PLACE_COUNT_ATTEMPT + attemptCount);
		cout << wellPlacedCount;
		gotoxy(TEXT_WRONG_PLACE_POS_X, STARTING_PLACE_COUNT_ATTEMPT + attemptCount);
		cout << wrongPlacedCount;
		attemptCount++;

	} while((attemptCount < MAX_PLAYER_ATTEMPT) && wellPlacedCount != PASS_CODE_LENGTH);

	// Display final message (win / lose)
	gotoxy(FINAL_MESSAGE_POS_X, FINAL_MESSAGE_POS_Y);
	if (wellPlacedCount == PASS_CODE_LENGTH)
		cout << WIN_FINAL_MESSAGE;
	else
		cout << LOSE_FINAL_MESSAGE;

	_getch();
}