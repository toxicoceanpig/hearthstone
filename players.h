#ifndef PLAYERS_H
#define PLAYERS_H
#include "player.h"






  class players {
      player *p1;
      player *p2;
    public:
      players(player *p1, player *p2): p1{p1}, p2{p2} {}
      player* actturn();
      player* inactturn();
      player *getp1();
      player *getp2();
      void display_whole();
      
  };

#endif

