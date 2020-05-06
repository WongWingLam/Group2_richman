// richMan_save.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sys/stat.h>
#include "richMan_save.h"
#include <dirent.h>

using namespace std;

void richMan_save(Block *mapBlocks, Status *players){
  string slot_name;
  DIR *dir = opendir("save");

  struct dirent *entry;
  struct stat info;

  if (!dir) {
    cout << "Directory was not found\n" << endl;
    return;
  }
  entry = readdir(dir);
//(entry = readdir(dir)) != NULL
  while ((entry = readdir(dir)) != NULL ){
    if ( entry->d_name[0] != '.'){
      string name = string(entry->d_name);
      name = name.erase(name.find(".txt"), 4);
      cout << name << endl;
      stat(name.c_str(), &info);
          /*if (S_ISDIR(info.st_mode)) {
            load_richman(save);
          }*/
    }
  }
  closedir(dir);

  cout << "Which slot do you want to overwrite? (Name of file)";
  cin >> slot_name;
  string stringpath = "save";
  //int status = mkdir(stringpath.c_str(),0777);
  ofstream fout("save/"+slot_name+".txt");
  if (fout.fail()) {
    //the error message to notify failed opening; (2) for exporting text
    cout << "Error in the file opening!" << endl;
    exit(1);
  }
  int n = 0;
  for (int i=0; i<4; i++){
    if (player[i] != NULL){n++;}
  }
  int j = 0;
  while (j < 36+n) {
    if (j <36) {
      fout << mapBlocks[j].name << " "
        << mapBlocks[j].price << " "
        << mapBlocks[j].Lv << " "
        << mapBlocks[j].ownership << endl;
    }
    else {
      fout << "P" << players[j-36].id << " "
        << players[j-36].cash << " "
        << players[j-36].property << " "
        << players[j-36].pos << endl;
    }
    j++
  }
  fout.close();
}

int main(){
  richMan_save("save");
  return 0;
}
