#include <iostream>
#include "headers/daymeals.h"
#include "headers/recipebook.h"

void DayMeals::choose_meals(RecipeBook *master_book){

  bool repeat{1};
  while(repeat){
    int search_result{-1};
    while((search_result = master_book->search_recipes()) == -1);

    char meal;
    std::cout << "Which meal would you like this to be for? B/L/D" << std::endl;
    std::cin >> meal;
    std::cin.ignore();

    if(meal == 'B' || meal == 'b'){
      chosen_meals[0] = search_result;
    }

    else if(meal == 'L' || meal == 'l'){
      chosen_meals[1] = search_result;
    }

    else if(meal == 'D' || meal == 'd'){
      chosen_meals[2] = search_result;
    }

    else{
      throw 403;
    }

    char selection{};
    std::cout << "Would you like to select another? Y/N" << std::endl;
    std::cin >> selection;
    std::cin.ignore();

    if(selection == 'Y' || selection == 'y'){
      repeat = 1;
    }

    else{
      repeat = 0;
    }
  }
}

int DayMeals::get_meal(int j){
  return chosen_meals[j];
}
