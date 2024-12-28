/***************************************
The Stongest Link
Author: Dylan Dorey
Date Completed: 10/24/24
Description: A triva game that allows the user to answer trivia questions and attempt to get as many question right in a row as possible
***************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include "LinkedList.hpp"
using namespace std;

/// @brief A question object that stores a question prompt, potential answers, and a correct answer value
class Question
{
   private:

   string questionPrompt;
   string firstText;
   string secondText;
   string thirdText;
   string fourthText;
   int correctIndex;
   array<string, 4> answerOptions;

   public:

   //Constructor for the Question object
   Question(string qP, string fiT, string sT, string tT, string foT, int cI) 
      : questionPrompt(qP), firstText(fiT), secondText(sT), thirdText(tT), fourthText(foT), answerOptions{fiT, sT, tT, foT}, correctIndex(cI) {}

   
   /// @brief Getter for the question prompt
   /// @return the question prompt
   string getPrompt()
   {
      return questionPrompt;
   }

   /// @brief Getter for one of the answer options based on a passed in index parameter
   /// @param index the desired index of the answer option
   /// @return the desired answer option
   string getAnswerOptionByIndex(int index)
   {
      return answerOptions.at(index);
   }

   /// @brief Getter for the correct answer index value
   /// @return the correct answer's index from the array of answer options
   int getCorrectAnswerIndex()
   {
      return correctIndex;
   }
};

/// @brief populates the linked list of questions generated from an input file
/// @param qList reference to the linked list in main
/// @return if the file was opened or not
bool populateQuestionListFromFile(LinkedList<Question> &qList)
{
   //input file stream for the SampleQuestions.txt file
   ifstream inFile;

   //open SampleQuestions.txt file
   inFile.open("SampleQuestions.txt");

   // Check to make sure the file was opened successfully
   if (!inFile.is_open())
   {
      //if not, return false
      return false;
   }
   else
   {
      //create a string for each line in the file
      string fileLine;

      //while the fileLine has a value in it
      while (getline(inFile, fileLine))
      {
         //store the fileLine into a string input buffer
         istringstream stringStream(fileLine);

         array<string, 4> optionsData;

         //strings for the prompt and answer
         string prompt, answer;

         //store the first to values before the first two delimiters into the prompt and answer string values
         getline(stringStream, prompt, ';');
         getline(stringStream, answer, ';');

         //store the rest of the information into the options data array as the potential answer
         for (int index = 0; index < optionsData.size(); index++)
         {
            getline(stringStream, optionsData.at(index), ';');
         }

         //convert the correct answer index value to an int
         int convertedAnswer;
         istringstream convert(answer);
         convert>>convertedAnswer;

         //store values read from file into new question
         Question newQuestion = Question(prompt, optionsData.at(0), optionsData.at(1), optionsData.at(2), optionsData.at(3), convertedAnswer-1);

         //add the question to the linked list
         qList.pushBack(newQuestion);
      }

      //close SampleQuestions.txt file
      inFile.close();

      //return true because the file was opened successfully
      return true;
   }
}

int main() 
{
   //linked list of Question objects
   LinkedList<Question> questionList;

   //the users selected answer, the correct answers amount, the most answers answered correctly in a row, and the question number
   int userAnswer = 0;
   int correctAnswerCount = 0;
   int strongestLinkAmount = 0;
   int questionIndex = 1;

   //populate the question linked list from the file
   populateQuestionListFromFile(questionList);

   //display welcome message
   cout<<"Welcome to The Strongest Link!"<<endl<<endl;

   //while the linked list is not empty (still has questions)
   while(!questionList.empty())
   {
      //display which question the user is on
      cout<<"Question "<<questionIndex<<":"<<endl;

      //Instantiate a new question object and initialize it as the first question in the linked list via popFront()
      Question question = questionList.popFront();

      //display the question prompt
      cout<<question.getPrompt()<<endl<<endl;

      //display each answer option for that specific question by getting the answer option by its index
      for (int index = 0; index < 4; index++)
      {
         cout<<index+1<<". "<<question.getAnswerOptionByIndex(index)<<endl;
      }

      //collect the user's answer
      cout<<endl<<"Enter answer number: ";
      cin>>userAnswer;

      //if the answer is equal to the correct answer of the specific question (retrieved via the getCorrectAnswerIndex() member function)
      if(userAnswer-1 == question.getCorrectAnswerIndex())
      {
         //display the answer is correct and increase the correct answer count
         cout<<"Correct!"<<endl<<endl;
         correctAnswerCount++;

         //if the correct answer count is greater than the strongest link amount
         if(correctAnswerCount > strongestLinkAmount)
         {
            //set the strongest link amount to the correct answer count
            strongestLinkAmount = correctAnswerCount;
         }
      }
      else
      {
         //otherwise the answer is incorrect
         cout<<"Incorrect!"<<endl<<endl;

         //set the correct answer count back to 0
         correctAnswerCount = 0;
      }
      
      //increase the question index by 1
      questionIndex++;
   }

   //at the end, display the user's strongest link amount
   cout<<"Your strongest link was "<<strongestLinkAmount<<" correctly answered question(s) in a row. Thanks for playing!"<<endl;

   //Your code here
   return 0;
}