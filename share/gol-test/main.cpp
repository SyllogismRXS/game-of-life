#include <iostream>
#include <unistd.h>

#include <gol/GOL.h>

using std::endl;
using std::cout;

int main(int argc, char *argv[])
{
     std::cout << "Game of Life!" << std::endl;

     GOL gol(20,20);

     gol.randomize();
     cout << gol << endl;

     int steps = 100;
     for (int i = 0; i < steps; i++) {
          gol.step();
          cout << gol << endl;
          usleep(500000);
     }

     

     return 0;
}
