#include "config.hxx"
#include "menu.hxx"
int main(){
  initAll();
  if(COLS < 90 || LINES < 22){
    clear();
    printw("ERROR, WRONG SIZE OF TERMINAL, LESS THAN 90x22");
    getch();
    endwin();
    exit(1);
  }

  menu();

  endwin();
  return 0;
}
