#ifndef FILEANALYZER_H
#define FILEANALYZER_H
#include <iostream>
#include <fstream>
#include <map>

using namespace std;


class TextFileAnalyzer
{
    public:
        string nameOfFile;
        map<string,int> wordCount;
        int totalWordCount;
        TextFileAnalyzer();
        virtual ~TextFileAnalyzer();

        string readFile(string fileName){

            nameOfFile = fileName;

            // creation of a text string variable which is used to output the text from file
            string textLineFromFile;

            // creation of a text string variable which is used to store the text from file
            string textFromFile;

            // read from text file
            fstream ReadFile(fileName);

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

        void saveResultsToTxtFile(string fileName){
                // Create and open a text file
                ofstream FileToSaveAnalysisData(fileName);

                FileToSaveAnalysisData << "================================================================\n\n";
                FileToSaveAnalysisData << "Results of analysis for " << nameOfFile << "\n\n";
                FileToSaveAnalysisData << "================================================================\n\n";
                FileToSaveAnalysisData << "\n\n" << "Total word count" << " : " << totalWordCount << "\n\n";
                FileToSaveAnalysisData << "----------------------------------------------------------------\n\n";

                for(auto item : wordCount){
                    FileToSaveAnalysisData << item.first << " : " << item.second << "\n";
                }
            }

        void analyzeText(string text){

            string word;

            for(int i=0; i < text.length(); i++){
                    if(text[i] == '(' || text[i] == ')' || text[i] == ',' || text[i] == '.'){
                        continue;
                    } else if (text[i] != ' '){
                        word += text[i];
                    } else {
                        totalWordCount++;

                        auto it = wordCount.find(word);
                        if(it == wordCount.end()){
                                if(word.length() > 1 && word != "e.g." && word != "the" && word != "The"){
                                    wordCount.insert({word,1});
                                }
                        } else {
                            wordCount[word]++;
                        }
                        word = "";
                    }

            }

            cout << "\n\n" << "Total word count" << " : " << totalWordCount << "\n\n";

                for(auto item : wordCount){
                    cout << item.first << " : " << item.second << "\n";
                }

        }

    protected:

    private:
};

#endif // FILEANALYZER_H
