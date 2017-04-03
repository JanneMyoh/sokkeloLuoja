#include <iostream>
#include "labGen.h"

using namespace std;

int main()
{
    labGen lab;
    lab =  labGen(20);
    for(int i = 0; i < 20; i++)
            {
                for(int j = 0; j < 20; j++)
                {
                    cout << lab.getGlyph(i,j);
                }
                cout << endl;
            }

    return 0;
}
