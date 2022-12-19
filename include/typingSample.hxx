#ifndef TYPING_SAMPLE_HXX_INCLUDED___
#define TYPING_SAMPLE_HXX_INCLUDED___

#include "weighMaster.hxx"
#include <ncurses.h>
weighMaster typingSample(const std::string& text){
  weighMaster result(lettersAmount);


  int goodSym = 0;
  int allSum = 0;

  if(has_colors()==FALSE){

  }else{
    start_color();
    init_pair(1,COLOR_BLACK,COLOR_RED);
    init_pair(2,COLOR_MAGENTA,COLOR_BLACK);
  }

  while( goodSym < text.size() ){
    clear();

    attron(A_BOLD | COLOR_PAIR(2));

    move(Y_SIZE_WINDOW/4,X_SIZE_WINDOW/4);

    for(int i = 0; i < goodSym;++i){
      printw("%c",text[i]);
    }
    attroff(A_BOLD | COLOR_PAIR(2));

    attron(A_REVERSE);
    attron(A_BLINK);

    attrset(COLOR_PAIR(1));
    for(int i = goodSym; i < allSum;++i){
      printw("*");
    }
    attroff(COLOR_PAIR(1));

    attroff(A_BLINK);

    for(int i = allSum; i < text.size();++i){
      printw("%c",text[i]==' ' ? '_' : text[i]);
    }
    attroff(A_REVERSE);

    char c = getch();
    if(allSum > 0 && c == 127){ // delit
      if(allSum == goodSym)
        --goodSym;
      --allSum;
    }else if(allSum == goodSym){ // on point
      if(c == text[goodSym]){// good symbol
        ++goodSym;
      }else{//first error
        const char prevChar = allSum==0 ? ' ' : text[allSum-1];
        const char nowChar = text[allSum];
        const char prevIndex = lettersMap[prevChar];
        const char nowIndex = lettersMap[nowChar];
        result.makeSample(prevIndex,nowIndex);
      }
      ++allSum;
    }else if (allSum >= text.size()){
    }else{
      ++allSum;
    }
    refresh();
  }
  result.normalize();
  return result;
}
#endif // TYPING_SAMPLE_HXX_INCLUDED___
