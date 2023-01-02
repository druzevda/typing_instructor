#ifndef MODES_HXX_INCLUDED_________________
#define MODES_HXX_INCLUDED_________________
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
  while(true){
    const int betterText = findBetterText(personMaster.getWeights(),words);
    printw("your better text = %s", words[betterText].c_str());
    const std::string newText = scanTextToString(words[betterText]);
    personMaster = typingSample(newText);
  }
}
#endif //  MODES_HXX_INCLUDED_________________
