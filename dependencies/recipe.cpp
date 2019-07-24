#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "headers/ingredient_list.h"
#include "headers/recipe.h"
/*
void Recipe::set_name(){
  std::string recipe_name = "";

  std::cout << "Please input name of recipe: ";

  std::getline(std::cin, recipe_name);

  cout << "You enterred: " << recipe_name << endl;
  name = recipe_name;

  name = "Tuna Pasta Bake";
}
*/
std::string Recipe::get_name(){
  return name;
}

IngredientList* Recipe::get_ingredients(){
  return &required_ingredients;
}
/*
void Recipe::load_ingredients(){
  std::string ingredients_list;

  std::cout << "Please input filename of ingredients: ";
  //cin >> file_name;
  ingredients_list = "ingredients.txt";
  std::cout << std::endl;

  required_ingredients = {};
  required_ingredients.import_list(ingredients_list);

}

void Recipe::load_instructions(){

  std::string instructions_list;
  std::string line{};

  std::cout << "Please input filename of instructions: ";
  //cin >> file_name;
  instructions_list = "instructions.txt";
  std::cout << std::endl;

  std::ifstream instructions_data(instructions_list);

  if(instructions_data.is_open()){
    while(getline(instructions_data, line)){
      instructions.push_back(line);
    }
    instructions_data.close();
  }
}
*/
void Recipe::show_list(){
  required_ingredients.show_ingredients();
}

void Recipe::show_instructions(){
  for(int i=0; i<instructions.size(); i++){
    std::cout << instructions.at(i) << std::endl;
  }
}

std::string Recipe::export_md(){
  std::string markdown_export{""};

  markdown_export += "##" + name + "\n";
  markdown_export += required_ingredients.table_md();
  markdown_export += "\n \n";

  for(int i=0; i<instructions.size(); i++){
    markdown_export += "1. " + instructions.at(i) + '\n';
  }

  return markdown_export;
}

std::string Recipe::export_tex(){
  std::string latex_export{""};

  latex_export += "\\section{" + name + "} \n";
  latex_export += required_ingredients.table_tex();
  latex_export += "\n";
  latex_export += "\\begin{enumerate} \n";
  for(int i=0; i<instructions.size(); i++){
    latex_export += "\\item " + instructions.at(i) + '\n';
  }

  latex_export += "\\end{enumerate} \n";

  return latex_export;
}

std::string Recipe::json_write(){

  std::string json_entry{""};

  json_entry = "\t\t\t{\t\"name\" : \"" + name + "\",\n";
  json_entry += "\t\t\t\t\"portions\" : " + std::to_string(portions) + ",\n";
  json_entry += "\t\t\t\t\"required_ingredients\" : ";
  json_entry += required_ingredients.json_write();

  json_entry += ",\n\t\t\t\t\"instructions\" : \n\"";
  for(int i=0; i<instructions.size(); i++){
    json_entry += instructions.at(i) + "\n";
  }

  json_entry += "\"";

  return json_entry;
}
/*
Recipe::Recipe(int i){

  ifstream ifs("saved_book.json");
  Json::Reader reader;
  Json::Value obj;

  reader.parse(ifs, obj);

  name = obj["RecipeBook"]["recipes"][i]["name"].asString();
  portions = obj["RecipeBook"]["recipes"][i]["portions"].asUInt();

  for(int j=0; j<obj["RecipeBook"]["recipes"][i]["required_ingredients"].size(); j++){

  }
}
*/

Recipe::Recipe(std::string input_name, int input_portions, std::string ingredients_list, std::string instructions_list){

  name = input_name;
  portions = input_portions;
  {
    std::istringstream f(instructions_list);
    std::string line{""};
    while(getline(f, line)){
      instructions.push_back(line);
    }
  }

  {
    IngredientList *new_list =  new IngredientList(ingredients_list);
    required_ingredients = *new_list;
  }

}

Recipe::Recipe(){

  {
    std::string recipe_name = "";

    std::cout << "Please input name of recipe: ";
  /*
    std::getline(std::cin, recipe_name);

    cout << "You enterred: " << recipe_name << endl;
    name = recipe_name;
    */
    name = "Tuna Pasta Bake";
  }
/*
  {
    int input_portions{0};
    std::cout << "How many people are these measurements for?" << std::endl;
    std::cin >> input_portions;
    portions = input_portions;

  }
*/
  {
    std::string ingredients_list{};

    std::cout << "Please input filename of ingredients: ";
    //cin >> ingredients_list;
    ingredients_list = "ingredients.txt";
    std::cout << std::endl;

    IngredientList *new_list = new IngredientList(ingredients_list, 1);

    required_ingredients = *new_list;
//    required_ingredients.import_list(ingredients_list);
  }

  {
    std::string instructions_list;
    std::string line{};

    std::cout << "Please input filename of instructions: ";
    //cin >> instructions_list;
    instructions_list = "instructions.txt";
    std::cout << std::endl;

    instructions = {};

    std::ifstream instructions_data(instructions_list);

    if(instructions_data.is_open()){
      while(getline(instructions_data, line)){
        instructions.push_back(line);
      }
      instructions_data.close();
    }
    else{
      throw 404;
    }
  }
}
