#include <iostream>
#include "TextFileAnalyzer.h"
#include <filesystem>
#include <regex>

using namespace std;

// this function that checks if a user inputs a correct file name
string checkTxtFileNameUserInput(){

    string userInput;

    cin >> userInput;

    regex txtFileNamePattern(".+\\.txt$");

    // repeat input until a user enters a correct file name
    while(!regex_match(userInput, txtFileNamePattern)){
        cout << "Invalid txt file name. Please, try again: ";
        cin.clear(); // Reset input errors
        cin.ignore(10000, '\n'); // Remove bad input
        cin >> userInput;
      }

    cout << "You entered: " << userInput << "\n";

    return userInput;
}

// this function that checks if a user inputs a correct number
int checkIntegerUserInput(int numberOfWordsTotal){

    int userInput;

    // repeat input until a user enters a correct number
    while(!(cin >> userInput) || userInput > numberOfWordsTotal || userInput < 0){
        if(userInput > numberOfWordsTotal || userInput < 0){
            cout << "The amount cannot be negative or bigger than the total amount of words. Please, try again: ";
        }else{
            cout << "Invalid number. Please, try again: ";
        }
        cin.clear(); // Reset input errors
        cin.ignore(10000, '\n'); // Remove bad input
      }

    cout << "You entered: " << userInput << "\n\n";

    return userInput;
}


int main() {
      // code to find out the current working directory of the program
      //cout << std::filesystem::current_path() << endl;

    // get from a user the name of a file to analyze
    cout << "Please, enter the name of a file to analyze: ";
    string userInputFileToAnalyze = checkTxtFileNameUserInput();

    // get from a user the name of a file to save results
    cout << "Please, enter the name of a file to save results (e.g. analysis_results.txt): ";
    string userInputFileToSaveResults = checkTxtFileNameUserInput();

    // creation of an object from TextFileAnalyzer class
    TextFileAnalyzer textFileAnalyzer;


    string text_to_analyze = textFileAnalyzer.readFile(userInputFileToAnalyze);

    if(text_to_analyze.length() > 0){

        textFileAnalyzer.analyzeText(text_to_analyze);

        // get from a user the amount of the most frequent words to display separately
        cout << "Please, enter the amount of the most frequent words to display separately from other words: ";
        int mostFrequentWordsAmount = checkIntegerUserInput(textFileAnalyzer.totalWordCount);

        textFileAnalyzer.saveResultsToTxtFile(userInputFileToSaveResults, mostFrequentWordsAmount);

        cout << "The results have successfully been saved to " << userInputFileToSaveResults << "\n\n";
    } else{
        return 0;
    }
}
