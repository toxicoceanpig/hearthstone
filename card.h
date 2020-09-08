#ifndef CARD_H
#define CARD_H
#include <string>
#include <vector>

   class card {
	protected:
      int cost;
	public:
	   card(int cost): cost{cost} {}
     virtual int gettype() = 0;
     int getcost();
     virtual std::vector<std::string> getGraphics() = 0;   
     virtual void display() = 0;
     void carddisplay(std::vector<std::string> card_display);
     virtual ~card() {} 
   };

#endif
