#ifndef TYPING_SAMPLE_HXX_INCLUDED___
#define TYPING_SAMPLE_HXX_INCLUDED___

#include "weighMaster.hxx"
#include <ncurses.h>
#include <chrono>

weighMaster typingSample(const std::string& text){
  fprintf(logfile,"in typing sample\n");
  weighMaster result(symbolsAmount);
  WINDOW* subwindow = newwin(
      Y_SIZE_SUBWINDOW,
      X_SIZE_SUBWINDOW,
      Y_POINT_SUBWINDOW,
      X_POINT_SUBWINDOW
  );
  if(subwindow == nullptr){
    fprintf(logfile,"dosnt open subwindow exit()\n");
    delwin(subwindow);
    endwin();
    exit(100);
  }

  WINDOW* statwindow = newwin(
      4,
      X_POINT_SUBWINDOW,
      LINES-4,
      0
  );

  if(statwindow == nullptr){
    fprintf(logfile,"dosnt open statwindow exit()\n");
    delwin(subwindow);
    delwin(statwindow);
    delwin(subwindow);
    endwin();
    exit(100);
  }

  int goodSym = 0;
  int allSum = 0;

  if(has_colors()==FALSE){
    fprintf(logfile,"dosnt has_colors()  exit()\n");
    delwin(subwindow);
    endwin();
    exit(100);
  }else{
    start_color();
    init_pair(1,COLOR_BLACK,COLOR_RED);
    init_pair(2,COLOR_MAGENTA,COLOR_BLACK);
  }

  move(Y_POINT_SUBWINDOW-1,X_POINT_SUBWINDOW-1);
  hline(0,X_SIZE_SUBWINDOW+1);
  vline(0,Y_SIZE_SUBWINDOW+2);
  move(Y_POINT_SUBWINDOW+Y_SIZE_SUBWINDOW,X_POINT_SUBWINDOW);
  hline(0,X_SIZE_SUBWINDOW);
  move(Y_POINT_SUBWINDOW-1,X_POINT_SUBWINDOW+X_SIZE_SUBWINDOW);
  vline(0,Y_SIZE_SUBWINDOW+2);


  wrefresh(stdscr);

  const int symbolsInText = text.size();

  auto begin = std::chrono::system_clock::now();

  auto printStat=[&begin](WINDOW* curWin,const std::string& header,const int errorsAmount,const int goodSymbols){
    wclear(curWin);
    const double errorsProc = goodSymbols==0 ? 0.0 : double(errorsAmount)/goodSymbols * 100.0;

    const auto end = std::chrono::system_clock::now();
    const std::chrono::duration<double> elapsed_seconds = end - begin;
    const double seconds = elapsed_seconds.count();

    const double symbPerSec = goodSymbols/seconds;
    const double symbPerMin = symbPerSec*60;

    wmove(curWin,0,0);
    wprintw(curWin,header.c_str());

    wmove(curWin,1,0);
    wprintw(curWin,"Errors = %d, %.1lf%%",errorsAmount,errorsProc);

    wmove(curWin,2,0);
    wprintw(curWin,"symbPerSec = %.1lf",symbPerSec);

    wmove(curWin,3,0);
    wprintw(curWin,"symbPerMin = %.1lf",symbPerMin);

    wrefresh(curWin);
  };

  printStat(statwindow,"PleaseStartTyping",0,0);

  const auto printText = [&subwindow,&text,&goodSym,&allSum,symbolsInText](){
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
    for(int i = allSum; i < symbolsInText;++i){
      wprintw(subwindow,"%c",text[i]==' ' ? '_' : text[i]);
    }
    wattroff(subwindow,A_REVERSE);

    wrefresh(subwindow);
  };

  while( goodSym < symbolsInText){
    printText();

    const char c = getch();
    if(allSum==0)
      begin = std::chrono::system_clock::now();

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
        const char prevIndex = symbolsMap[prevChar];
        const char nowIndex = symbolsMap[nowChar];
        result.makeSample(prevIndex,nowIndex);
      }
      ++allSum;
    }else if (allSum >= symbolsInText){
    }else{
      ++allSum;
    }

    printStat(statwindow,"RealTimeStat",result.getSamplesAmount(),goodSym);
    //wrefresh(subwindow);
  }
  fprintf(logfile,"finish texts\n");
  result.normalize();

  delwin(statwindow);
  delwin(subwindow);

  WINDOW* reswindow = newwin(
      4,
      X_POINT_SUBWINDOW,
      LINES-4,
      X_POINT_SUBWINDOW
  );
  if(reswindow == nullptr){
    fprintf(logfile,"dosnt open reswindow exit()\n");
    endwin();
    exit(100);
  }

  init_pair(3,COLOR_BLACK,COLOR_WHITE);
  wbkgd(reswindow,COLOR_PAIR(3));
  printStat(reswindow,"LastFinishStat",result.getSamplesAmount(),goodSym);
  delwin(reswindow);

  fprintf(logfile,"return from typingsample()\n");
  return result;
}
#endif // TYPING_SAMPLE_HXX_INCLUDED___
