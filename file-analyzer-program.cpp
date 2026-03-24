#include <iostream>
#include "FileAnalyzer.h"
#include <filesystem>

using namespace std;


int main() {
  //cout << std::filesystem::current_path() << endl;

  FileAnalyzer fileAnalyzer;

  string text_read_from_file = fileAnalyzer.readFile("textfile.txt");

  cout << text_read_from_file;

  return 0;
}
