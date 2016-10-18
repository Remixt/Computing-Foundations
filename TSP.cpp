#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <sstream>
#include <cstdlib>
#include <string>
#include <stdint.h>


using namespace std;



static char gFirstCity = 0;
static unsigned graph[20][20] = {0};
static unsigned minTour = 0xffffffff;


void swap (char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
void permute(char* cities, unsigned start, unsigned length)
{
   if (start == (length-1))
   {


       unsigned cost =0;
       cost+= graph[(unsigned)gFirstCity][(unsigned)*cities];
       for(unsigned i = 0; i < length-1; i++ )
       {
        cost+=graph[(unsigned)cities[i]][(unsigned)cities[i+1]];

       }
       cost+=graph[(unsigned)cities[length-1]][(unsigned)gFirstCity];

       if(cost<minTour){
           minTour = cost;
       }
   }
   else
   {
        for (unsigned j = start; j < length; j++)
        {
            swap((cities + start), (cities + j));
            permute(cities, start + 1, length);
            swap((cities + start), (cities + j));
        }
    }
}


int main()
{
    string cities;
    string printCity = "";
    string line;
    char command = 0;
    unsigned city = 0;
    while (getline(cin, line))
    {
        sscanf(line.c_str(), "%c %d", &command, &city);
        if (command != 'c')
            break;
        cities.push_back((unsigned char)city);
        printCity +=(city);





    }

    gFirstCity = cities[0];

    unsigned to = 0;
    unsigned from = 0;
    uint32_t cost = 0;

    sscanf(line.c_str(), "%c %d %d %d", &command, &to, &from, &cost);
    graph[to][from]=cost;
    graph[from][to]=cost;


    while (getline(cin, line))
    {
        sscanf(line.c_str(), "%c %d %d %d", &command, &to, &from, &cost);
        graph[to][from]=cost;
        graph[from][to]=cost;
    }


    permute((char*)cities.c_str()+1, 0, cities.length()-1);
    cout << "Minimum cost for the tour: ";

    for (unsigned i = 0; i < printCity.length();i++)
    {cout << (unsigned)printCity[i] << " ";}



    cout << " is: "<< minTour << endl;

    return EXIT_SUCCESS;



}
