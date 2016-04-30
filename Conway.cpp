#include <iostream>

using namespace std;

class Conway
{
     public :
           Conway();
           ~Conway();
           void buildUserMatrix(void);
           void applyRules(void);
           void printAndHousekeeping(void);

     private :
           int x,y;
           int x1;
           int y1;
           int **ary;
           int **aryB;
};


Conway::Conway(void)
{
}


Conway::~Conway(void)
{
     for(int i = 0; i < y; ++i) 
     {
           delete [] ary[i];
     }
     delete [] ary;

     for(int j = 0; j < y; ++j) 
     {
           delete [] aryB[j];
     }
     delete [] aryB;
}


void Conway::buildUserMatrix(void)
{
     std::cout << "Define your matrix dimensions : \n";

     std::cout << "\tx = ";
     cin>>x;
     std::cout << "\ty = ";
     cin>>y;

     ary = new int*[y];
     for(int i = 0; i < y; ++i) 
     {
           ary[i] = new int[x];
     }

     // start all with 0s
     for(int i = 0; i < y; ++i) 
     {
           for(int j = 0; j < x; ++j) 
           {
                ary[i][j] = 0; 
           }
     }

     std::cout << "Tell me where you want 1's (reminders will get 0s) (-1 to start running): \n";
     do 
     {
           std::cout << "\ty = "; 
           cin>>y1;
           std::cout << "\tx = "; 
           cin>>x1;

           if (x1 != -1 && y1 != -1) 
           {
                if (x1 <= x && y1 <= y)
                {
                     ary[y1][x1] = 1;
                }
                else
                {
                     std::cout << "Location outside boundaries or matrix. Error\n";
                     exit(-1);
                }
           }
     } while (x1 != -1 && y1 != -1);
}


void Conway::applyRules(void)
{
     std::cout << "Start\n";
     for(int j = 0; j < y; ++j) 
     {
           for(int i = 0; i < x; ++i) 
           {
                std::cout << ary[j][i] << ' ';
           }
           std::cout << '\n'; 
     }

    aryB = new int*[y];

     for(int j = 0; j < y; ++j) 
     {
           aryB[j] = new int[x];
     }

     // start all with 0s
     for(int j = 0; j < y; ++j) 
     {
           for(int i = 0; i < x; ++i) 
           {
                aryB[j][i] = 0; 
           }
     }

     for(int j = 0; j < y; ++j) 
     {
           for(int i = 0; i < x; ++i) 
           {
                int sum = 0;
                if (j-1 >= 0 && i-1 >= 0)                       { sum += ary[j-1][i-1]; }
                     if (i-1 >= 0)                             { sum += ary[j][i-1];   }
                           if (j+1 < y && i-1 >= 0)                   { sum += ary[j+1][i-1]; }
                           if (j-1 >= 0)                              { sum += ary[j-1][i];   }
                           if (j+1 < y && i < x)                           { sum += ary[j+1][i];   }
                           if (j-1 < y && i+1 < x && j-1 >= 0 && i+1 >= 0)      { sum += ary[j-1][i+1]; }
                           if (i+1 < x && j < y)                           { sum += ary[j][i+1];   }
                           if (j+1 < x && i+1 < x)                    { sum += ary[j+1][i+1]; }

                if (sum < 2)
                           {
                                aryB[j][i] = 0;
                           }
                        if (sum == 2 || sum == 3)
                           {
                                aryB[j][i] = ary[j][i];
                        }
                           if (sum > 3)
                        {
                               aryB[j][i] = 0;
                           }
                           if (ary[j][i] == 0 && sum == 3)
                           {
                                aryB[j][i] = 1;
                        }
           }
     }
}


void Conway::printAndHousekeeping(void)
{
     // re-initalise aryA with aryB in case we want another iteration
     for( int j = 0; j < x; ++j )
     {
           for( int i = 0; i < y; ++i )
           {
                ary[j][i] = aryB[j][i];
           }
     }

     std::cout << "\n\nEnd\n";
     for(int j = 0; j < y; ++j) 
     {
           for(int i = 0; i < x; ++i) 
           {
                std::cout << ary[j][i] << ' ';
           }
           std::cout << '\n'; 
     }
}


int main()
{

     
     Conway conway;
     char ch, ch_main;

     do 
     {
           conway.buildUserMatrix();
           do
           {
                conway.applyRules();
                conway.printAndHousekeeping();

                std::cout << "Run again (Y/N) ? ";

                scanf(" %c", &ch);
           } while (ch == 'Y');

           std::cout << "Enter new matrix (Y/N) ? ";

           scanf(" %c", &ch_main);
        } while (ch_main == 'Y');


     return 0;
}
