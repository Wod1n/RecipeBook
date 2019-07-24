#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <iostream>
#include <string>

class Ingredient{
private:
  int quantity;
  std::string name;
  std::string units{'g'};
public:
  void add_ingredient(int, std::string);
  void show_data();
  void increase_quantity(int, int);
  int get_quantity();
  std::string get_units();
  std::string get_name();
  std::string json_write();

  Ingredient(int, std::string);
};

#endif
