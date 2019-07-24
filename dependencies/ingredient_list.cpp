#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "headers/ingredient_list.h"
#include "headers/ingredient.h"

IngredientList::IngredientList(){
}

IngredientList::IngredientList(std::string ingredients_list, bool add){

  std::ifstream ingredient_data(ingredients_list);

  if(ingredient_data.is_open()){
    int x{};
    std::string y{};
    while(ingredient_data >> x >> y){

      Ingredient* new_ingredient = new Ingredient(x,y);
      ingredients.push_back(*new_ingredient);
    }

    ingredient_data.close();
  }

  else{
    throw 404;
  }
}

IngredientList::IngredientList(std::string ingredients_list){

  std::istringstream f(ingredients_list);
  std::string line{""};

  int x{};
  std::string y{""};
  while(getline(f, line)){
    std::istringstream g(line);
    while(g >> x >> y){
      std::cout << x << " " << y << std::endl;
      Ingredient *new_ingredient = new Ingredient(x,y);
      ingredients.push_back(*new_ingredient);
    }
  }
}
/*
void IngredientList::import_list(std::string file_name){
  Ingredient *new_ingredient = new Ingredient;
  std::ifstream ingredient_data(file_name);

  if(ingredient_data.is_open()){
    int x{};
    std::string y{};
    while(ingredient_data >> x >> y){

      new_ingredient->add_ingredient(x,y);
      ingredients.push_back(*new_ingredient);
    }

    ingredient_data.close();
  }

  else{
    throw 404;
  }
}
*/
void IngredientList::create_inventory(){

  std::cout << "No inventory found." << std::endl;
  std::cout << "Launching inventory creater" << std::endl;

  std::cout << "Please type in current inventory in the format" << std::endl;
  std::cout << "Quantity Units Name" << std::endl;

  std::cout << "Type \"QUIT\" when finished" << std::endl;
}

void IngredientList::show_ingredients(){
  for(int i=0; i<ingredients.size(); i++){
    ingredients.at(i).show_data();
  }
}

void IngredientList::merge_lists(IngredientList *merging_list, bool increase){
  bool exists{0};
  int k{0};

  int addition = 1;

  if(increase == 0){
    addition = -1;
  }

  for(int i=0; i<merging_list->ingredients.size(); i++){
    for(int j=0; j<ingredients.size(); j++){
      if(merging_list->ingredients.at(i).get_name() == ingredients.at(j).get_name()){
        ingredients.at(j).increase_quantity(merging_list->ingredients.at(i).get_quantity(), addition);
        exists = 1;
        break;
      }
    }

    if(exists == 0){
      ingredients.push_back(merging_list->ingredients.at(i));
      exists = 0;
    }
  }

  if(!increase){
    for(int i=0; i<ingredients.size(); i++){
      if(ingredients.at(i).get_quantity() < 0){
        ingredients.erase(ingredients.begin() + i);
      }
    }
  }
}

void IngredientList::write_to_file(std::string filename = "inventory.txt"){

  std::ofstream myfile;
  myfile.open(filename);

  for(int i=0; i<ingredients.size(); i++){
    myfile << ingredients.at(i).get_name() << " " << ingredients.at(i).get_quantity() << ingredients.at(i).get_units() << std::endl;
  }

  myfile.close();
}

std::string IngredientList::table_md(){

  std::string markdown_table{"| Quantity | Ingredient |"};

  markdown_table += "\n | ----- | ----- |";

  for(int i=0; i<ingredients.size(); i++){
    markdown_table += "\n" + std::to_string(ingredients.at(i).get_quantity()) + ingredients.at(i).get_units();
    markdown_table += " | " + ingredients.at(i).get_name();
  }

  return markdown_table;

}

std::string IngredientList::table_tex(){

  std::string latex_table{"\\begin{center} \n"};
  latex_table += "\\begin{tabular}{|l|l|} \n \\hline ";
  latex_table += "Quantity & Ingredient\\\\\n\\hline";

  for(int i=0; i<ingredients.size(); i++){
    latex_table += std::to_string(ingredients.at(i).get_quantity()) + ingredients.at(i).get_units();
    latex_table += " & " + ingredients.at(i).get_name() + "\\\\ \n";
  }

  latex_table += "\\hline \n";

  latex_table += "\\end{tabular}\n\\end{center}";

  return latex_table;
}

std::string IngredientList::json_write(){

  std::string json_entry{"\n\""};

  for(int i=0; i<ingredients.size(); i++){
    json_entry += ingredients.at(i).json_write() + "\n";
  }

  json_entry += "\"";

  return json_entry;
}
