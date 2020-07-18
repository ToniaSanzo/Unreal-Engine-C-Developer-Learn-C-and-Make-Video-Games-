// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include <string>
#include "HiddenWordList.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount{
    int32 bulls = 0;
    int32 cows  = 0;
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
		virtual void BeginPlay() override;
		virtual void OnInput(const FString& playerInput) override;
		void setupGame();
		void endGame();
		void processGuess(const FString& guess);
		void printWelcomeMsg() const;
		bool isIsogram(const FString& word) const;
		TArray<FString> getValidWords();
		void getBullCows(const FString& guess, int32& bulls, int32& cowCount) const;

	private:
		TArray<FString> isograms;
		FString hiddenWord;
		int32 lives;
		bool bGameOver;
};
