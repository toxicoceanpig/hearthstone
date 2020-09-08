#ifndef _EN_H_
#define _EN_H_
#include <string>
#include <vector>
#include "card.h"


class enchantment : public card {
 int type;
 std::string name;
 int cost;
 std::string desc;
public:
  enchantment(std::string name,int cost, std::string desc);
  std::string getname();
  int gettype();
  void display() override;
  std::vector<std::string> getGraphics(); 
};

#endif
