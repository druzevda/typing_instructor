#include "weighMaster.hxx"
#include "findBetterText.hxx"
#include <iostream>
#include "typingSample.hxx"
#include "scanTextToString.hxx"
int main(){
  for(int i = 0; i < lettersAmount; ++i){
    lettersMap.insert({letters[i],i});
  }
  weighMaster personMaster(lettersAmount);

  initscr();
  initsizes();

  personMaster = typingSample("English texts for beginners to practice reading and comprehension online and for free.");
  while(true){
    const int betterText = findBetterText(personMaster.getWeights());
    printw("your better text = %s", texts[betterText].c_str());
    const std::string newText = scanTextToString(betterText);
    personMaster = typingSample(newText);
  }

  endwin();
  return 0;
}
