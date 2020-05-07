#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include "richMan_display.h"
#include "richMan_mapEffect.h"

using namespace std;

void mapEffect(int dice, int turn, Block *mapBoard, Status *players, int playerNo){
  int choice = 1;
  int pos = players[turn].position;
  while (choice)
  {
    system("CLS");
    displayMap(mapBoard, players, playerNo);
    cout << "========================================================" << endl
    << "The dice number is " << dice << "  "
    << players[turn].name << " go to " << mapBoard[pos].name << endl
    << "========================================================" << endl
    << "Cash: " << players[turn].cash << ' ' << "Property owned: " << players[turn].property << endl
    <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    //cout << mapBoard[pos].ownership << endl;
    if (players[turn].cash > mapBoard[pos].price && mapBoard[pos].ownership == -1)
    {
      int buy;
      cout << "Buy " << mapBoard[pos].name << "(price: "<< mapBoard[pos].price << ')' << " ? (1:buy 0:not buy)";
      if (cin >> buy)
      {
        mapBoard[pos].ownership = turn;
        players[turn].cash -= mapBoard[pos].price;
        cout << "## " << players[mapBoard[pos].ownership].name << " become the owner of " << mapBoard[pos].name << " ##" << endl
        << "## Cash remaining: " << players[turn].cash << " ##";
      }
    }
    cout << endl << "Enter 0 to continue the game: ";
    cin >> choice;
  }
  return;
}