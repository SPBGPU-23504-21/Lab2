#ifndef Lab2
#define Lab2
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


/// read file function
string ReadFromFile(char *filename);

/**
  Cleaned string of [^\w\ \,\.] and replace [\s]{2,} => \s
  replace word [\w]{10,} => "Vau!!!"
  @return cleaned string \c string
  */
string StringClean(string str);
/**
  * pretty print function
  * @param width an \c int for set width print
  */
template <typename T> void PrintVector(vector<T> v);
void PrettyPrint(string str, int width);

#endif //Lab2
