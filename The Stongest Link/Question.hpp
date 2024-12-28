#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <string>
#include <array>
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

#endif