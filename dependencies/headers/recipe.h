#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <vector>
#include "ingredient_list.h"

class Recipe{
private:
  IngredientList required_ingredients;
  std::vector<std::string> instructions;
  std::string name;
  int portions{0};
public:
  void set_name();
  std::string get_name();
  IngredientList *get_ingredients();
  void load_ingredients();
  void load_instructions();
  void show_list();
  void show_instructions();
  std::string export_md();
  std::string export_tex();
  std::string json_write();

  Recipe();
  Recipe(std::string, int, std::string, std::string);
};

#endif
