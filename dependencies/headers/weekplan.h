#ifndef WEEKPLAN_H
#define WEEKPLAN_H

#include "daymeals.h"
#include "ingredient_list.h"
#include "recipebook.h"

class WeekPlan{
private:
  DayMeals dayplan[7];
  IngredientList week_ingredients;
public:
  void plan_days(RecipeBook*);
  void make_list(RecipeBook*);
  IngredientList get_list();
  void display_plan();
  void export_plan();
  void update_inventory();
};

#endif
