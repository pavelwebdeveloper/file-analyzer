#include <iostream>
#include "TextFileAnalyzer.h"
#include <filesystem>

using namespace std;


int main() {
  //cout << std::filesystem::current_path() << endl;

  TextFileAnalyzer textFileAnalyzer;

  string text_read_from_file = textFileAnalyzer.readFile("textfile.txt");

  cout << text_read_from_file;

  textFileAnalyzer.analyzeText(text_read_from_file);

  textFileAnalyzer.saveResultsToTxtFile("analysisresults.txt");

  return 0;
}
