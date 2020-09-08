#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <exception>
#include "card.h"
#include "minion.h"
#include "player.h"
#include "players.h"
#include "enchantment.h"
#include "ritual.h"
#include "spell.h"
#include "string.h"

using namespace std;

  int main(int argc, char* argv[]) {
      bool firstgame = true;     // use to test whether is first player's first game
      string name1;
      string name2;
      string time;                // used on certain time for trigger
      bool testmode = false;                
      string fname1 = "default.deck";
      string fname2 = "default.deck";
      string ini_file;
      bool ini_exist = false;
                                                    // check command argument line
      for (int i = 0; i < argc; i++) {
          if (strcmp(argv [i], "-deck1") == 0) {
              i++;
              fname1 = argv[i];
          } else if (strcmp(argv [i], "-deck2") == 0){
              i++;
              fname2 = argv[i];
          } else if (strcmp(argv[i], "-testing")== 0) {
              testmode = true;
          } else if (strcmp(argv[i], "-init") == 0) {
              ini_exist = true;
              i++;
              ini_file = argv[i];
          }
      }
      
      ifstream myfile;
                                        // next two are for initial check
      if(ini_exist) {
          myfile.open(ini_file);
                        if(myfile >> name1) {
                        } else if(myfile.eof()){
                                    ini_exist = false;
                                    cout << "Who you are ?" << endl;
                                    cin >> name1;
                                  }
      } else {
          cout << "Who you are ?" << endl;
          cin >> name1;
      }
      
      if(ini_exist) {
                          if(myfile >> name2) {
                          } else if(myfile.eof()){
                                    ini_exist = false;
                                    cin >> name2;
                                  }
      } else {
          cin >> name2;
      }

      // create main sorcery class
      players p12 {new player {20, 3, name1, true}, new player {20, 3, name2, false}};

        p12.getp1()->setdeck(fname1);
        p12.getp2()->setdeck(fname2);
        
       
  // shuffle both decks
        random_shuffle(p12.getp1()->getdeck().begin(), p12.getp1()->getdeck().end());
        random_shuffle(p12.getp2()->getdeck().begin(), p12.getp2()->getdeck().end());
	
	// set hand to four
        for (int i = 0; i < 4; ++i) {
	try{
            p12.getp1()->draw();
        }  catch(char const* s) { cout << s << endl;}
	try{
	    p12.getp2()->draw();
        }  catch(char const* s) { cout << s << endl;}
	}
	
	
  // this is the main while loop, players start their turn alternately. 
  // When the loop out, the game is over.        
        while(true) {
          // at the start of the turn trigger
			    	    time = "start";
          // notify all actturn player's minions
					for(int i = 0; i < p12.actturn()->getboard().size(); ++i) {
          static_cast<minion *>(p12.actturn()->getboard()[i])->notifym(p12.actturn(), p12.inactturn(), time);
          }                        
          // notify trigger
          p12.actturn()->notifyr(p12.actturn(), p12.inactturn(), time);

          // reset all minions turn (let them able to attack or use)
				    for(int i = 0; i < p12.actturn()->getboard().size(); ++i) {
					static_cast<minion *>(p12.actturn()->getboard()[i])->newturn();
				    }
	
          if (!firstgame) {     // check is not the first turn
                      try{                    
                            p12.actturn()->changemagic(1);
				                        p12.actturn()->draw();
				                              if(p12.actturn()->dead()) {       // check for Bomb
                                                cout << p12.inactturn()->getname() << " win !" << endl;
                                                delete p12.getp1();
                                                delete p12.getp2();
                                                cout << "GAME OVER" << endl;
						                                    return 0;
			                                           }
                        } catch(char const* s) {cout << s << endl;}  
			    }

          firstgame = false;  // turn off the first game
          
			while(true) {
                string command;
                string input;
                
                if(ini_exist) {
                    getline(myfile, input);
                    if (myfile.eof()) {
                        ini_exist = false;
                    }
                }
                
                if(!ini_exist){
                    getline(cin, input);
                    if (cin.eof()) {
                        break;
                    }
                }
                istringstream str{input};
                str >> command;

                                    if(command == "play") {  
                                      try{
            	        	                          int index;
             					                            str >> index;
               						                             int tp;
                                                      // check is 1 parameter or 3 
             				                                      if (str >> tp) {  
                        				                                int tm;
                        				                                    if (str >> tm) { 
										                                                            if(tp == 1) {  									                            
                        					                                                     p12.actturn()->play(index, p12.getp1(), tm);
							       		                                                      } else { 							
										                                                                   p12.actturn()->play(index, p12.getp2(), tm);
                        			                                                       } 
                                                                  } else {      // check the last parameter is r
                                       						                     char x;                                  					   
                                     					                         str >> x;
										                                                             if(tp == 1) {							   
                                                                                   p12.actturn()->play(index, p12.getp1(), 6);
									                                                             } else {   
									                                                                 p12.actturn()->play(index, p12.getp2(), 6);	
                                                                               }
            				                                                    }
                                                        } else {   // only 1 parameter
					minion* check = dynamic_cast<minion *>(p12.actturn()->gethand()[index-1]);     // check the card type
					spell* check0 = dynamic_cast<spell *>(p12.actturn()->gethand()[index-1]);
					ritual* check1 = dynamic_cast<ritual *>(p12.actturn()->gethand()[index-1]);
          
                			if(check0) { p12.actturn()->usespell(p12.actturn(), p12.inactturn(), index);
				
			    	   }  else if(check) {    // if it's a minion, then notify my minions and ritual
               
                         			 p12.actturn()->play(index);
					    int before = p12.actturn()->getboard().size();        // check the number of minion, in order to stop notify
						  time = "my new min";
              p12.actturn()->notifyr(p12.actturn(), p12.inactturn(), time);
					    int after = p12.actturn()->getboard().size();
                    // notify opponent's minions and ritual
					if(before == after) {
					 	  time = "op new min";
					    for(int i = 0; i < p12.inactturn()->getboard().size(); ++i) {
							if(before == after) {
				            static_cast<minion *>(p12.inactturn()->getboard()[i])->notifym(p12.inactturn(), p12.actturn(), time);
							after = p12.actturn()->getboard().size();
							                     }
						  }     
					if (before == after) {				
					p12.inactturn()->notifyr(p12.inactturn(), p12.actturn(), time); }}
					} else if (check1) {    
            p12.actturn()->play(index);}		
                       				}
				                                                    } catch(char const* s) { cout << s << endl;}
             
        } else if (command == "end") {
					time = "end";      // end of the turn trigger, same like above one
					for(int i = 0; i < p12.actturn()->getboard().size(); ++i) {
				static_cast<minion *>(p12.actturn()->getboard()[i])->notifym(p12.actturn(), p12.inactturn(), time);
					}
					p12.actturn()->notifyr(p12.actturn(), p12.inactturn(), time);
                                        p12.getp1()->nextturn();
                                        p12.getp2()->nextturn();
                                        break;
                                } else if (command == "quit") {
					                             delete p12.getp1();
					                             delete p12.getp2();
                                        return 0;
				} else if (command == "use") {      // same like play command
					try {
					            int index1;                  
                    str >> index1;
                                                        
                                                    int tp1;
                                                    if (str >> tp1) {
                                                                        int tm1;
                                                                      if (str >> tm1) {
                                                                                if(tp1 == 1) {
									
                                                                                p12.actturn()->use(index1, p12.getp1(), tm1);
									     
                                                                             } else {
									
                                                                                p12.actturn()->use(index1, p12.getp2(), tm1);
									  
                                                                             }
                                                                      } else { throw "Can't do this";}
                                                  } else { 
                                                        p12.actturn()->use(p12.inactturn(), index1);
	
                                                  }
					} catch(char const* s) {cout << s << endl;}	
          
				} else if (command == "inspect") {
					int i;
					str >> i;
					p12.actturn()->inspectminion(i); 
        } else if (command == "hand"){
					p12.actturn()->hand_display();
  			} else if(command == "board"){
			                 p12.display_whole(); 					
      				} else if (command == "attack") {
                             try{
                                        int x;
                                        str >> x;
					                              int y;     // check is attack player or minion
				                                         if(str >> y) {     					
					                                              static_cast<minion *> (p12.actturn()->getboard()[x-1])->attack(*p12.inactturn(), y);
				    	                                                 p12.actturn()->mdead(x-1);   //check my minion dead or not
				  	                                                   p12.inactturn()->mdead(y-1);  //check opponent minion dead or not
			
                                              } else {       				
                                                        static_cast<minion *> (p12.actturn()->getboard()[x-1])->attack(*p12.inactturn());
                                                        // fourth trigger occur
					                                                   time = "my hero has been attacked";
					                                                   p12.inactturn()->notifyr(p12.inactturn(), p12.actturn(), time);
						                                              if(p12.inactturn()->dead()) {   // check myself dead or not
                                                                
						                                                 cout << p12.actturn()->getname() << " win !" << endl;
						                                                       delete p12.getp1();
						                                                       delete p12.getp2();
						                                                 cout << "GAME OVER" << endl;
                                                             
							                                               return 0;
                                                           }
                                                           
						                                             if(p12.actturn()->dead()) {   // check opponent dead or not
                                                            
                                                            cout << p12.inactturn()->getname() << " win !" << endl;
                                                                  delete p12.getp1();
                                                                  delete p12.getp2();
                                                            cout << "GAME OVER" << endl;
                                                            
                                                            return 0;
                                                        }
                                                        
                                      } } catch(char const* s) {cout << s << endl;} 
                                      
       } else if (command == "draw") {  // draw in test mode
                if (testmode){
                          try {
                            p12.actturn()->draw();
		                        } catch(char const* s) { cout << s << endl;}
            } else {
                    cout << "This command is only available in -testing mode." << endl;
                }
                
      } else if (command == "discard") {   // same like draw
                if(testmode){
                    try {  
                        int index;
                        str >> index;
                        p12.actturn()->discard(index);
                    } catch (char const* s) {
                        cout << s << endl;
                    }
                } else {
                    cout << "This command is only available in -testing mode." << endl;
                }
                
      } else if (command == "help") {     //print help tip
        
			cout << "Commands: " << endl << endl;
			cout << "help -- Display this message." << endl;
			cout << "end -- End the current player’s turn." << endl;
			cout << "quit -- End the game." << endl;
			cout << "attack minion other-minion -- Orders minion to attack other-minion." << endl;
			cout << "attack minion -- Orders minion to attack the opponent." << endl;
			cout << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
			cout << "use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player." << endl;
			cout << "inspect minion -- View a minion’s card and all enchantments on that minion." << endl;
			cout << "hand -- Describe all cards in your hand." << endl;
			cout << "board -- Describe all cards on the board." << endl;
	    } 
     }
    }
} 
