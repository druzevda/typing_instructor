#ifndef MODES_HXX_INCLUDED_________________
#define MODES_HXX_INCLUDED_________________
#include <random>
void learningByErrorsTextes_mode(){
  weighMaster personMaster(lettersAmount);
  personMaster = typingSample("English texts for beginners to practice reading and comprehension online and for free.");
  while(true){
    const int betterText = findBetterText(personMaster.getWeights(),texts);
    printw("your better text = %s", texts[betterText].c_str());
    const std::string newText = scanTextToString(texts[betterText]);
    personMaster = typingSample(newText);
  }
}

void learningByErrorsWords_mode(){
  weighMaster personMaster(lettersAmount);
  personMaster = typingSample("English texts for beginners to practice reading and comprehension online and for free.");
  const std::vector<std::string> buff = scanWordsToString(wordsFile);
  while(true){
    const std::string newText = constructBetterWords(personMaster.getWeights(), buff);
    personMaster = typingSample(newText);
  }
}

void randomWord_mode(){
  std::vector<std::string> buff = scanWordsToString(wordsFile);
  std::mt19937 mersene(std::random_device{}());
  assert(buff.size() > 0);
  std::uniform_int_distribution<> unif(0,buff.size());
  while(true){
    const int wordNum = unif(mersene);
    const std::string& word = buff[wordNum];

    const std::string newText = constructTextFromWord(word);
    const auto personMaster = typingSample(newText);
  }
}

void learningByErrorsOneWord_mode(){
  weighMaster personMaster(lettersAmount);
  personMaster = typingSample("English texts for beginners to practice reading and comprehension online and for free.");
  const std::vector<std::string> buff = scanWordsToString(wordsFile);
  while(true){
    const std::string bestWord = findBetterWord(personMaster.getWeights(), buff);
    const std::string newText = constructTextFromWord(bestWord);
    personMaster = typingSample(newText);
  }
}
#endif //  MODES_HXX_INCLUDED_________________
