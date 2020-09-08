#ifndef spell_h
#define spell_h
#include "players.h"
#include <string>
#include "card.h"


class spell :public card {
	std::string name;
	int type;
        std::string desc;
        int cost;
      public:
	std::string getname();
	spell(std::string name, int cost, std::string desc): card{cost}, name{name}, desc{desc}, cost{cost}, type{2} {}
	void playspell(player* my, player* op);
	int gettype();
	void playspell(player* tp, int t);
 	std::vector<std::string>getGraphics() override;
        void display() override;
};

#endif
