#ifndef FILEANALYZER_H
#define FILEANALYZER_H
#include <iostream>
#include <fstream>

using namespace std;


class FileAnalyzer
{
    public:
        FileAnalyzer();
        virtual ~FileAnalyzer();

        string readFile(string fileName){
            // creation of a text string variable which is used to output the text from file
            string textLineFromFile;

            // creation of a text string variable which is used to store the text from file
            string textFromFile;

            // read from text file
            ifstream ReadFile(fileName);

            if(!ReadFile.is_open()){
                cout << "Failed to open the file\n";
                return "";
            }

            // read the file line by line
            while(getline(ReadFile, textLineFromFile)){
                // output text
                //cout << textLineFromFile << endl;
                textFromFile += textLineFromFile;
            }

            cout << "The text has been read !!!!!!!!\n";

            return textFromFile;
        }

    protected:

    private:
};

#endif // FILEANALYZER_H
