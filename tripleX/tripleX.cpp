/**
 * @Title:TripleX
 * @author: Tonia Sanzo
 * @Date: 7/16/2020
 * @Version: 1.0 
 * @Citation: - Udemy unreal engine C++ tutorial
 */

#include <iostream>

using namespace std;

// Print the introduction to every level, with the current level
void printIntroduction(int difficulty){
    cout << "\n\nYou are a CIA agent, breaking into a rouge states nuclear program [" << difficulty 
        <<  "] secure server room\nEnter the correct code to continue...\n\n";
}

// Prompt the user with a number puzzle
bool playGame(int difficulty){
    printIntroduction(difficulty);
    bool aFlag = false, bFlag = false, cFlag = false;

    //  Values used in tripleX game
    int codeA = (rand() % difficulty) + 1, codeB = (rand() % difficulty) + 1, codeC = (rand() % difficulty) + 1;
    int codeSum = codeA + codeB + codeC, codeProduct = codeA * codeB * codeC;
    // Values used for getting user input
    int value = 0;

    // Print the sum and product of the 3 values
    cout << "Sum of 3 digits: " << codeSum << endl;
    cout << "Product of 3 digits: " << codeProduct << endl;
    cout << "Make sure you enter x after you finish typing in the code, i.e. 1 2 3 x" << endl;
    
    while(cin >> value){
        // Check codeA
        if(!aFlag && value == codeA){
            aFlag = true;
            continue;
        }

        // Check codeB
        if(!bFlag && value == codeB){
            bFlag = true;
            continue;
        }

        // Check codeC
        if(!cFlag && value == codeC){
            cFlag = true;
            continue;
        }
    }

    return aFlag && bFlag && cFlag;

}

// Run the loop
int main(){
    const int MAX_DIFFICULTY = 10;
    int difficulty = 2;


    while(difficulty <= MAX_DIFFICULTY){
        bool bLevelComplete = playGame(difficulty);
        cin.clear();    // Clears any errors
        cin.ignore();   // discard the buffer


        if(bLevelComplete){
            // increase the level difficulty
            cout << "\n\n  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" 
                 << "Congratulations operative, you are one step closer to disarming the WMD\n"
                << "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            difficulty++;
        } else {
            cout << "\n\n  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" 
                 << "THE ROGUES AGENTS IPS PUSHED YOU OUT OF THE SYSTEM! BE MORE CAUTIOUS!\n"
                << "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        }

    }
    cout << "Well done agent the WMD has been disarmed" << endl;

    return 0;
}