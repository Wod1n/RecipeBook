#ifndef DAYMEALS_H
#define DAYMEALS_H

#include "recipebook.h"

class DayMeals{
private:
  int chosen_meals[3]{-1,-1,-1};
public:
  void choose_meals(RecipeBook*);
  int get_meal(int);
};

#endif
