#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include "richMan_display.h"
#include "richMan_mapEffect.h"
#include "richMan_randomevent.h"

using namespace std;

//triger different effect when player go to different block of the map
void mapEffect(int dice, int mode, int turn, Block *mapBoard, Status *players, int playerNo, int *freeze){
  int choice = 1;
  int pos = players[turn].position;
  while (choice && (mode ==2 || (mode == 1 && turn ==0)))
  {
    //system("CLS");
    //displayMap(mapBoard, players, playerNo);
    cout << "=====================================================" << endl
    << "The dice number is " << dice << "  "
    << players[turn].name << " go to " << mapBoard[pos].name << endl
    << "=====================================================" << endl
    << "Cash: " << players[turn].cash << ' ' << "Property owned: " << players[turn].property << endl
    << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    //cout << mapBoard[pos].ownership << endl;
    if (players[turn].cash > mapBoard[pos].price && mapBoard[pos].ownership == -1)
    {
      int buy;
      cout << "Buy " << mapBoard[pos].name << "(price: "<< mapBoard[pos].price << ')' << " ? (1:buy 0:not buy)";
      cin >> buy;
      if (buy)
      {
        mapBoard[pos].ownership = turn;
        players[turn].cash -= mapBoard[pos].price;
        cout << "## " << players[mapBoard[pos].ownership].name << " become the owner of " << mapBoard[pos].name << " ##" << endl
        << "## Cash remaining: " << players[turn].cash << " ##" << endl;
        players[turn].property += 1;
      }
    }
    else if (mapBoard[pos].ownership == turn && players[turn].cash >= mapBoard[pos].price*0.5)
    {
      int invest;
      cout << "Invest " << mapBoard[pos].price*0.5 << " to upgrade " << mapBoard[pos].name << " ? (1:yes 0:No)";
      cin >> invest;
      if(invest)
      {
        mapBoard[pos].Lv += 1;
        players[turn].cash -= mapBoard[pos].price*0.5;
        if (mapBoard[pos].Lv >= 3)
        {
          mapBoard[pos].price *= 2;
        }
        else
        {
          mapBoard[pos].price *= 1.5;
        }
        cout << "## Successfully upgrade " << mapBoard[pos].name << " to Lv: " << mapBoard[pos].Lv << " ##" << endl
        << "## Value of " << mapBoard[pos].name << " become $" << mapBoard[pos].price << " ##" << endl
        << "## Cash remaining: " << players[turn].cash << " ##" << endl;
      }
    }
    else if(mapBoard[pos].ownership >= 0 && mapBoard[pos].ownership < playerNo && mapBoard[pos].ownership != turn)
    {
      cout << "## " << mapBoard[pos].name << " is owned by " << players[mapBoard[pos].ownership].name << " ##" << endl
      << "## You have to pay $" << mapBoard[pos].price*0.4 << " to " << players[mapBoard[pos].ownership].name << " ##" << endl;
      players[turn].cash -= mapBoard[pos].price*0.4;
      players[mapBoard[pos].ownership].cash += mapBoard[pos].price*0.4;
      cout << "## Cash remaining: " << players[turn].cash << " ##" << endl;
    }
    else if (mapBoard[pos].name.compare("Chance") == 0)
      random_event("chance", players, turn);
    else if (mapBoard[pos].name.compare("Destiny") == 0)
    {
      random_event("destiny", players, turn);
      if (players[turn].position == 9)
      {
        freeze[turn] = 3;
      }
      if (players[turn].position == 18)
      {
        freeze[turn] = 2;
      }
    }
    cout << endl;
    while (choice != 0)
    {
      cout << "Enter 0 to continue the game: ";
      cin >> choice;
    }
  }
  
//ai part
  while (choice && mode == 1 && turn !=0)
  {
    cout << "The dice number is " << dice << "  "
    << players[turn].name << " go to " << mapBoard[pos].name << endl
    << "Cash: " << players[turn].cash << ' ' << "Property owned: " << players[turn].property << endl
         << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    if (players[turn].cash > mapBoard[pos].price && mapBoard[pos].ownership == -1)
    {
      int buy = 1;
      if (buy)
      {
        mapBoard[pos].ownership = turn;
        players[turn].cash -= mapBoard[pos].price;
        cout << "## " << players[mapBoard[pos].ownership].name << " become the owner of " << mapBoard[pos].name << " ##" << endl
        << "## Cash remaining: " << players[turn].cash << " ##" << endl;
        players[turn].property += 1;
      }
    }
    else if (mapBoard[pos].ownership == turn && players[turn].cash >= mapBoard[pos].price*0.1)
    {
      int invest = 1;
      if(invest)
      {
        mapBoard[pos].Lv += 1;
        players[turn].cash -= mapBoard[pos].price*0.5;
        if (mapBoard[pos].Lv >= 3)
        {
          mapBoard[pos].price *= 2;
        }
        else
        {
          mapBoard[pos].price *= 1.5;
        }
        cout << "## Successfully upgrade " << mapBoard[pos].name << " to Lv: " << mapBoard[pos].Lv << " ##" << endl
        << "## Value of " << mapBoard[pos].name << " become $" << mapBoard[pos].price << " ##" << endl
        << "## Cash remaining: " << players[turn].cash << " ##" << endl;
      }
    }
    else if(mapBoard[pos].ownership >= 0 && mapBoard[pos].ownership < playerNo && mapBoard[pos].ownership != turn)
    {
      cout << "## " << mapBoard[pos].name << " is owned by " << players[mapBoard[pos].ownership].name << " ##" << endl
      << "## You have to pay $" << mapBoard[pos].price*0.4 << " to " << players[mapBoard[pos].ownership].name << " ##" << endl;
      players[turn].cash -= mapBoard[pos].price*0.4;
      players[mapBoard[pos].ownership].cash += mapBoard[pos].price*0.4;
      cout << "## Cash remaining: " << players[turn].cash << " ##" << endl;
    }
    else if (mapBoard[pos].name.compare("Chance") == 0)
    {
      random_event("chance", players, turn);
    }
    else if (mapBoard[pos].name.compare("Destiny") == 0)
    {
      random_event("destiny", players, turn);
      if (players[turn].position == 9)
      {
        freeze[turn] = 3;
      }
      if (players[turn].position == 18)
      {
        freeze[turn] = 2;
      }
    }
    choice = 0;
  }

  return;
}
