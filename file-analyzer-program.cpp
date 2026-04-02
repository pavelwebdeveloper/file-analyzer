#include <iostream>
#include "TextFileAnalyzer.h"
#include <filesystem>
#include <regex>

using namespace std;

string checkTxtFileNameUserInput(){

    string userInput;

    cin >> userInput;

    regex txtFileNamePattern(".*\\.txt$");

    while(!regex_match(userInput, txtFileNamePattern)){
        cout << "Invalid txt file name. Please, try again: ";
        cin.clear(); // Reset input errors
        cin.ignore(10000, '\n'); // Remove bad input
        cin >> userInput;
      }

    cout << "You entered: " << userInput << "\n";

    return userInput;
}

int checkIntegerUserInput(){

    int userInput;

    /*while(true){
        cin >> userInput;

        //cout << "Inside checkIntegerUserInput function and the value of userInput is: " << userInput << "\n";

        if(cin >> userInput){
            break;
        }
        cout << "Invalid number. Please, try again: ";
        cin.clear(); // Reset input errors
        cin.ignore(10000, '\n'); // Remove bad input
        cin >> userInput;
      }*/

    while(!(cin >> userInput)){
        cout << "Invalid number. Please, try again: ";
        cin.clear(); // Reset input errors
        cin.ignore(10000, '\n'); // Remove bad input
        cin >> userInput;
      }

    cout << "You entered: " << userInput << "\n";

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

    // get from a user the amount of the most frequent words to display separately
    cout << "Please, enter the amount of the most frequent words to save: ";
    int mostFrequentWordsAmount = checkIntegerUserInput();

    cout << "About to create TextFileAnalyzer class: ";

    TextFileAnalyzer textFileAnalyzer;

    string text_to_analyze = textFileAnalyzer.readFile(userInputFileToAnalyze);

    cout << text_to_analyze;

    textFileAnalyzer.analyzeText(text_to_analyze);

    textFileAnalyzer.saveResultsToTxtFile(userInputFileToSaveResults, mostFrequentWordsAmount);


  return 0;
}
