#include "card.h"
#include <vector>
#include <string>
#include <iostream>
#include "ascii_graphics.h"
using namespace std;

int card:: getcost() {
	return cost;
}

 void card:: carddisplay(vector<string> card_display){
    int len = card_display.size();
    for(int i = 0; i < len; ++i){
        cout << card_display[i] << endl;
    }
}
