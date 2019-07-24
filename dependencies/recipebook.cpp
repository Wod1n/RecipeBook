#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <jsoncpp/json/json.h>
#include "headers/ingredient_list.h"
#include "headers/recipe.h"
#include "headers/recipebook.h"

void RecipeBook::add_new(){
  bool repeat{1};
  while(repeat){
    bool correct{0};
    while(!correct){
      try{
        Recipe *new_recipe = new Recipe();
        std::cout << "\n";
        std::cout << "This is how the card will be stored: " << std::endl;

        std::cout << new_recipe->get_name() << std::endl;
        new_recipe->show_list();
        new_recipe->show_instructions();
        char response{};
        std::cout << "Is this correct? Y/N \n";
        std::cin >> response;
        std::cin.ignore();

        if(response == 'Y' or response == 'y'){
          correct = 1;
          recipes.push_back(*new_recipe);
        }
      }

      catch(int x){
        std::cerr << "Error " << x << ": File not found" << std::endl;
      }
    }
    char response;
    std::cout << "Would you like to input another? Y/N \n";
    std::cin >> response;
    std::cin.ignore();

    if(response == 'N' or response == 'n'){
      repeat = 0;
    }
  }

}

void RecipeBook::set_book_name(){
  std::string input_name{};

  bool repeat{1};

  while(repeat){
    char response{};
    std::cout << "Please type desired name for Recipe Book" << std::endl;
    std::getline(std::cin, input_name);
    std::cin.ignore();
    std::cout << "You enterred: " << input_name << std::endl;
    std::cout << "Is this correct? Y/N" << std::endl;
    std::cin >> response;
    std::cin.ignore();

    if(response == 'Y' || response == 'y'){
      repeat = 0;
    }
  }

  name = input_name;
}

void RecipeBook::set_author(){
  std::string input_name{};

  bool repeat{1};

  while(repeat){
    char response{};
    std::cout << "Please type desired name for Author" << std::endl;
    std::getline(std::cin, input_name);
    std::cin.ignore();
    std::cout << "You enterred: " << input_name << std::endl;
    std::cout << "Is this correct? Y/N" << std::endl;
    std::cin >> response;
    std::cin.ignore();

    if(response == 'Y' || response == 'y'){
      repeat = 0;
    }
  }

  author = input_name;
}

void RecipeBook::display_recipes(){

  for(int i=0; i<recipes.size(); i++){
    std::cout << recipes.at(i).get_name() << std::endl;
    std::cout << "Ingredients: " << std::endl;
    recipes.at(i).show_list();
    std::cout << "Instructions" << std::endl;
    recipes.at(i).show_instructions();
  }
}

void RecipeBook::display_names(){
  for(int i=0; i<recipes.size(); i++){
    std::cout << i+1 << ". ";
    std::cout << recipes.at(i).get_name() << std::endl;
  }
}

int RecipeBook::search_recipes(){

  std::string search_name{};
  std::cout << "Please input recipe name" << std::endl;
  std::getline(std::cin, search_name);

  std::vector<std::string> possible_hits{};
  std::vector<int> list_numbers{};

  for (int i=0; i<recipes.size(); i++){
    if(recipes.at(i).get_name() == search_name){
      possible_hits.push_back(recipes.at(i).get_name());
      list_numbers.push_back(i);
    }
  }

  if(possible_hits.size() == 0){
    std::cout << "Sorry, no hits found. Please check spelling and try again." << std::endl;
    return -1;
  }

  else if(possible_hits.size() == 1){
    char response{};
    std::cout << "One hit found!" << std::endl;
    std::cout << possible_hits.at(0) << std::endl;

    std::cout << "Is this what you were looking for? Y/N" << std::endl;
    std::cin >> response;

    if(response == 'Y' || response == 'y'){
      return list_numbers.at(0);
    }

    else{
      return -1;
    }
  }

  else{
    std::cout << "Multiple hits found. Please make a selection" << std::endl;
    for(int i=0; i<possible_hits.size(); i++){
      std::cout << i+1 << ". " << possible_hits.at(i) << std::endl;
    }

    int selection{};
    std::cin >> selection;
    std::cin.ignore();
    selection--;

    return list_numbers.at(selection);
  }
}

Recipe RecipeBook::get_recipe(int i){
  return recipes.at(i);
}

void RecipeBook::export_md(){
  std::ofstream myfile;

  myfile.open("New Book.md");
  myfile << '#' << name << "\n";

  for(int i=0; i<recipes.size(); i++){
    myfile << recipes.at(i).export_md();
  }

  myfile.close();
}

void RecipeBook::export_tex(){
  std::ofstream myfile;

  myfile.open("New Book.tex");
  myfile << "\\documentclass[a4paper,10pt]{article} \n";
  myfile << "\\usepackage[utf8]{inputenc} \n";
  myfile << "\\title{" << name << "} \n";
  myfile << "\\author{" << author << "} \n";
  myfile << "\\begin{document} \n";
  myfile << "\\maketitle \n";
  myfile << "\\newpage \n\\tableofcontents \n\\newpage\n";

  for(int i=0; i<recipes.size(); i++){
    myfile << recipes.at(i).export_tex();
  }

  myfile << "\\end{document}";
}
/*
void RecipeBook::json_write(){

  std::ofstream myfile;

  myfile.open("saved_book.json");

  if(myfile.is_open()){

    myfile << "{" << "\n";
    myfile << "\t \"RecipeBook\": { \n \t \t \"name\" : \"" << name << "\",\n";
    myfile << "\t \t \"author\" : \"" << author << "\",\n";
    myfile << "\t \t \"recipes\" : [\n";

    for(int i=0; i<recipes.size(); i++){
      myfile << recipes.at(i).json_write();
      myfile << "\n\t\t\t}";

      if(i+1 != recipes.size()){
        myfile << ",\n";
      }
    }

    myfile << "\n\t\t]\n";
    myfile << "\t}\n";
    myfile << "}";

    myfile.close();
  }
}
*/

RecipeBook::RecipeBook(){

  std::ofstream saved_book;
  saved_book.open("saved_book.json", std::ios::in);

  if(saved_book.is_open()){
    std::ifstream ifs("saved_book.json");
    Json::Reader reader;
    Json::Value obj;

    reader.parse(ifs, obj);

    name = obj["RecipeBook"]["name"].asString();
    author = obj["RecipeBook"]["author"].asString();

    for(int i=0; i<obj["RecipeBook"]["recipes"].size(); i++){
      std::string new_name = obj["RecipeBook"]["recipes"][i]["name"].asString();
      int new_portions = obj["RecipeBook"]["recipes"][i]["portions"].asUInt();
      std::string new_ingredients = obj["RecipeBook"]["recipes"][i]["required_ingredients"].asString();
      std::string new_instructions = obj["RecipeBook"]["recipes"][i]["instructions"].asString();

      Recipe *new_recipe = new Recipe(new_name, new_portions, new_ingredients, new_instructions);
      recipes.push_back(*new_recipe);
    }
  }

  else{
    std::cout << "No saved book found" << std::endl;
    std::cout << "Creating new book" << std::endl;

    std::ofstream new_book("saved_book.json");
    new_book.close();
  }
}


RecipeBook::~RecipeBook(){

  std::ofstream myfile;
  myfile.open("saved_book.json");

  if(myfile.is_open()){

    myfile << "{" << "\n";
    myfile << "\t\"RecipeBook\": {\n\t\t\"name\" : \"" << name << "\",\n";
    myfile << "\t\t\"author\" : \"" << author << "\",\n";
    myfile << "\t\t\"recipes\" : [\n";

    for(int i=0; i<recipes.size(); i++){
      myfile << recipes.at(i).json_write();
      myfile << "\n\t\t\t}";

      if(i+1 != recipes.size()){
        myfile << ",\n";
      }
    }

    myfile << "\n\t\t]\n";
    myfile << "\t}\n";
    myfile << "}";

    myfile.close();
  }
}
