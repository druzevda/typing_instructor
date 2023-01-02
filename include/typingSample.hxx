#ifndef TYPING_SAMPLE_HXX_INCLUDED___
#define TYPING_SAMPLE_HXX_INCLUDED___

#include "weighMaster.hxx"
#include <ncurses.h>

weighMaster typingSample(const std::string& text){
  weighMaster result(lettersAmount);
  WINDOW* subwindow = newwin(Y_SIZE_SUBWINDOW,X_SIZE_SUBWINDOW,Y_POINT_SUBWINDOW,X_POINT_SUBWINDOW);
  if(subwindow == nullptr){
    std::cerr << "error, dos not open subwindow"<< std::endl;
    delwin(subwindow);
    endwin();
    exit(100);
  }
  int goodSym = 0;
  int allSum = 0;

  //wclear(stdscr);
  wrefresh(stdscr);

  if(has_colors()==FALSE){
    std::cerr << "error, dos not init colors "<< std::endl;
    delwin(subwindow);
    endwin();
    exit(100);
  }else{
    start_color();
    init_pair(1,COLOR_BLACK,COLOR_RED);
    init_pair(2,COLOR_MAGENTA,COLOR_BLACK);
  }
  while( goodSym < text.size() ){
    wclear(subwindow);

    wattron(subwindow,A_BOLD | COLOR_PAIR(2));

    for(int i = 0; i < goodSym;++i){
      wprintw(subwindow,"%c",text[i]);
    }
    wattroff(subwindow,A_BOLD | COLOR_PAIR(2));

    wattron(subwindow,A_REVERSE);
    wattron(subwindow,A_BLINK);

    wattrset(subwindow,COLOR_PAIR(1));
    for(int i = goodSym; i < allSum;++i){
      wprintw(subwindow,"*");
    }
    wattroff(subwindow,COLOR_PAIR(1));

    wattroff(subwindow,A_BLINK);

    for(int i = allSum; i < text.size();++i){
      wprintw(subwindow,"%c",text[i]==' ' ? '_' : text[i]);
    }
    wattroff(subwindow,A_REVERSE);
    wrefresh(subwindow);

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
    wrefresh(subwindow);
  }
  result.normalize();
  delwin(subwindow);
  return result;
}
#endif // TYPING_SAMPLE_HXX_INCLUDED___
