#include <iostream>
#include "headers/weekplan.h"
#include "headers/daymeals.h"
#include "headers/recipebook.h"
#include "headers/ingredient_list.h"

void WeekPlan::plan_days(RecipeBook *master_book){
  bool repeat{1};

  while(repeat){
    int selection{-1};
    std::cout << "Which day number would you like to plan? 0-6" << std::endl;
    std::cin >> selection;
    std::cin.ignore();

    if(selection >= 0 && selection <=6){
      dayplan[selection].choose_meals(master_book);

      char choice{};
      std::cout << "Would you like to edit another? Y/N" << std::endl;
      std::cin >> choice;
      std::cin.ignore();

      if(choice == 'Y' || choice == 'y'){
        repeat = 1;
      }

      else{
        repeat = 0;
      }
    }

    else{
      std::cerr << "Error: Invalid selection." << std::endl;
      std::cout << "Please try again" << std::endl;
    }
  }

  for(int i=0; i<7; i++){
    for(int j=0; j<3; j++){
      std::cout << dayplan[i].get_meal(j) << " ";
    }

    std::cout << std::endl;
  }
}

void WeekPlan::make_list(RecipeBook *master_book){

  for(int i=0; i<6; i++){
    for(int j=0; j<3; j++){
      if(dayplan[i].get_meal(j) == -1){
        std::cout << "";
      }

      else{
        week_ingredients.merge_lists(master_book->get_recipe(dayplan[i].get_meal(j)).get_ingredients());
      }
    }
  }

  week_ingredients.show_ingredients();
}

IngredientList WeekPlan::get_list(){
  return week_ingredients;
}
