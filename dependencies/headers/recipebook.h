#ifndef RECIPEBOOK_H
#define RECIPEBOOK_H

#include <string>
#include <vector>
#include "recipe.h"

class RecipeBook{
private:
  std::vector<Recipe> recipes;
  std::string name{"User's Recipe Book"};
  std::string author{"Morgan Colbeck"};

public:
  void add_new();
  void set_book_name();
  void set_author();
  void display_recipes();
  int search_recipes();
  Recipe get_recipe(int i);
  void display_names();
  void save_json();
  void export_md();
  void export_tex();
  void json_write();

  RecipeBook();
  ~RecipeBook();
};

#endif
