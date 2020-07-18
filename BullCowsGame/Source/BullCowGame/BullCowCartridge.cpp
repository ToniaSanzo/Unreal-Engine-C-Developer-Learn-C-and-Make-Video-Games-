// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    isograms = getValidWords(); // Return an array of all isograms between 4 and 8 characters(iunclusively)
    setupGame();

    PrintLine(TEXT("Number of Valid Words %i"), isograms.Num());
}


void UBullCowCartridge::OnInput(const FString& playerInput) // When the player hits enter
{
    ClearScreen();
    printWelcomeMsg();

    // if the game is over then clear screen and setup game
    // else checking the player guess
    if(bGameOver){
        ClearScreen();
        setupGame();
    }
    else{ // Check the player guess
        processGuess(playerInput);
    }
}


void UBullCowCartridge::setupGame(){ // Init variables
    // Choose a random hiddenWord from isograms
    hiddenWord = isograms[FMath::RandRange(0, isograms.Num() - 1)];
    

    lives = hiddenWord.Len();
    bGameOver = false;

    ClearScreen();
    printWelcomeMsg();

    PrintLine(TEXT("The hidden word is: %s."), *hiddenWord);// Debug line  
}


void UBullCowCartridge::endGame(){ 
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again..."));
}


void UBullCowCartridge::printWelcomeMsg() const{ // Print welcome message
     
    // Print the opening statements
    PrintLine(TEXT("Welcome to the Bull Cows Game!"));
    PrintLine(TEXT("Guess the %i letter word!"), hiddenWord.Len());
    PrintLine(TEXT("Type in your guess.\npress enter to continue..."));
}


void UBullCowCartridge::processGuess(const FString& guess){
    if(guess == hiddenWord){ // Guess is correct
        ClearScreen();
        PrintLine(TEXT("Congrats! you win!"));
        endGame();
        return;
    } 

    // Confirm the guess and hiddenWord have the same number of characters
    if(hiddenWord.Len() != guess.Len()){
        PrintLine(TEXT("Uh oh you guessed the wrong number of characters"));
        PrintLine(TEXT("The hidden word is %i characters long\nyou have %i lives left!"), hiddenWord.Len(), lives);
        return;
    }

    // Confirm the guess is an isogram
    if(!isIsogram(guess)){
        PrintLine(TEXT("Whoopsie, remember to enter an isogram.\n(A word with no repeating characters)"));
        return;
    }

    PrintLine(TEXT("You guessed wrong you have %i lives left!"), --lives);

    if(lives <= 0){ // If the user lost, print lost message
        ClearScreen();
        PrintLine(TEXT("You lost :(\nThe hidden word was: %s\n\n"), *hiddenWord);
        endGame();
    }

    // Show the player the bulls and cows
    FBullCowCount count;
    getBullCows(guess, count.bulls, count.cows);

    PrintLine(TEXT("You have %i bulls, and %i cows"), count.bulls, count.cows);
}


bool UBullCowCartridge::isIsogram(const FString& word) const { // Return true if the word is a isogram, otherwise false
    for(int32 i = 0; i < word.Len(); i++){
        for(int32 j = i + 1; j < word.Len(); j++){
            if(word[i] == word[j]){
                return false;
            }
        }
    }
    return true;
}


TArray<FString> UBullCowCartridge::getValidWords(){ // Filter out the valid words from our words array
    TArray<FString> isograms;
    
    // Print out all the words between 4 and 8 characters (inclusive), for the first 10 FStrings in words
    for(FString word : words){
        if(word.Len() >= 4 && word.Len() <= 8 && isIsogram(word)){
            isograms.Emplace(word);
        }
    }
    return isograms;
}


void UBullCowCartridge::getBullCows(const FString& guess, int32& bulls, int32& cows) const{ // Determine the number of bulls and cows for a guess, update the corresponding calling parameter variables
    bulls = 0; cows = 0;
    
    // For every index guess is same as index hiddenWord, bulls++
    // if not a bull was it a cow? if yes cows++
    for(int32 i = 0; i < guess.Len(); i++){
        if(hiddenWord[i] == guess[i]){
            bulls++;
            continue;
        }

        for(int32 j = 0; j < guess.Len(); j++){
            if(guess[i] == hiddenWord[j]){
                cows++;
                break;
            }
        }
    }
}