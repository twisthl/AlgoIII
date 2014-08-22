#ifndef EJ1_H
#define EJ1_H

#include <list>
#include <utility>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

using namespace std;

typedef std::vector<int> LBoardState;
typedef std::vector<int> LJumps;


LJumps resolver(int cantBoards, int maxJumps, LBoardState& boards);