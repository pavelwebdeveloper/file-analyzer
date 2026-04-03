#ifndef FILEANALYZER_H
#define FILEANALYZER_H
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;


class TextFileAnalyzer
{
    public:
        string nameOfFile;
        map<string,int> wordCount;
        int totalWordCount = 0;
        TextFileAnalyzer();
        virtual ~TextFileAnalyzer();
        unordered_set<string> wordsToExclude = {"e.g.", "the", "The", "an", "a", "and", "as", "in", "with", "of", "by",
        "for", "or", "at", "also", "eg", "is", "it", "its", "on", "over", "that", "then", "these", "to", "was", "which"};

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

            return textFromFile;
        }


        void saveResultsToTxtFile(string fileName, int amountOfMostFrequentWords){

                // Create and open a text file
                ofstream FileToSaveAnalysisData(fileName);

                printHeaderForFileContents(fileName, FileToSaveAnalysisData);

                saveMostFrequentWordsCounts(amountOfMostFrequentWords, FileToSaveAnalysisData);

                saveDistinctWordCount(FileToSaveAnalysisData);

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
                                if(word.length() > 1 && wordsToExclude.find(word) == wordsToExclude.end()){
                                    wordCount.insert({word,1});
                                }
                        } else {
                            wordCount[word]++;
                        }
                        word = "";
                    }

            }

            cout << "\n\n" << "     Total word count" << " : " << totalWordCount << "\n\n";

                for(auto item : wordCount){
                    cout << item.first << " : " << item.second << "\n";
                }

            cout << "----------------------------------------------------------------\n";

        }



    protected:

    private:

        void printHeaderForFileContents(string fileName, ofstream& FileToSaveAnalysisData){

                FileToSaveAnalysisData << "================================================================\n\n";
                FileToSaveAnalysisData << "     Results of analysis for " << nameOfFile << "\n\n";
                FileToSaveAnalysisData << "================================================================\n";
                FileToSaveAnalysisData << "\n\n" << "       Total word count" << " : " << totalWordCount << "\n\n";
                FileToSaveAnalysisData << "----------------------------------------------------------------\n";

            }

        void saveMostFrequentWordsCounts(int amountOfMostFrequentWords, ofstream& FileToSaveAnalysisData){
            vector<pair<string,int>> vec(wordCount.begin(), wordCount.end());

            sort(vec.begin(), vec.end(),
                     [](const auto& a, const auto& b){
                        return a.second > b.second; // descending
                     }
                 );

            FileToSaveAnalysisData << "\n\n" << "   " << amountOfMostFrequentWords << " most frequent words count: " << "\n\n";

            for(int i = 0; i < amountOfMostFrequentWords && vec.size(); i++){
                FileToSaveAnalysisData << "     " << vec[i].first << " : " << vec[i].second << endl;
            }

            FileToSaveAnalysisData << "\n\n" << "----------------------------------------------------------------\n";
        }

        void saveDistinctWordCount(ofstream& FileToSaveAnalysisData){
            FileToSaveAnalysisData << "\n\n" << "   Distinct words count: " << "\n\n";
                FileToSaveAnalysisData << "----------------------------------------------------------------\n";

                for(auto item : wordCount){
                    FileToSaveAnalysisData << "     " << item.first << " : " << item.second << "\n";
                }
        }
};

#endif // FILEANALYZER_H
