#include "weighMaster.hxx"
#include "findBetterText.hxx"
#include <iostream>
#include "typingSample.hxx"
#include "scanTextToString.hxx"
#include "menu.hxx"
int main(){
  for(int i = 0; i < lettersAmount; ++i){
    lettersMap.insert({letters[i],i});
  }

  initscr();

  noecho();
  cbreak();
  initsizes();

  menu();

  endwin();
  return 0;
}
