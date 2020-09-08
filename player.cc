#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "player.h"
#include "card.h"
#include "minion.h"
#include "enchantment.h"
#include "ritual.h"
#include "ascii_graphics.h"
#include "spell.h"
#include <exception>
//#include "window.h"
using namespace std;

string player:: getname() {return name;}


player:: ~player() {
	delete myri;
	for(int i = 0; i < deck.size(); ++i) {
		delete deck[i];
		deck.clear();
	}
	for(int i = 0; i < hand.size(); ++i) {
                delete hand[i];
		hand.clear();
        }
        for(int i = 0; i < gyard.size(); ++i) {
                delete gyard[i];
		gyard.clear();
        }
        for(int i = 0; i < board.size(); ++i) {
                delete board[i];
		board.clear();
        }
}


bool player:: dead() {
	if (HP < 1) {return true;}
	else {return false;}
}

void player::display_player(vector<string> v){
 int len = v.size();
 for(int m = 0; m < len; ++m){
    cout << v[m] << endl;
 }
}

void player:: draw() {
    if (hand.size() < 5 && deck.size() >= 1) {
                  card* temp = deck[0];
                  deck.erase(deck.begin());
	spell* check = dynamic_cast<spell *>(temp);
	if(check) {
			if (check->getname() == "Bomb") {
			//Xwindow w;
		//	w.drawBigString(246, 500, "BOOOOOOOOM!", Xwindow::Red);
			cout << " Booooooom!" << endl;
	//		string bad;
	//		cin >> bad;
				HP -= 5;
				delete temp;
		     } else { hand.push_back(temp);}
	} else {
                  hand.push_back(temp);
		}
                } else { throw "You cannot draw the card";}
              }

void player:: usespell(player* my, player* op, int index) {
	if(hand[index-1]->getcost() > magic) {
		throw "You don't have enough magic!";
} else {
	if(static_cast<spell *>(hand[index-1])->getname() == "Recharge") {
		if(my->getmyri()) {
				card* temp = hand[index-1];
                  hand.erase(hand.begin()+index-1);
                  static_cast<spell *>(temp)->playspell(my, op);
                  magic -= temp->getcost();
                  delete temp;
		} else { throw "You don't have ritual";}
      } else if(static_cast<spell *>(hand[index-1])->getname() == "Raise Dead") {
		if(my->getgyard().size() == 0 || my->getboard().size() == 5) {
			throw "Can't use Raise Dead";
		} else {
		          card* temp = hand[index-1];
	                  hand.erase(hand.begin()+index-1);
        	          static_cast<spell *>(temp)->playspell(my, op);
                	  magic -= temp->getcost();
               	          delete temp;
		}
      } else {
	    	  card* temp = hand[index-1];
                  hand.erase(hand.begin()+index-1);
                  static_cast<spell *>(temp)->playspell(my, op);
		  magic -= temp->getcost();
		  delete temp;
      }
}
}

void player:: play(int index) { 
   if(hand[index-1]->getcost() > magic) { 
	throw "You don't have enough magic!";
} else {
	magic -= hand[index-1]->getcost();
      if (hand[index-1]->gettype() == 1) {         //check what is the type of card
            if (board.size() < 5) {
                    card* temp = hand[index-1];
                    hand.erase(hand.begin()+index-1);
                    board.push_back(temp);

         } else { throw "you have already 5 minions";}
   } else if (hand[index-1]->gettype() == 3) {
                  if(myri) {
                            delete myri;
                            card* temp = hand[index-1];
                            hand.erase(hand.begin()+index-1);
                            myri = static_cast <ritual *> (temp);
                } else {
			    card* temp = hand[index-1];
                            hand.erase(hand.begin()+index-1);
                            myri = static_cast <ritual *> (temp); 
		}
   } 
   
 }
}

void player:: play(int index, player* tp, int t) {

      if (hand[index-1]->gettype() == 4) {
            if (tp->getboard().size() > 0) {
                      card* temp = hand[index-1];
                      hand.erase(hand.begin()+index-1);
		      magic -= temp->getcost();
                      static_cast<minion *> (tp->getboard()[t-1])->enhance(static_cast<enchantment *> (temp));
            }
              
   } else if (hand[index-1]->gettype() == 2) {
	   	if( t > 0 && t < 6) {
			if(tp->getboard().size() >= t) {
				if(static_cast<spell *>(hand[index-1])->getname() == "Disenchant") {
					if(static_cast<minion *>(tp->getboard()[t-1])->getmyen().size() == 0) {
						throw "Can't do this";
					} else {
					  	 card* temp = hand[index-1];
 		                                 hand.erase(hand.begin()+index-1);
                	               		 static_cast<spell *>(temp)->playspell(tp, t);
                        	      		 magic -= temp->getcost();
                                	 	 delete temp;
					}
			} else {	 			
				card* temp = hand[index-1];
				hand.erase(hand.begin()+index-1);
				static_cast<spell *>(temp)->playspell(tp, t);
				magic -= temp->getcost();
                		  delete temp;
			}
                      } else {
	                  			throw "Not available target!";}
	      } else {
			if(t == 6) {
				 card* temp = hand[index-1];
                                hand.erase(hand.begin()+index-1);
                                static_cast<spell *>(temp)->playspell(tp, t);
				magic -= temp->getcost();
                                  delete temp;
			} else { throw "Not available target!";}
  	      }
       }
    }

void player:: mdead(int index) {
	if (static_cast<minion *>(board[index])->mdead()) {
			static_cast<minion *>(board[index])->reset();
			card* temp = board[index];
			board.erase(board.begin() + index);
			gyard.push_back(temp);
			}
	}		 

void player:: setdeck(string fname) {
      ifstream filestream{fname};
      string pre;
      string next;
      string name;
      while (filestream >> pre) {
            if (pre == "Air") {
                filestream >> next;
                name = pre + " " + next;
                card* temp = new minion {name, 0, 1, 1, 0, false, ""};   
                deck.push_back(temp);           
         } else if (pre == "Earth") {
                filestream >> next;
                name = pre + " " + next;
                card* temp = new minion {name, 3, 4, 4, 0, false, ""};
                deck.push_back(temp);
	 } else if (pre == "Water") {
		filestream >> next;
                name = pre + " " + next;
                card* temp = new minion {name, 2, 1, 2, 0, true, "At end of turn, heal 1 to yourself"};
                deck.push_back(temp);
	 } else if (pre == "Treasure") {
		filestream >> next;
		name = pre + " " + next;
		card* temp = new minion {name, 3, 2, 2, 0, true, "At end of turn, give your minions in the hand +1/+1"};
		deck.push_back(temp);
         } else if (pre == "Fire") {
                filestream >> next;
                name = pre + " " + next;
                card* temp = new minion {name, 2, 2, 2, 0, true, "Whenever an opponent's minion enters play, deal 1 damage to it"};
                deck.push_back(temp);
         } else if (pre == "Giant") {
                filestream >> next;
           	name = pre + " " + next;
          	card* temp = new enchantment {name, 1, ""};
         	deck.push_back(temp);
	}  else if (pre == "Silence") {
		name = pre;
		card* temp = new enchantment {name, 1, "Enchanted minion cannot use abilities"};
                deck.push_back(temp);
	}  else if (pre == "Magic") {
                filestream >> next;
                name = pre + " " + next;
                card* temp = new enchantment {name, 0, "Enchanted minion's activated ability costs 2 more"};
                deck.push_back(temp);
  	}  else if (pre == "Fertilizer") {
		name = pre;
		card* temp = new enchantment {name, 2, "Give minion a new activated ability that cost 2 and gain a target minion's attack"};
		deck.push_back(temp);
        }  else if (pre == "Dark") {
                filestream >> next;
                name = pre + " " + next;
                card* temp = new ritual {name, 0, 5, 1, "At the start of your turn, gain 1 magic"};
                deck.push_back(temp);
	}  else if (pre == "Explosive") {
		filestream >> next;
                name = pre + " " + next;
		card* temp = new ritual {name, 3, 1, 1, "Deal 2 damage to opponent minions and hero"};
		deck.push_back(temp);
        }  else if (pre == "Aura") {
                filestream >> next;
                string third;
                filestream >> third;
                name = pre + " " + next + " " + third;
                card* temp = new ritual {name, 1, 4, 1, "whenever a minion enters play under your control, it gains +1/+1"};
                deck.push_back(temp);
       }   else if (pre == "Blizzard") {
		name = pre;
		card* temp = new spell {name, 3, "Deal 2 damage to all minions"};
	        deck.push_back(temp);
       }   else if (pre == "Raise") {
		filestream >> next;
		name = pre + " " + next;
		card* temp = new spell {name, 1, "Resurrect the top minion in your graveyard"};
		deck.push_back(temp);
       }  else if (pre == "Surprise") {
		name = pre;
		card* temp = new spell {name, 2, "Put a Bomb into your opponent deck"};
		deck.push_back(temp);
       }  else if (pre == "Recharge") {
                name = pre;
                card* temp = new spell {name, 1, "Your ritual gains 3 charges"};
                deck.push_back(temp);
       }  else if (pre == "Banish") {
                name = pre;
                card* temp = new spell {name, 2, "Destory target minion or ritual"};
                deck.push_back(temp);
       }  else if (pre == "Unsummon") {
                name = pre;
                card* temp = new spell {name, 1, "Put target minion on the bottom of its owner's deck"};
                deck.push_back(temp);
       }  else if (pre == "Disenchant") {
                name = pre;
                card* temp = new spell {name, 1, "Destroy the top enchantment on target minion"};
                deck.push_back(temp);
       }  else if (pre == "Potion") {
            filestream >> next;
            name = pre + " " + next;
            card* temp = new minion {name, 2, 1, 3, 0, true, "At the end of your turn, all your minions gain +0/+1"};
            deck.push_back(temp);
       }  else if (pre == "Novice") {
            filestream >> next;
            name = pre + " " + next;
            card* temp = new minion {name, 1, 0, 1, 1, true, "Deal 1 damage to target minion"};
            deck.push_back(temp);
       }  else if (pre == "Apprentice") {
            filestream >> next;
            name = pre + " " + next;
            card* temp = new minion {name, 1, 1, 1, 1, true, "Summon a 1/1 air elemental"};
            deck.push_back(temp);
       }  else if (pre == "Master") {
            filestream >> next;
            name = pre + " " + next;
            card* temp = new minion {name, 3, 2, 3, 2, true, "Summon up to three 1/1 air elementals"};
            deck.push_back(temp);
       }  else if (pre == "Standstill") {
	    name = pre;
	    card* temp = new ritual {name, 3, 4, 2, "Whenever a minion enters play, destroy it"};
	    deck.push_back(temp);
       }
     }
    }
vector<card *>& player:: getdeck() {
	return deck;
	}

vector<card *>& player:: gethand() {
        return hand;
        }

vector<card *>& player:: getboard() {
        return board;
        }

vector<card *>& player:: getgyard() {
        return gyard;
        }


void player:: changemagic(int num) {
      magic += num;
}

void player:: nextturn() {
      if (active == true) {
          active = false;
    } else {
          active = true;
    }
}

void player:: deletemyri() {
	delete myri;
	myri = nullptr;
}

bool player:: getact() {
	return active;
}

void player:: injure(int num) {
	HP -= num;
}

void player:: notifyr(player* my, player* op, string command) { 
    if (myri) {
            myri->notify(my, op, command);
    } 
}

int& player:: getmagic() {return magic;}

ritual* player:: getmyri() {return myri;}

   //inspect minion
   void player::inspectminion(int i){
       int size = board.size();
       if(i < 1 || i > size){
           cout << "your don't have ith minion" << endl;
       }else{
           board[i-1]->display();
            minion* temp = dynamic_cast<minion *>(board[i-1]);
           if(temp->getmyen().size() != 0){
           display_min_enchant(i);}
       }
   }
   
   void player::display_min_enchant(int a){
	int num_of_ench;
	minion* temp = dynamic_cast<minion *>(board[a-1]);

	if(temp) { num_of_ench = temp->getmyen().size(); }
   
       int curr = 0;
       int curr_num = num_of_ench;
       //recursively print five enchantments a line until the remaining enchantments is less than five
       while(curr_num > 5){
        vector<string>line(11, "");
        for(int i = 0; i<11; ++i){

          for(int j = 0; j < 5; ++j){
             line[i] += temp->getmyen()[curr]->getGraphics()[i];
	     ++curr;
          }
	curr -= 5;
        }
        //print
        int len = line.size();
        for(int m = 0; m < len; ++m){
            cout << line[m] << endl;
        }
        curr += 5;
        //reset curr
        curr_num -= 5;
       }
       
       //print out the remaining enchantments 
       vector<string>line_final(11, "");
        for(int n = 0; n<11; ++n){
         for(int x = 0; x < curr_num; ++x){
    
           line_final[n] += temp->getmyen()[curr]->getGraphics()[n];  
           ++curr;
         }
	curr -= curr_num;
        }
        int len_final = line_final.size();
        for(int z = 0; z < len_final; ++z){
            cout << line_final[z] << endl;
        }
   }  

  void player::use(player* op, int i) {
    if (board.size() < i) {
        throw "Can't find the target minion";
	
    }
    minion *tempmin = static_cast<minion*>(board[i-1]);
    if (tempmin->geteff_cost() > magic) {
        throw "You don't have enough magic!";
	
    } else {
        tempmin->use_eff(this, op);
        magic -= tempmin->geteff_cost();
    }
}

  void player::use(int i, player *p, int t) {
    if (board.size() < i) {
        throw "Can't find the target minion";
    } 
    minion *tempmin = static_cast<minion*>(board[i-1]);
    if (tempmin->geteff_cost() > magic) {
	throw "You don't have enough magic!";
   } else {
        tempmin->use_eff(p, t);
	magic -= tempmin->geteff_cost();
    }
  }

 void player:: discard(int i) {
	if(hand.size() >= i) {
    card* temp = hand[i-1];
    hand.erase(hand.begin() + i - 1);
    delete temp;
} else {
	throw "Can't discard";
	}
}



//hand display
void player::hand_display(){
   vector<string> line(11, "");
   int len = hand.size();
   for(int i = 0; i<11; ++i){
     for(int j = 0; j<len; ++j){
       line[i] += hand[j]->getGraphics()[i];
     }
   }
  display_player(line);
}


//display the first row for each player
void player::row_first_display(int t){
        vector<string> line(11, "");
        
        for(int i = 0; i< 11; ++i){
           line[i] += "║";
	   if(myri){
            line[i]+= (myri->getGraphics()[i]);
           }else{
  	    line[i] += CARD_TEMPLATE_BORDER[i];
  	   }
	     line[i] += CARD_TEMPLATE_EMPTY[i];
           
            if(t == 1){
              line[i] += display_player_card(1, name, HP, magic)[i];
            }else{
              line[i] += display_player_card(2, name, HP, magic)[i];
            }
             line[i]+= CARD_TEMPLATE_EMPTY[i];
	    if(gyard.size() != 0){
             line[i]+= (gyard.back()->getGraphics()[i]);
            }else{
 	     line[i]+= CARD_TEMPLATE_BORDER[i];   
	    }
  	   line[i] += "║";
   	 }
        //print out each string in line vector
        display_player(line);
}


//display the second row for each player, which is the row of minions
void player:: row_second_display(){
      vector<string>line(11, "");
      int minionsize = board.size();
      if(minionsize == 0){
   	for(int i = 0; i < 11; ++i){
	 line[i] += "║";
   	 for(int j = 0; j<5; ++j){
          line[i]+= CARD_TEMPLATE_BORDER[i];
         }
	 line[i] += "║";
        }
      }else{
       for(int i = 0; i< 11; ++i){
	line[i] += "║";
        for(int j = 0; j<minionsize; ++j){
              
          line[i] += (board[j]->getGraphics()[i]);
        }
       }
       for(int i = 0; i<11; ++i){
	  int remain_len = 5 - minionsize;
 	  for(int z = 0; z < remain_len; ++z){
	    line[i] += CARD_TEMPLATE_BORDER[i];
          }
	  line[i] += "║";
       }
      }
      //print out each string in line vector
      display_player(line);
}

//display the player-side board
void player:: display_myturn(int i){
    if(i == 1){
      row_first_display(i);
      row_second_display();
    }else{
      row_second_display();
      row_first_display(i);
    }
}
  
