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
        int totalWordCount = 0; // variable to store the number of all words

        // set to store all the words that should be ignored
        unordered_set<string> wordsToExclude = {"e.g.", "the", "The", "an", "a", "and", "as", "in", "with", "of", "by",
        "for", "or", "at", "also", "eg", "is", "it", "its", "on", "over", "that", "then", "these", "to", "was", "which"};

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

            // if failure to access a file then outputing a message about the failure
            if(!ReadFile.is_open()){
                cout << "Failed to open the file\n";
                return "";
            }

            // read the file line by line
            while(getline(ReadFile, textLineFromFile)){
                // reading a text file line by line
                textFromFile += textLineFromFile;
            }

            return textFromFile;
        }


        void saveResultsToTxtFile(string fileName, int amountOfMostFrequentWords){

                // Create and open a text file
                ofstream FileToSaveAnalysisData(fileName);

                // calling the functions from the class
                printHeaderForFileContents(fileName, FileToSaveAnalysisData);

                saveMostFrequentWordsCounts(amountOfMostFrequentWords, FileToSaveAnalysisData);

                saveDistinctWordCount(FileToSaveAnalysisData);

            }


        void analyzeText(string text){

            string word;

            for(int i=0; i < text.length(); i++){

                    if(text[i] == '(' || text[i] == ')' || text[i] == ',' || text[i] == '.'){ // ignoring some text signs
                        continue;
                    } else if (text[i] != ' '){
                        word += text[i]; // gathering a word together while there is no space after another letter
                    } else {

                        auto it = wordCount.find(word); // finding the collected word in the wordCount map
                        if(it == wordCount.end()){
                                if(word.length() > 1 && wordsToExclude.find(word) == wordsToExclude.end()){
                                    wordCount.insert({word,1}); // inserting the word into the wordCount map
                                    totalWordCount++; // incrementing the number stored in the totalWordCount variable
                                }
                        } else {
                            wordCount[word]++; // incrementing the number of occasions of the word found in the text
                        }
                        word = ""; // erasing the word before scanning for the next possible word in the text
                    }

            }

            cout << "\n\n" << "   Total word count" << " : " << totalWordCount << "\n\n";
        }



    protected:

    private:
        // map to store words and their amounts
        map<string,int> wordCount;


        // function to write header to the file where the results will be saved
        void printHeaderForFileContents(string fileName, ofstream& FileToSaveAnalysisData){

                FileToSaveAnalysisData << "================================================================\n\n";
                FileToSaveAnalysisData << "     Results of analysis for " << nameOfFile << "\n\n";
                FileToSaveAnalysisData << "================================================================\n";
                FileToSaveAnalysisData << "\n\n" << "     Total word count" << " : " << totalWordCount << "\n\n";
                FileToSaveAnalysisData << "----------------------------------------------------------------\n";

            }

        // function to write to the file the information about user defined amount of the most frequent words
        void saveMostFrequentWordsCounts(int amountOfMostFrequentWords, ofstream& FileToSaveAnalysisData){
            // creating a vector and filling it with all elements from the wordCount map
            vector<pair<string,int>> vec(wordCount.begin(), wordCount.end());

            // sorting the vector
            sort(vec.begin(), vec.end(),
                     [](const auto& a, const auto& b){
                        return a.second > b.second; // descending order
                     }
                 );

            FileToSaveAnalysisData << "\n\n" << "    " << amountOfMostFrequentWords << " most frequent words count: " << "\n\n";

            // writing to the file the top amount of elements from the vector that equals the amount entered by a user
            for(int i = 0; i < amountOfMostFrequentWords && vec.size(); i++){
                FileToSaveAnalysisData << "     " << vec[i].first << " : " << vec[i].second << endl;
            }

            FileToSaveAnalysisData << "\n\n" << "----------------------------------------------------------------\n";
        }

        // function to write to the file the information about distinct words found in text
        void saveDistinctWordCount(ofstream& FileToSaveAnalysisData){

            FileToSaveAnalysisData << "\n\n" << "    All distinct words count: " << "\n\n";
                FileToSaveAnalysisData << "----------------------------------------------------------------\n";

                for(auto item : wordCount){
                    FileToSaveAnalysisData << "     " << item.first << " : " << item.second << "\n";
                }
        }
};

#endif // FILEANALYZER_H
