#ifndef MINION_H
#define MINION_H
#include <string>
#include "player.h"
#include "enchantment.h"


class minion :public card {
      int att;
      int def;
      int orgatt;
      int orgdef;
      std::string name;
      int type;
      std::vector<enchantment *> myen;
      int eff_cost;
      int orgeff_cost;
      bool useeff;
      std::string desc;
      bool turn;
      enchantment* neweff;
    public:
      ~minion();
      std::string getname();
      void newturn();
      void notify(player* my, player* op);
      void dehance();
      void enhance(enchantment *en);
      std::vector<enchantment *>& getmyen();
      void attack(player &target);
      void attack(player &target, int i);
      void injure(int i);
      void amidead();
      void reset();
      bool mdead();
      int getatt();
      int gettype();
      int& geteff_cost();
      bool& getuseeff();
      void use_eff(player *my, player *op);
      void use_eff(player *p, int t); 
      void display() override;
      void notifym(player* my, player* op, std::string time);
      std::vector<std::string> getGraphics() override;
      void gainatt(int num);
      minion(std::string name, int cost, int att, int def, int eff_cost, bool useeff, std::string desc):neweff{nullptr}, orgeff_cost{eff_cost}, turn{true}, desc{desc}, eff_cost{eff_cost}, useeff{useeff}, type{1}, orgatt{att}, orgdef{def}, name{name}, card{cost}, att{att}, def{def} {}
};

#endif
