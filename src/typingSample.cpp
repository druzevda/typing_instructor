#include "typingSample.hxx"
#include <unordered_map>
#include <ncurses.h>
#include <chrono>

#include "config.hxx"
#include "enumCodes.hxx"

void typingSample(const std::string& text, EXITCODE_TS& exitcode, weighMaster& personMaster){
  fprintf(logfile,"in typing sample\n");
  personMaster.print();
  fflush(logfile);
  WINDOW* subwindow = newwin(
      Y_SIZE_SUBWINDOW,
      X_SIZE_SUBWINDOW,
      Y_POINT_SUBWINDOW,
      X_POINT_SUBWINDOW
  );
  if(subwindow == nullptr){
    fprintf(logfile,"dosnt open subwindow exit()\n");
    fflush(logfile);
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
    fflush(logfile);
    delwin(subwindow);
    delwin(statwindow);
    delwin(subwindow);
    endwin();
    exit(100);
  }

  int goodSym = 0;
  int allSum = 0;
  int errorsAmount = 0;

  if(has_colors()==FALSE){
    fprintf(logfile,"dosnt has_colors()  exit()\n");
    fflush(logfile);
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

  [](){
    mvwprintw(stdscr,LINES-4,X_POINT_SUBWINDOW+X_POINT_SUBWINDOW,"CTRL+P - Skip symbol");
    mvwprintw(stdscr,LINES-3,X_POINT_SUBWINDOW+X_POINT_SUBWINDOW,"CTRL+U - To menu");
    mvwprintw(stdscr,LINES-2,X_POINT_SUBWINDOW+X_POINT_SUBWINDOW,"CTRL+N - Rerun");
    mvwprintw(stdscr,LINES-1,X_POINT_SUBWINDOW+X_POINT_SUBWINDOW,"CTRL+X - randomize");
  }();
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
    const KEYS_TS curKey = KEYS_TS(c);
    if(allSum==0)
      begin = std::chrono::system_clock::now();

    if(curKey == KEYS_TS::CTRL_N ){
      fprintf(logfile,"CTRL_N, go to the next text\n");
      fflush(logfile);
      delwin(statwindow);
      delwin(subwindow);
      wclear(stdscr);

      exitcode=EXITCODE_TS::RERUN_THIS_MODE;
      return;
    }else if(curKey == KEYS_TS::CTRL_U ){
      fprintf(logfile,"CTRL_U, go to menu\n");
      fflush(logfile);
      delwin(statwindow);
      delwin(subwindow);
      wclear(stdscr);

      exitcode=EXITCODE_TS::TO_MENU;
      return;
    }
    else if(curKey == KEYS_TS::CTRL_X){
      fprintf(logfile,"CTRL_X, randomize and go to the new text\n");
      fflush(logfile);
      delwin(statwindow);
      delwin(subwindow);
      wclear(stdscr);
      personMaster.randomize();
      exitcode=EXITCODE_TS::RERUN_THIS_MODE;
      return;
    }
    if(allSum > 0 && (curKey==KEYS_TS::BACKSPACE_NORMAL || curKey==KEYS_TS::BACKSPACE_ARROWS)){ // delit
      if(allSum == goodSym)
        --goodSym;
      --allSum;
    }else if(allSum == goodSym ){ // on point
      if(c == text[goodSym] || curKey == KEYS_TS::CTRL_P){// good symbol
        ++goodSym;
      }else{//first error
        const char prevChar = allSum==0 ? ' ' : std::tolower(text[allSum-1]);
        const char nowChar = std::tolower(text[allSum]);

        const int prevIndex = symbolsMap[prevChar];
        const int nowIndex = symbolsMap[nowChar];
        personMaster.makeSample(prevIndex,nowIndex);
        ++errorsAmount;
        std::fprintf(logfile,"errNum:[%d],sample:[%d],symb:[%c][%c],idx[%d][%d]\n",errorsAmount,personMaster.getSamplesAmount(),prevChar,nowChar,prevIndex,nowIndex);
      }
      ++allSum;
    }else if (allSum >= symbolsInText){
    }else{
      ++allSum;
    }

    printStat(statwindow,"RealTimeStat",errorsAmount,goodSym);
    //wrefresh(subwindow);
  }
  fprintf(logfile,"finish texts\n");
  fflush(logfile);

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
    endwin(); exit(100);
  }

  init_pair(3,COLOR_BLACK,COLOR_WHITE);
  wbkgd(reswindow,COLOR_PAIR(3));
  printStat(reswindow,"LastFinishStat",errorsAmount,goodSym);
  delwin(reswindow);

  if(errorsAmount == 0){
    exitcode=EXITCODE_TS::ALL_GOOD_WITHOUT_ERRORS;
    fprintf(logfile,"return from typingsample() without errors!!!!!!!!\n");
  }else{
    exitcode=EXITCODE_TS::ALL_GOOD;
    fprintf(logfile,"return from typingsample()\n");
  }
}
