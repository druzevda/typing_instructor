#include "menu.hxx"
#include <menu.h>
#include <ncurses.h>
#include <cassert>
#include <string>
#include <vector>

extern const std::vector<std::string> menu_choices;
extern const std::vector<std::string> menu_descriptions;

void learningByErrorsTextes_mode();
void randomText_mode();
void learningByErrorsWords_mode();
void randomWords_mode();
void learningByErrorsOneWord_mode();
void randomWord_mode();
void randomLetters_mode();

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
  set_item_userptr(my_items[1],(void*)randomText_mode);
  set_item_userptr(my_items[2],(void*)learningByErrorsWords_mode);
  set_item_userptr(my_items[3],(void*)randomWords_mode);
  set_item_userptr(my_items[4],(void*)learningByErrorsOneWord_mode);
  set_item_userptr(my_items[5],(void*)randomWord_mode);
  set_item_userptr(my_items[6],(void*)randomLetters_mode);

  my_menu = new_menu((ITEM **)my_items);
  post_menu(my_menu);

  while((c = getch()) != KEY_F(1))
  {
    switch(c)
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

        menu_driver(my_menu, REQ_DOWN_ITEM);
        --curItem;
      break;
    }
  }

  free_item(my_items[0]);
  free_item(my_items[1]);
  free_item(my_items[2]);
  free_item(my_items[3]);
  free_item(my_items[4]);
  free_item(my_items[5]);
  free_item(my_items[6]);
  free_menu(my_menu);
}
