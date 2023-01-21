#ifndef __OUTILS_HH__
#define __OUTILS_HH__
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "TrueFalse.h"
#include "MCQ.h"

//Load all the True/False questions from the listQTF file
int loadTFQ(vector<TrueFalse*> &TFTable);

//Load all the multiple choices questions from the listMCQ.txt file
int loadMCQ(vector<MCQ*> & MCQTable);

// Randomize a list
template<typename T>
void randomize(vector<T*> &listQuestion);

#endif