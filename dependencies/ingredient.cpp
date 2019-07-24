#include "headers/ingredient.h"
#include <string>
#include <iostream>

Ingredient::Ingredient(int x, std::string y){
  quantity = x;
  name = y;
}

void Ingredient::add_ingredient(int x, std::string y){
  quantity = x;
  name = y;
}

void Ingredient::increase_quantity(int x, int addition){
  quantity += x*addition;

  if(quantity == 0){
    if(addition == -1){
      quantity = -1;
    }
  }
}

void Ingredient::show_data(){

  if(quantity == 0){
    std::cout << "A pinch of " << name << std::endl;
  }

  else{
    std::cout << quantity;
    std::cout << units << ' ';
    std::cout << name << std::endl;
  }
}

int Ingredient::get_quantity(){
  return quantity;
}

std::string Ingredient::get_units(){
  return units;
}

std::string Ingredient::get_name(){
  return name;
}

std::string Ingredient::json_write(){
  std::string json_entry{""};

  json_entry += std::to_string(quantity) + " " + name;

  return json_entry;
}
