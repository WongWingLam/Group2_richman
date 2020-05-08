#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include "richMan_struct.h"

using namespace std;

struct Status{
  string name;
  int cash;
  int property;
  int position;
};

struct Block{
  string name;
  double price;
  int Lv;
  string ownership;
};

void save_temp(Block *mapBlocks, Status *players, int n, int round, int turn, int mode){
  ofstream fout("temp.txt");
  if (fout.fail()) {
    //the error message to notify failed opening; (2) for exporting text
    cout << "Error in the file opening!" << endl;
    exit(1);
  }
   int j = 0;
  while (j < 36+n+1) {
    if (j <36) {
      fout << mapBlocks[j].name << " "
        << mapBlocks[j].price << " "
        << mapBlocks[j].Lv << " "
        << mapBlocks[j].ownership;
      if (j == 35) {
        fout << " " << n;
      }
      fout << endl;
    }
    else if (j > 35 && j < 36+n) {
      fout << players[j-36].name << " "
        << players[j-36].cash << " "
        << players[j-36].property << " "
        << players[j-36].position << endl;
    }
    else {
      fout << round << " " << turn << " " << mode << endl;
    }
    j++;
  }
  fout.close();
}

void load_temp(Block *mapBlocks, Status *players, int n, int round, int turn, int mode) {
  string slot_name = "temp";
  string name;
  ifstream fin(slot_name+".txt"); //change the cmd when the name of directory changed
  if (fin.fail()) {
    //the error message to notify failed opening; (1) for importing text
    cout << "Error in the file opening!" << endl;
    exit(1);
  }
  int j = 0;
  int j = 0;
  while (fin >> name) {
    if (j < 36){
      mapBlocks[j].name = name;
      fin >> mapBlocks[j].price;
      fin >> mapBlocks[j].Lv;
      fin >> mapBlocks[j].ownership;
      if (j == 35) {
        fin >> playerNo;
        players = new Status[playerNo];
      }
    }
    else if (j > 35 && j < 36 + playerNo) {
      players[j-36].name = name;
      fin >> players[j-36].cash;
      fin >> players[j-36].property;
      fin >> players[j-36].position;
    }
    else {
      round = stoi(name);
      fin >> turn;
      fin >> mode;
    }
    j++;
  }
  fin.close();
}
