// richMan_load.cpp
#include <iostream>
#include <fstream>
#include "richMan_load.h"
#include <cstdlib>
#include <string>
#include <sys/stat.h>
#include <dirent.h>
#include "richMan_struct.h"

using namespace std;

//Pass by reference to update the data in main and struct
void richMan_load(struct Block *mapBlocks, struct Status *&players, int &playerNo, int &round, int &turn, int &mode, int *&freeze){
  string slot_name;
  char save[10] = "save";
  DIR *dir= opendir(save);

  struct dirent *entry;
  struct stat info;

  if (!dir) {
    cout << "Directory was not found\n" << endl;
    return;
  }
  entry = readdir(dir);
  while ((entry = readdir(dir)) != NULL ){ //to read the files in directories
    if ( entry->d_name[0] != '.'){
      string name = string(entry->d_name);
      name = name.erase(name.find(".txt"), 4);
      if (name != "default" && name != "Template")
      {
        cout << name << endl;
      }
      stat(name.c_str(), &info);
    }
  }
  closedir(dir);

  cout << "Which slot do you want to load? (Name of file)" << endl;
  string name;
  cin >> slot_name;
  int check = 0; 
  ifstream fin("save/"+slot_name+".txt"); //change the cmd when the name of directory changed
  while (fin.fail()) {
    //the error message to notify failed opening; (1) for importing text
    cout << "Wrong file name!!! Please enter the correct slot name!!!" << endl;
    cin >> slot_name;
    fin.open("save/"+slot_name+".txt");
  }

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
      fin >> turn >> mode;
      freeze = new int[playerNo];
      for (int i = 0; i < playerNo; i++)
      {
        fin >> freeze[i];
      }
    }
    j++;
  }
  fin.close();
}
