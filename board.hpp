#ifndef BOARD
#define BOARD

#include<iostream>
#include <stdio.h>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class board{
    private:
        int num[9][9];
        bool hide[9][9];
    public:
        board();
        void modif(int i,int j, int number);
        void afisare();
        int getNumar(int linie,int coloana);
        bool getHide(int linie,int coloana);
        bool isValid(int linie,int coloana,int number);
        bool generare(int linie,int coloana);
        void makeSudoku();
        ~board();

};

#endif