#ifndef MENU_HXX_INCLUDED_____
#define MENU_HXX_INCLUDED_____
#include "config.hxx"
#include <menu.h>
#include "modes.hxx"
void menu(){
  int c;
  MENU *my_menu;
  ITEM *cur_item;
  int curItem = 0;


  const uint32_t n_choices = menu_choices.size();
  ITEM **my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
  const std::string empty{""};

  for(uint32_t i = 0; i < n_choices; ++i)
    my_items[i] = new_item(menu_choices[i].c_str(), empty.c_str());
  my_items[n_choices] = (ITEM *)NULL;

  my_menu = new_menu((ITEM **)my_items);
  post_menu(my_menu);
  refresh();

  while((c = getch()) != KEY_F(1))
  {   switch(c)
    {	case 'j':
        menu_driver(my_menu, REQ_DOWN_ITEM);
        --curItem;
      break;
      case 'k':
        menu_driver(my_menu, REQ_UP_ITEM);
        ++curItem;
      break;
      case 10:
        const int res = std::abs(curItem % n_choices);
        switch(res){
          case 0:
            learningByErrorsTextes_mode();
            exit(1);
          break;
          case 1:
            exit(1);
          break;
        }
      break;
    }
  }

  free_item(my_items[0]);
  free_item(my_items[1]);
  free_menu(my_menu);
}
#endif // MENU_HXX_INCLUDED_____
