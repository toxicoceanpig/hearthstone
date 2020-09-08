#ifndef RITUAL_H
#define RITUAL_H
#include <string>
#include "card.h"
class player;

class ritual : public card {
      std::string name;
      int type;
      int cost;
      int charge;
      int chargecost;
      std::string desc;
    public:
      int gettype();
      void getcharge(int i);
      ritual (std::string name, int cost, int charge, int chargecost, std::string desc): name{name}, card{cost}, type{3}, charge{charge}, chargecost{chargecost}, desc{desc}, cost{cost} {}
      void notify (player *my, player *op, std::string command);
      std::vector<std::string>getGraphics() override;
      void display() override;
};

#endif
