#ifndef NEWMAIN_H
#define NEWMAIN_H

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <termios.h>
#include <errno.h>
 #include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
#include <algorithm>
#include "data.h"
#include<unordered_map>
#include <string.h>
#include <vector>
#include <fstream>
#include <cstdint>
#include <experimental/filesystem>
 #include <fts.h>
using namespace std;
#define PATH_MAX 4096

class newmain {
public:

newmain();
BinarySearchTree<BSTNode<file>,file>* tree1= new BinarySearchTree<BSTNode<file>,file>;

long long  onedir(short indent,char *name,BinarySearchTree<BSTNode<file>,file>* Ntree);
void traverseASC(BSTNode<file>*n);
void traverseChild(BSTNode<file>*n,ofstream &myfile,string cwd);
void insertFile(file a, BinarySearchTree<BSTNode<file>,file>*t);
string utility (string temp);
int getnfiles(){return nfiles;}
int getndirectories(){return ndirectories;}
int recursive_delete(const char *dir);
void run(char *);
BinarySearchTree<BSTNode<file>,file> * insertdirectory(file a,BSTNode<file> *n);
string cw;

private:

long long nbytes;
int nfiles;
int ndirectories;
long long v_size;
long t_size;
long long totalsize;
};


#endif // NEWMAIN_H
