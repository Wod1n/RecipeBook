#ifndef INGREDIENT_LIST_H
#define INGREDIENT_LIST_H

#include <string>
#include <vector>
#include "ingredient.h"

class IngredientList{
private:
  std::vector<Ingredient> ingredients{};

public:
  void import_list(std::string file_name);
  void create_inventory();
  void merge_lists(IngredientList*, bool = 1);
  void write_to_file(std::string);
  void show_ingredients();
  std::string table_md();
  std::string table_tex();
  std::string json_write();

  IngredientList();
  IngredientList(std::string);
  IngredientList(std::string, bool);
};

#endif
