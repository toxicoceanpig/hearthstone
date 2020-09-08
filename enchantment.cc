#include "enchantment.h"
#include <iostream>
#include <string>
#include <vector>
#include "ascii_graphics.h"
using namespace std;

 enchantment::enchantment(std::string name,int cost, string desc): type{4}, name{name}, card{cost},cost{cost}, desc{desc} {}
  
string enchantment::getname() {return name;}

int enchantment::gettype() {return type;}
  
vector<string> enchantment::getGraphics() {
 if(name == "Giant Strength"){
   return display_enchantment_attack_defence(name, cost, desc, "+2", "+2");
 }else if(name == "Magic Fatigue"){
   return display_enchantment(name, cost, desc);
 }else{
   return display_enchantment(name, cost, desc);
 }
}

void enchantment:: display(){
 carddisplay(getGraphics());
}
