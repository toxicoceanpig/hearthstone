#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "card.h"
#include "ritual.h"
   class player {
      int HP;
      int magic;
      std::string name;
      std::vector<card *> deck;
      std::vector<card *> hand;
      std::vector<card *> gyard;
      std::vector<card *> board;
      bool active;
      ritual* myri;
    public:
      std::string getname();
      player(int hp, int magic, std::string name, bool active): myri{nullptr}, HP{hp}, magic{magic}, name{name}, active{active} {} 
      void draw();
      bool dead();
      void play(int index);
      void play(int index, player* tp, int t);
      void setdeck(std::string fname);
      void changemagic(int num);
      void nextturn();
      void injure(int num);
      void usespell(player* my, player* op, int index);
      std::vector<card *> &getdeck();
      std::vector<card *> &gethand();
      std::vector<card *> &getboard();
      std::vector<card *> &getgyard();
      void mdead(int index);
      bool getact();
      void deletemyri();
      int& getmagic();
      void notifyr(player* my, player* op, std::string command);
      void use(int index, player* tp, int t);
      void use(player* op, int index);
      ritual* getmyri();
      void inspectminion(int i);
      void display_min_enchant(int a);
      void discard(int i);
      void display_player(std::vector<std::string> v);
      void hand_display();
      void row_first_display(int); 
      void row_second_display();
      void display_myturn(int);
      void display_whole();  
      ~player();      
};

   #endif

