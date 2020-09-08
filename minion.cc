#include "minion.h"
#include "card.h"
#include "player.h"
#include <iostream>
#include <vector>
#include "ascii_graphics.h"
using namespace std;

  minion:: ~minion() {
	for(int i = 0; i < myen.size(); ++i) {
		delete myen[i];
	}
	myen.clear();
  }
  
  string minion:: getname() {return name;}

  void minion:: attack(player& target) {
    if(turn) {
        target.injure(att);
        turn = false;
  } else { throw "This minion cannot attack or use ability in this turn anymore";}
  }

  void minion:: injure(int i) {
        def -= i;
  }

  int minion:: getatt() {
      return att;
  }

  void minion:: newturn() {turn = true;}

  vector<enchantment *>& minion:: getmyen() {return myen;} 


  void minion:: attack(player& target, int i) {
  if(i <= target.getboard().size()) {
    if(turn) {
	if(name == "Water Elemental") {
		if(static_cast<minion *> (target.getboard()[i-1])->getname() == "Fire Elemental") {
			static_cast<minion *> (target.getboard()[i-1])->injure(att+1);
		        def -= static_cast<minion *> (target.getboard()[i-1])->getatt();
			turn = false;
			cout << "Critical Hit!" << endl;
		} else {
			static_cast<minion *> (target.getboard()[i-1])->injure(att);
		        def -= static_cast<minion *> (target.getboard()[i-1])->getatt();
			turn = false;
	        }
    } else if (name == "Fire Elemental") {
		if(static_cast<minion *> (target.getboard()[i-1])->getname() == "Water Elemental") {
                        static_cast<minion *> (target.getboard()[i-1])->injure(att-1);
                        def -= static_cast<minion *> (target.getboard()[i-1])->getatt();
                        turn = false;
                        cout << "Not a Good Choice!" << endl;
                } else {
                        static_cast<minion *> (target.getboard()[i-1])->injure(att);
                        def -= static_cast<minion *> (target.getboard()[i-1])->getatt();
                        turn = false;
                }
    } else {
        static_cast<minion *> (target.getboard()[i-1])->injure(att);
        def -= static_cast<minion *> (target.getboard()[i-1])->getatt();
        turn = false;
   }  
      } else { throw "This minion cannot attack or use ability in this turn anymore";}
  }  else { throw "Cannot do this";}
 }
  
  void minion:: enhance(enchantment *en) {

	
      if (en->getname() == "Giant Strength") {
          att += 2;
          def += 2;
          myen.push_back(en);
    } else if(en->getname() == "Silence") {
		useeff = false;
		myen.push_back(en);
    } else if(en->getname() == "Magic Fatigue") {
		eff_cost += 2;
		myen.push_back(en);
    } else if(en->getname() == "Fertilizer") {
		if(neweff) {
			delete neweff;
			neweff = en;
			useeff = true;
			eff_cost = 2;
			myen.push_back(en);
	     } else { 
			neweff = en;
			useeff = true;
			eff_cost = 2;
                        myen.push_back(en);
  		  }
    }	
  }
  
  void minion:: dehance() {
	enchantment* temp = myen.back();
	if (temp->getname() == "Giant Strength") {
		att -= 2;
		def -= 2;
		myen.pop_back();
		delete temp;
       } else if (temp->getname() == "Silence") {
		useeff = true;
		myen.pop_back();
		delete temp;
       } else if (temp->getname() == "Magic Fatigue") {
		eff_cost -= 2;
		myen.pop_back();
                delete temp;
       } else if (temp->getname() == "Fertilizer") {
		neweff = nullptr;
		myen.pop_back();
		eff_cost = orgeff_cost;
		for(int i = 0; i < myen.size(); ++i) {
		if(myen[i]->getname() == "Silence") {
		useeff = false;
		}
		}
                delete temp;
       }
  }
	

  int minion:: gettype() {return type;}
  
  void minion:: reset() {
	int size =  myen.size();
	for (int i = 0; i < size; ++ i) {
		dehance();
	}
	att = orgatt;
	def = orgdef;
	eff_cost = orgeff_cost;
  }
  
  bool minion:: mdead() {
	if(def < 1) {return true;}
	else return false;
  }

  void minion:: gainatt(int num) {att += num;}

vector<string> minion:: getGraphics(){
         if(name == "Air Elemental") { 
            return display_minion_no_ability(name, cost, att, def);
         }else if(name == "Earth Elemental"){
   	    return display_minion_no_ability(name, cost, att, def);
	 }else if(name == "Fire Elemental"){
	    return display_minion_triggered_ability(name,cost, att, def, desc);
	 }else if(name == "Water Elemental"){
	    return display_minion_triggered_ability(name,cost, att, def, desc);
	 }else if(name == "Treasure Finder"){
	    return display_minion_triggered_ability(name,cost, att, def, desc);
         }else if(name == "Potion Seller"){
	    return display_minion_triggered_ability(name,cost, att, def, desc);
         }else if(name == "Novice Pyromancer"){
	    return display_minion_activated_ability(name, cost, att, def, eff_cost, desc);
  	 }else if(name == "Apprentice Summoner"){
	    return display_minion_activated_ability(name, cost, att, def, eff_cost, desc);
 	 }else{
	    return display_minion_activated_ability(name, cost, att, def, eff_cost, desc);
         }
}

void minion:: display(){
 carddisplay(getGraphics());
}

int& minion::geteff_cost() {
    return eff_cost;
}

bool& minion::getuseeff() {
    return useeff;
}


void minion::use_eff(player *my, player *op) {
	string time;
    if(turn) {
	 
     if (name == "Apprentice Summoner") { 
        if (!getuseeff()) {
            throw "The ability of the selected minion can't be used";
        }
        if (my->getboard().size() < 5) {
            card* temp = new minion {"Air Elemental", 0, 1, 1, 0, false, ""};
            my->getboard().emplace_back(temp);
	    int before = my->getboard().size();
                                                  time = "my new min";
                                    my->notifyr(my, op, time);
                                        int after = my->getboard().size();
                                        if(before == after) {
                                                  time = "op new min";
                                             for(int i = 0; i < op->getboard().size(); ++i) { 
                                                        if(before == after) {
                                static_cast<minion *>(op->getboard()[i])->notifym(op, my, time);
                                                        after = my->getboard().size();
                                                        }
                                                }
                                        if (before == after) {
                                        
                                        op->notifyr(op, my, time); }}
	    turn = false;
        } else {
            throw "You already have 5 minions";
        }
    } else if (name == "Master Summoner") { 
        if (!getuseeff()) {
            throw "The ability of the selected minion can't be used";
        }
        turn = false;
        if (my->getboard().size() < 5) {
            for (int i = 0; i < 3; i++) {
                if(my->getboard().size() == 5) break;
                card* temp = new minion {"Air Elemental", 0, 1, 1, 0, false, ""};
                my->getboard().emplace_back(temp);
					int before = my->getboard().size();
                                                  time = "my new min";
                                    my->notifyr(my, op, time);
                                        int after = my->getboard().size();
                                        if(before == after) {
                                                  time = "op new min";
                                             for(int i = 0; i < op->getboard().size(); ++i) {
                                                        if(before == after) {
                                static_cast<minion *>(op->getboard()[i])->notifym(op, my, time);
                                                        after = my->getboard().size();
                                                        }
                                                }
                                        if (before == after) {

                                        op->notifyr(op, my, time); }}

            } 
        } else {
            throw "You already have 5 minions";
        }
    } else {
        throw "Invalid ability usage";
    } 
             
     } else { throw "This minion cannot attack or use ability in this turn anymore";}
}

void minion::use_eff(player *p, int t) {
     if(turn) {
	if (!neweff) {
    	if (name == "Novice Pyromancer") { 
       		 if (!getuseeff()) {
       		     throw "The ability of the selected minion can't be used";
       		   }
        static_cast<minion *>(p->getboard()[t-1])->injure(1);
        p->mdead(t-1);
        turn = false;
    } else {
        throw "Invalid ability usage";
    }
    } else {  if (!getuseeff()) {
                     throw "The ability of the selected minion can't be used";
                   }

		att +=  static_cast<minion *>(p->getboard()[t-1])->getatt();
		turn = false;
		}
   } else { throw "This minion cannot attack or use ability in this turn anymore";}
}

void minion:: notifym(player* my, player* op, string time) {
    if(getuseeff()) {
	if(!neweff) {
	if(name == "Fire Elemental" && time == "op new min") { 
		static_cast<minion *>(op->getboard().back())->injure(1);
		int index = op->getboard().size();
		op->mdead(index-1);
      } else if (name == "Potion Seller" && time == "end") { 
		for(int i = 0; i < my->getboard().size(); ++i) {
		
			 static_cast<minion *>(my->getboard()[i])->injure(-1);
		}
      } else if (name == "Treasure Finder" && time == "end") {
		for(int i = 0; i < my->gethand().size(); ++i) {
		minion* temp = dynamic_cast<minion *>(my->gethand()[i]);
		if(temp) {
			temp->gainatt(1);
			temp->injure(-1);
			}
                }
      } else if (name == "Water Elemental" && time == "end") {
		 my->injure(-1);
      }
	}
   }
}


