#include <iostream>
#include <string>
#include <vector>
#include "spell.h"
#include "player.h"
#include "card.h"
#include "minion.h"
#include "ascii_graphics.h"
#include <algorithm>
using namespace std;

int spell:: gettype() {return type;}

string spell:: getname() {return name;}

void spell:: playspell(player* my, player* op) {
string time;
	if(name == "Recharge"){  
				if (my->getmyri()){
		        my->getmyri()->getcharge(3);
		    } else {
		        throw "Cannot play selected card: Ritual slot is empty.";
		    }


   } else if (name == "Raise Dead") {
		 
		if( !my->getgyard().empty() ) {
        if( my->getboard().size() < 5) {
            card* temp = my->getgyard().back();
            my->getgyard().pop_back();
            my->getboard().push_back(temp);
	    					
                                            int before = my->getboard().size();        // check the number of minion, in order to stop notify
                                                  time = "my new min";
             					 my->notifyr(my, op, time);
                                            int after = my->getboard().size();
                    // notify opponent's minions and ritual
                                        if(before == after) {
                                                  time = "op new min";
                                            for(int i = 0; i < op->getboard().size(); ++i) {
                                                        if(before == after) {
                                            static_cast<minion *>(op->getboard()[i])->notifym(op, my, time);
                                                        after = op->getboard().size();
                                                                             }
                                                  }
                                        if (before == after) {
                                        op->notifyr(op, my, time); }}
	
        } else {
            throw "Cannot play selected card: Minions slot is full";
        }
    } else {
        throw "Cannot play selected card: Graveyard is empty";
    }


  } else if (name == "Blizzard") {
		
		for(int i = 0; i < my->getboard().size(); ++i) {
			static_cast<minion *>(my->getboard()[i])->injure(2);
		}
		int size1 = my->getboard().size();
		for(int i = 0; i < size1; ++i) {
                                if(static_cast<minion *>(my->getboard()[i])->mdead()) {
                                        my->mdead(i);
                                        i -= 1;
                                }
                            }

		for(int i = 0; i < op->getboard().size(); ++i) {
                        static_cast<minion *>(op->getboard()[i])->injure(2);
                }
		int size = op->getboard().size();
		for(int i = 0; i < size; ++i) {
                                if(static_cast<minion *>(op->getboard()[i])->mdead()) {
                                        op->mdead(i);
                                        i -= 1;
                                }
                            }

  } else if (name == "Surprise") {
		card* temp = new spell {"Bomb" , 0, "Deal 5 damage to yourself"};
		op->getdeck().push_back(temp);
		random_shuffle(op->getdeck().begin(), op->getdeck().end());
                
  }
}

void spell:: playspell(player* tp, int t) {
	if (name == "Banish") { 
				if(t == 6) {
					 tp->deletemyri();
				} else {
					static_cast<minion *>(tp->getboard()[t-1])->injure(99999999);
					tp->mdead(t-1);
				}
   } else if (name == "Unsummon") {
	
				static_cast<minion *>(tp->getboard()[t-1])->reset();
				card* temp = tp->getboard()[t-1];
				tp->getboard().erase(tp->getboard().begin() + t-1);
				tp->getdeck().push_back(temp);

   } else if (name == "Disenchant") {  
			 	static_cast<minion *>(tp->getboard()[t-1])->dehance();
				tp->mdead(t-1);;
				}
}

vector<string> spell:: getGraphics(){
   return display_spell(this->name, this->cost, this->desc);
}

void spell:: display(){
 carddisplay(getGraphics());;
}	
