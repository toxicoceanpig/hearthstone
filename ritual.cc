#include <iostream>
#include "ritual.h"
#include "player.h"
#include "minion.h"
#include <string>
#include <vector>
#include "ascii_graphics.h"
using namespace std;
int ritual:: gettype() {return type;}

void ritual:: getcharge(int i) {charge += i;}

void ritual:: notify(player* my, player* op, string command) {
      if(name == "Dark Ritual") {  
           if(command == "start") {
                if(charge >= chargecost){
                    my->changemagic(1);
                    charge -= chargecost;
                  }
           }
  } else if(name == "Aura of Power") {
           if(command == "my new min") {
                  if(charge >= chargecost){
                          static_cast<minion *>(my->getboard().back())->gainatt(1);
                         
                          static_cast<minion *>(my->getboard().back())->injure(-1);
                          charge -= chargecost;
                    }
           }
  } else if(name == "Standstill") { 
           if(command == "my new min") {
                  if(charge >= chargecost){
                            static_cast<minion *>(my->getboard().back())->reset();
                          card* temp = my->getboard().back();
                            my->getboard().pop_back();
                            my->getgyard().push_back(temp);
                            charge -= chargecost;
                          }
        } else if (command == "op new min") {
                  if(charge >= chargecost){
                            static_cast<minion *>(op->getboard().back())->reset();
                            card* temp = op->getboard().back();
                            op->getboard().pop_back();
                            op->getgyard().push_back(temp);
                            charge -= chargecost;
                          }
        }            
  } else if(name == "Explosive Trap") {
		if(command == "my hero has been attacked") {
		   if(charge >= chargecost){ 
			int size = op->getboard().size();
			    for(int i = 0; i < op->getboard().size(); ++i) {
				static_cast<minion *>(op->getboard()[i])->injure(2);
				}
			    for(int i = 0; i < size; ++i) {
				if(static_cast<minion *>(op->getboard()[i])->mdead()) {
					op->mdead(i);
					i -= 1;
				} 
			    }
				op->injure(2);
				charge -= chargecost;
 			 }
        }
  }
}


vector<string> ritual:: getGraphics(){
  return display_ritual(name,cost, chargecost, desc,charge);
}

void ritual:: display(){
  carddisplay(getGraphics());
}
