#include "players.h"
#include "player.h"
#include "ascii_graphics.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

player* players:: actturn() {
    if(p1->getact() == true) {
      return p1;
  } else {
      return p2;
  }
}

player* players:: inactturn() {
    if(p1->getact() == false) {
      return p1;
  } else {
      return p2;
  }
}

player* players:: getp1() {
	return p1;
	}

player* players:: getp2() {
        return p2;
        }

//display the whole board
void players:: display_whole(){
  cout << "╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗"  << endl;
   p1->display_myturn(1);
   for(int i = 0; i < 10; ++i){
      cout << CENTRE_GRAPHIC[i] << endl;
   }
   p2->display_myturn(2);
   cout << "╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝"<< endl;
}

