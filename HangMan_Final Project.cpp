#include <iostream>
#include <string>
using namespace std;


// Main Structure.
struct Hangman
{
    string wordName{ "0" }, wordHint{ "0" }, answer{ "" }, wordType{ "0" };

    string keyboard = "\t\t  ___________________________________  \n"
        "\t\t |             KEYBOARD              | \n"
        "\t\t |-----------------------------------| \n"
        "\t\t | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | \n"
        "\t\t |-----------------------------------| \n"
        "\t\t | a | b | c | d | e | f | g | h | i | \n"
        "\t\t |-----------------------------------| \n"
        "\t\t | j | k | l | m | n | o | p | q | r | \n"
        "\t\t |-----------------------------------| \n"
        "\t\t | s | t | u | v | w | x | y | z | 0 | \n"
        "\t\t |-----------------------------------| \n"
        "\t\t |___________________________________| \n";

    int countHang{ 0 };
    char ch{ 0 };
    bool active{ 1 }, flag{ 1 }, tag{ 1 };
    bool exit{ 0 };

    Hangman()
    {
        active = 1;
        while (active)
        {
            cout << "\n\n\t\t\t\t                                   M A I N M E N U  \n";
            cout << "\t\t\t\t                          ****** Welcome to HangMan Game! ****** \n";

            cout << "\n\n\t\t\t                                   ~~ HangMan Game Rules! ~~                        \n\n"
                "\t\t\t  1. Choose a person to be the 'Host' as Player1. This player will initiate the puzzle      \n"
                "\t\t\t  for Player2 by choosing a secret word to be guessed.                                      \n\n"
                "\t\t\t  2. If you are the host, choose a secret word using numbers and small alphabetical letters.\n"
                "\t\t\t  The other players will need to guess your word letter by letter, so choose a word you     \n"
                "\t\t\t  think will be difficult to guess.                                                         \n\n"
                "\t\t\t  3. Whenever Player2 guesses a wrong letter, he/she get a strike that brings the           \n"
                "\t\t\t  player closer to losing. The game draws a simple stick figure of a man being hung,        \n"
                "\t\t\t  adding a new part to the drawing with every wrong answer.                                 \n\n";

            cout << "\t\t Your Options: \n";
            cout << "\t\t 1. Play Game. \n";
            cout << "\t\t 2. Exit Game. \n" << endl;
            cout << "\t\t Please select option 1 or 2 : ";

            // Choice menu with conditions incase of wrong input.
            cin >> ch;
            if (ch == '1')
            {
                active = 0;
                HintWord();
            }
            else
            {
                active = 0;
                exit = 1;
            }
        }
    };


    void HintWord()
    {
        cout << "\n\t\t Hey Host! Please enter the Secret Word to be guessed! \n";
        cout << "\t\t Enter Here: ";
        cin >> wordName;

        cout << "\n\t\t Enter word type e.g Name, Movie, Food, Song .. etc: \n";
        cout << "\t\t Enter Here: ";
        cin >> wordHint;

        getline(cin, wordType);

        cout << "\n\t\t Enter Hint: ";
        getline(cin, wordHint);

        // Converting all of it into Underscores.
        for (unsigned i = 0; i < wordName.length(); i++)
            answer += "_";

        HangBoard();
    }


    void HangBoard()
    {
        int i = 0;
        active = 1;

        while (active)
        {
            HangCheck();
            //Displaying the word as Underscores with spaces.
            for (unsigned i = 0; i < wordName.length(); i++)
            {
                cout << answer[i] << " ";
            }

            cout << "\n\nHint: " << wordHint << " " << endl;
            cout << "\n'#' will be shown on the keyboard if the letter's already guessed." << endl;
            cout << "Enter '.' to Exit." << endl;
            cout << "\n\n" << keyboard;

            if (flag == 1)
            {
                cout << "\t\t ~X~ : "; cin >> ch;
            }
            else
            {
                cout << "\t\t ~O~ : "; cin >> ch;
            }

            if (ch == '.')
            {
                Hangman();
                active = 0;
                break;
            }

            // Converting.
            if (ch <= 90 && ch >= 65)
                ch += 32;

            // Incase of input of any of those signs to keep keyboard same outline format, using # sign as letter being taken.
            if (ch != '|' && ch != '_' && ch != '-' && keyboard.find(ch) != string::npos)
                keyboard[keyboard.find(ch)] = '#';

            if (ch != '#')
                tag = 0;

            if (ch == '#' && flag == 1 && tag == 1)
            {
                ch = wordName[0];
                flag = 0;
            }

            // Checking if correct input here with find function.
            i = wordName.find(ch);
            while (wordName.find(ch, i) != string::npos)
            {

                answer[wordName.find(ch, i)] = ch;
                i++;
            }
            if (wordName.find(ch) == string::npos)
            {
                countHang++;
                cout << "\a";
            }
            if (countHang == 6)
            {
                Menu();
            }
            else if (answer == wordName)
            {
                Menu();
            }
            system("cls");
        }
    }

    void Menu()
    {
        active = 1;
        while (active)
        {
            if (countHang == 6)
            {
                cout << "\n\t\t OOPS! HangMan died." << endl;
                cout << "\n\t\t Oh No, Seems like you're out of tries." << endl;
                cout << "\t\t Sorry! You have lost the Game. \n" << endl;
                cout << "\t\t Your Options: \n";
                cout << "\t\t 1. Hey, Do you wanna play once more?" << endl;
                cout << "\t\t 2. EXIT. Thank You for Playing! Have a Good Time." << endl;
            }
            else
            {
                cout << "\n\t\t YAYY! HangMan Lives!" << endl;
                cout << "\n\t\t You guess the word \"" << wordName << "\" correctly. \n";
                cout << "\t\t Congratulations! You have won the Game. \n" << endl;
                cout << "\t\t Your Options: \n";
                cout << "\t\t 1. Hey, Do you wanna play once more?" << endl;
                cout << "\t\t 2. EXIT. Thank You for Playing! Have a Good Time." << endl;
            }
            cout << "\n\t\t What's the mood? Enter here: ";
            cin >> ch;
            if (ch == '1')
            {
                active = 0;
                countHang = 0;
                flag = 1;
                tag = 1;
                wordName = "0";
                wordHint = "0";
                answer = "";
                HintWord();
            }

            else if (ch == '2')
            {
                active = 0;
                exit = 1;
            }
        }
    }

    void HangCheck()
    {
        if (countHang == 0)
        {
            cout << "\t\t     ______                     \n"
                "\t\t    |      |                    \n"
                "\t\t    |      :                    \n"
                "\t\t    |                           \n"
                "\t\t    |                           \n"
                "\t\t    |                           \n"
                "\t\t ___|___                        \n\n\n";
        }
        else if (countHang == 1)
        {
            cout << "\t\t     ______                     \n"
                "\t\t    |      |                    \n"
                "\t\t    |      :                    \n"
                "\t\t    |      O                    \n"
                "\t\t    |                           \n"
                "\t\t    |                           \n"
                "\t\t ___|___                        \n\n\n";
        }
        else if (countHang == 2)
        {
            cout << "\t\t     ______                     \n"
                "\t\t    |      |                    \n"
                "\t\t    |      :                    \n"
                "\t\t    |      O                    \n"
                "\t\t    |      |                    \n"
                "\t\t    |                           \n"
                "\t\t ___|___                        \n\n\n";
        }
        else if (countHang == 3)
        {
            cout << "\t\t     ______                     \n"
                "\t\t    |      |                    \n"
                "\t\t    |      :                    \n"
                "\t\t    |      O                    \n"
                "\t\t    |      |\\                  \n"
                "\t\t    |                           \n"
                "\t\t ___|___                        \n\n\n";
        }
        else if (countHang == 4)
        {
            cout << "\t\t     ______                     \n"
                "\t\t    |      |                    \n"
                "\t\t    |      :                    \n"
                "\t\t    |      O                    \n"
                "\t\t    |     /|\\                  \n"
                "\t\t    |                           \n"
                "\t\t ___|___                        \n\n\n";
        }
        else if (countHang == 5)
        {
            cout << "\t\t     ______                     \n"
                "\t\t    |      |                    \n"
                "\t\t    |      :                    \n"
                "\t\t    |      O                    \n"
                "\t\t    |     /|\\                  \n"
                "\t\t    |     /                     \n"
                "\t\t ___|___                        \n\n\n";
        }
        else if (countHang == 6)
        {
            cout << "\t\t     ______                     \n"
                "\t\t    |      |                    \n"
                "\t\t    |      :                    \n"
                "\t\t    |      O                    \n"
                "\t\t    |     /|\\                  \n"
                "\t\t    |     / \\                  \n"
                "\t\t ___|___                        \n\n\n";
        }
    }
};


// Main Code.
int main()
{
    Hangman game;
    if (game.exit == 1)
    {
        return 0;
    }

    return 0;
}



