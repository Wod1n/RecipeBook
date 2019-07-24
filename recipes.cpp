//RecipeBook Project Main File

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <jsoncpp/json/json.h>
#include "dependencies/headers/ingredient.h"
#include "dependencies/headers/ingredient_list.h"
#include "dependencies/headers/recipe.h"
#include "dependencies/headers/recipebook.h"
#include "dependencies/headers/daymeals.h"
#include "dependencies/headers/weekplan.h"

using namespace std;

bool export_menu(RecipeBook *master_book){
  int selection{1};

  cout << "Would you like to export as:" << endl;
  string options[3] = {"Markdown", "LaTeX","Plain Text"};
  for(int i=0; i<3; i++){
    cout << i+1 << ". " << options[i] << endl;
  }

  cout << "0. Do not export" << endl;

  cin >> selection;

  switch(selection){
    case 1:{
      master_book->export_md();
      return 1;}
    case 2:{
      master_book->export_tex();
      return 1;}
    case 3:{
      cout << "Plaintext? Are you a Savage?" << endl;
      return 1;}

    case 0:{
      return 1;
    }

    default: {
      return 0;
    }
  }
}

bool main_menu(RecipeBook *master_book){

  int selection{0};

  cout << "1. Display current recipe names" << endl;
  cout << "2. Add new recipes" << endl;
  cout << "3. Edit existing recipes" << endl;
  cout << "4. Build weekly plan" << endl;
  cout << "5. Update inventory" << endl;
  cout << "6. Export shopping list" << endl;
  cout << "7. Export recipe book" << endl;
  cout << "0. Quit" << endl;

  cin >> selection;
  cin.ignore();

  switch(selection){
    case 1:{
      cout << "Case 1" << endl;
      master_book->display_names();
      break;
    }

    case 2:{
      cout << "Case 2" << endl;
      master_book->add_new();
      break;
    }

    case 4:{
      cout << "Case 4" << endl;
      master_book->display_recipes();
    }

    case 5:{
      cout << "Case 5" << endl;

    }

    case 7:{
      while(!export_menu(master_book));
      break;
    }

    case 0:{
      return 0;
    }

    default:{
      cerr << "Error: Invalid Selection";
    }
  }
  char response{};
  cout << "Would you like another function? Y/N" << endl;
  cin >> response;
  if(response == 'Y' || response == 'y'){
    return 1;
  }

  else{
    return 0;}
}

IngredientList* startup(){

  std::string ingredient_list = "inventory.txt";
  IngredientList *inventory = new IngredientList(ingredient_list, 1);

  return inventory;
}

int main(){

  //int selection = main_menu();
  IngredientList *shopping_list = new IngredientList;
  RecipeBook *master_book = new RecipeBook;

  IngredientList* inventory = startup();

  master_book->display_recipes();

  while(main_menu(master_book));
/*
  master_book->add_new();
  master_book->display_names();
*/
  delete master_book;

//  master_book->json_write();
/*
  WeekPlan *this_week = new WeekPlan;

  this_week->plan_days(master_book);

  this_week->make_list(master_book);

  cout << "Back in main" << endl;

  *shopping_list = this_week->get_list();
  shopping_list->merge_lists(inventory, 0);

  shopping_list->show_ingredients();
/*
  int search{-1};
  while(search == -1){
    int search = master_book->search_recipes();
    cout << search << endl;
    if(search != -1){
      break;
    }
  }
  */
  //while(!export_menu(master_book));

  //master_book.display_recipes();

}
