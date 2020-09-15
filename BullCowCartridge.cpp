// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    //PrintLine(FString::Printf(TEXT("The Hidden Word is: %s"), *HiddenWord));
    PrintLine(TEXT("The number of possible words is %i"), Words.Num());
    PrintLine(TEXT("The number of valid words is %i"), GetValidWords(Words).Num());
    PrintLine(TEXT("The Hidden Word is: %s"), *HiddenWord); // string argument should be dereferenced("\0")

}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if(bGameOver){
        ClearScreen();
        SetupGame();
    }
    else{
        ProcessGuess(PlayerInput);
        
    }
}

void UBullCowCartridge::SetupGame(){
    PrintLine(TEXT("Hi there!"));

    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter words"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue..."));

    // const TCHAR HW[] = TEXT("cake");
}

void UBullCowCartridge::EndGame(){
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess){
    if(Guess == HiddenWord){
        PrintLine(TEXT("You have won!"));
        EndGame();
        return;
    }

    if(Guess.Len() != HiddenWord.Len()){
        PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);
        return;
    }

    if(!IsIsogram(Guess)){
        PrintLine(TEXT("Should not include repeating letters, guess again"));
        return;
    }

    PrintLine(TEXT("You lost a life!"));
    --Lives;

    if(Lives <= 0){
        ClearScreen();
        EndGame();
        return;
    }
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const{

    // int32 Index;
    // int32 Comparison = Index + 1;

    // for(int32 Index = 0, Comparison = Index + 1;Comparison < Word.Len();Comparison++){
    //     if(Word[Index]==Word[Comparison]){
    //         return false;
    //     }

    // }

    for(int32 Index = 0; Index < Word.Len(); Index++){
        for(int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++){
            if(Word[Index]==Word[Comparison]){
                return false;
            }
        }
    }
    // for(int32 Index=0;Index < Word.Len(); Index++){
    //     PrintLine(TEXT("%c"), Word[Index]);
    // }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const{
    TArray<FString> ValidWords;

    for(int32 Index = 0; Index < WordList.Num(); Index ++){
        if(WordList[Index].Len()>=4 && WordList[Index].Len()<=8 && IsIsogram(WordList[Index])){
                ValidWords.Emplace(WordList[Index]);
        }
    }

    // for(int32 Index = 0; Index<ValidWords.Num(); Index++){
    //     PrintLine(TEXT("%s"), *ValidWords[Index]);
    // }
    return ValidWords;
}