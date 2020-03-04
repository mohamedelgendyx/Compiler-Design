#include<conio.h>
#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
using namespace std;

#define Rules_Length 15
#define Max_Input_Length 100

struct grammer {
    char p[20];
    char prod[20];
}g[Rules_Length];

int main()
{
    int tempStackPosition;
    char selectedCharacter, tempStack[Max_Input_Length];

    ifstream rules;
    string line;
    rules.open("rules.txt");

    //Read rules from file to g[15]
    for (int y = 0;y < Rules_Length;y++)
    {
        if (getline(rules, line)) {
            int x = 0;

            for (char& c : line) {
                tempStack[x] = c;
                x++;
            }

            tempStack[x] = '\0';

            cout << "(" << tempStack << ")" << endl;
            strncpy(g[y].p, tempStack,1);
            strcpy(g[y].prod, &tempStack[3]);
        }
    }

    //Take user input
    char input[Max_Input_Length];
    cout << "\nEnter Input:";
    cin >> input;
    int inputLength = strlen(input);

    char stack[Max_Input_Length];
    int lastOperation;
    int stackSize = 0;
    int currentCharacterIndex = 0;
    //Push first character to stack
    selectedCharacter = input[currentCharacterIndex];
    stack[stackSize] = selectedCharacter;

    currentCharacterIndex++;
    cout << "\n\nStack\t\tInput\t\tAction";
    do
    {
        stackSize++;
        //last operation ?  2 => reduce ,else => shift
        lastOperation = 1;
        while (lastOperation != 0)
        {
            cout << "\n";
            for (int p = 0;p < stackSize;p++)
            {
                cout << stack[p];
            }
            cout << "\t\t";
            for (int p = currentCharacterIndex;p < inputLength;p++)
            {
                cout << input[p];
            }

            if (lastOperation == 2)
            {
                cout << "\t\tReduced";
            }
            else
            {
                cout << "\t\tShifted";
            }

            lastOperation = 0;

            getch();//interrupt
            //try reducing
            for (int currentStackPosition = 0;currentStackPosition < stackSize;currentStackPosition++)
            {
                // empty the temp stack
                for (int l = 0;l < Max_Input_Length;l++)
                {
                    tempStack[l] = '\0';
                }

                // Move from stack to temp stack and fill empty with '\0'
                tempStackPosition = 0;
                for (int l = currentStackPosition;l < stackSize;l++) //removing first character
                {
                    tempStack[tempStackPosition] = stack[l];
                    tempStackPosition++;
                }

                //now compare each possibility with production
                for (int currentRuleIndex = 0;currentRuleIndex < Rules_Length;currentRuleIndex++)
                {
                    //compare if the stack contains the production of the rule
                    int canReduce = strcmp(tempStack, g[currentRuleIndex].prod);

                    //if canReduce is zero then match is found
                    if (canReduce == 0)
                    {
                        //remove the production from stack
                        for (int l = currentStackPosition;l < Max_Input_Length;l++)
                        {
                            stack[l] = '\0';
                        }

                        stackSize = currentStackPosition;
                        //replace the production with the non-terminal (append)
                        strcat(stack, g[currentRuleIndex].p);
                        stackSize++;
                        lastOperation = 2;
                    }
                }
            }
        }

        //moving input
        selectedCharacter = input[currentCharacterIndex];
        stack[stackSize] = selectedCharacter;
        currentCharacterIndex++;
    } while (strlen(stack) != 1 && stackSize != inputLength);

    if (strlen(stack) == 1)
    {
        cout << "\n ---String Accepted---\n";
    }
    else {
        cout << "\n ---String is not Accepted---\n";
    }

    getch();
    return 0;
}
