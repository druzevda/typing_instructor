#ifndef MENU_HXX_INCLUDED_____
#define MENU_HXX_INCLUDED_____
#include "config.hxx"
#include <cassert>
#include <menu.h>
#include "modes.hxx"

void learningByErrorsTextes_mode();
void learningByErrorsWords_mode();

void menu(){
  int c;
  MENU *my_menu;
  int curItem = 0;

  assert(menu_choices.size()==menu_descriptions.size());

  const uint32_t n_choices = menu_choices.size();
  ITEM **my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

  for(uint32_t i = 0; i < n_choices; ++i)
    my_items[i] = new_item(menu_choices[i].c_str(), menu_descriptions[i].c_str());
  my_items[n_choices] = (ITEM *)NULL;

  set_item_userptr(my_items[0],(void*)learningByErrorsTextes_mode);
  set_item_userptr(my_items[1],(void*)learningByErrorsWords_mode);
  //set_item_userptr(my_items[1],(void*)learningByErrorsWords_mode);

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
        ITEM * cur_item = current_item(my_menu);
        void (*mode)() = (void(*)())item_userptr(cur_item);
        mode();
      break;
    }
  }

  free_item(my_items[0]);
  free_item(my_items[1]);
  free_menu(my_menu);
}
#endif // MENU_HXX_INCLUDED_____
