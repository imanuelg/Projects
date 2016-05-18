// Velocity.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <Windows.h>
#include <algorithm> 
#include <string>
#include <conio.h>

using namespace std;

class Boid
{
public:

	Boid() { }

	~Boid()
	{
		for (std::vector<Boid*>::iterator itr = BoidsVec.begin(); itr != BoidsVec.end(); itr++)
		{
			delete *itr;
		}
	}
	 // Overload + operator to add two Boids objects.
      Boid operator+(const Boid& b)
      {
         Boid boid;

		 boid.posX = this->posX + b.posX;
         boid.posY = this->posY + b.posY;

		 boid.velocityX = this->velocityX + b.velocityX;
		 boid.velocityY = this->velocityY + b.velocityY;

		 boid.alignmentX = this->alignmentX + b.alignmentX;
		 boid.alignmentY = this->alignmentX + b.alignmentY;

		 boid.cohesionX = this->cohesionX + b.cohesionX;
		 boid.cohesionY = this->cohesionY + b.cohesionY;

		 boid.seperationX = this->seperationX + b.seperationX;
		 boid.seperationY = this->seperationY + b.seperationY;

         return boid;
      }


	void selectRandomPositions(void)
	{
			// initialise initial random boids
			srand (time(NULL));
			for (int i = 0; i < 50; i++)
			{
				double posX = static_cast<int>(rand() % 70 + 1);
				double posY = static_cast<int>(rand() % 24 + 1);

				double velocityX = static_cast<int>(rand() % 10 + 1);
				double velocityY = static_cast<int>(rand() % 10 + 1);
		
				Boid *ptr = new Boid();
				ptr->setX(posX);
				ptr->setY(posY);

				ptr->setVelocityX(velocityX);
				ptr->setVelocityY(velocityY);

				ptr->setAlignmentX(0);
				ptr->setAlignmentY(0);

				ptr->setCohesionX(0);
				ptr->setCohesionY(0);

				ptr->setSeperationX(0);
				ptr->setSeperationY(0);
				
				BoidsVec.push_back(ptr);
			}

	}

	  void setX(double i) { posX = i; }
	  void setY(double j) { posY = j; }

	  void setVelocityX(double i) { velocityX = i; }
	  void setVelocityY(double i) { velocityY = i; }

	  void setAlignmentX(double i) { alignmentX = i; }
	  void setAlignmentY(double i) { alignmentY = i; }

	  void setCohesionX(double i) { cohesionX = i; }
	  void setCohesionY(double i) { cohesionY = i; }

	  void setSeperationX(double i) { seperationX = i; }
	  void setSeperationY(double i) { seperationY = i; }
	  
	  double getX(void) { return posX; }
	  double getY(void) { return posY; }

	  double getVelocityX(void) { return velocityX; }
	  double getVelocityY(void) { return velocityY; }

	  double getAlignmentX(void) { return alignmentX; }
	  double getAlignmentY(void) { return alignmentY; }

	  double getCohesionX(void) { return cohesionX; }
	  double getCohesionY(void) { return cohesionY; }

	  double getSeperationX(void) { return seperationX; }
	  double getSeperationY(void) { return seperationY; }

	  
	  void SetCursorPosition(int x, int y)
	  {
			HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD pos = { x, y };
			SetConsoleCursorPosition(output, pos);
	  }

	  void ClearSceen(const string& ch)
	  {
		  for (int x = 0; x <80; x++)
		  {
			  for (int y = 0; y < 25; y++)
			  {
				  SetCursorPosition(x,y);
				  std::cout << ch;
			  }
		  }
	  }
	  
	  void printBoids(void)
	  {
		 for (std::vector<Boid*>::iterator itr = BoidsVec.begin(); itr != BoidsVec.end(); itr++)
		 {
			int x =  static_cast<int>((*itr)->getX());
			int y =  static_cast<int>((*itr)->getY());
			SetCursorPosition(x,y);
			std::cout << "*";

			//getch();
		 }
	  }

	  void printDetails(void)
	  {
		  std::cout << "\n\n\n\n\n\nPositions:\n";
		  for (std::vector<Boid*>::iterator itr = BoidsVec.begin(); itr != BoidsVec.end(); itr++)
		  {
				std::cout << "x = [" << (*itr)->getX() << "] y = [" << (*itr)->getY() << "]  velocityX = [" << (*itr)->getVelocityX() << "]  velocityY = [" << (*itr)->getVelocityY() << "]\n";
		  }
	  }

	  void Alignment(void)
	  {
			//std::cout << "\nFind Neighbours Alignment (ignoring self) :-\n";
			for (std::vector<Boid*>::iterator OutterItr = BoidsVec.begin(); OutterItr != BoidsVec.end(); OutterItr++)
			{
				int count = 0;
				double AlignmentX = 0;
				double AlignmentY = 0;

				//std::cout << "Doing Boid : [" << (*OutterItr)->getX() << "," << (*OutterItr)->getY() << "]\n";
				std::vector<Boid*> Neighbours;
				for (std::vector<Boid*>::iterator InnerItr = BoidsVec.begin(); InnerItr != BoidsVec.end(); InnerItr++)
				{
					if (*OutterItr == *InnerItr)
					{
						//std::cout << "Ignoring : " << (*OutterItr)->getX() << " and " << (*OutterItr)->getY() << "\n";
						continue;
					}
					if ((abs((*OutterItr)->getX() - (*InnerItr)->getX()) <= 3) ||
						(abs((*OutterItr)->getY() - (*InnerItr)->getY()) <= 3))
					{
						AlignmentX += (*InnerItr)->getVelocityX();
						AlignmentY += (*InnerItr)->getVelocityY();
						//std::cout << "\t\t\t\tNeighbour : [" << (*InnerItr)->getX() << "," << (*InnerItr)->getY() << "] : velX = [" << (*InnerItr)->getVelocityX() << "] velY = [" << (*InnerItr)->getVelocityY() << "]\n";
						count++;
					}
				}
		
				(*OutterItr)->setAlignmentX( AlignmentX / count );
				(*OutterItr)->setAlignmentY( AlignmentY / count );
				//std::cout << "\t\tAlignmentX = [" << (*OutterItr)->getAlignmentX() << "]  AlignmentY = [" << (*OutterItr)->getAlignmentY() << "]\n";
				//std::cout << "\n\n\n";
			}
	  }



	  void Cohesion(void)
	  {
			//std::cout << "\nFind Neighbours Cohesion (ignoring self) :-\n";
			for (std::vector<Boid*>::iterator OutterItr = BoidsVec.begin(); OutterItr != BoidsVec.end(); OutterItr++)
			{
				int count = 0;
				double CohesionX = 0;
				double CohesionY = 0;

				//std::cout << "Doing Boid : [" << (*OutterItr)->getX() << "," << (*OutterItr)->getY() << "]\n";
				std::vector<Boid*> Neighbours;
				for (std::vector<Boid*>::iterator InnerItr = BoidsVec.begin(); InnerItr != BoidsVec.end(); InnerItr++)
				{
					if (*OutterItr == *InnerItr)
					{
						//std::cout << "Ignoring : " << (*OutterItr)->getX() << " and " << (*OutterItr)->getY() << "\n";
						continue;
					}
					if ((abs((*OutterItr)->getX() - (*InnerItr)->getX()) <= 3) ||
						(abs((*OutterItr)->getY() - (*InnerItr)->getY()) <= 3))
					{
						CohesionX += (*InnerItr)->getX();
						CohesionY += (*InnerItr)->getY();
						//std::cout << "\t\t\t\tNeighbour : [" << (*InnerItr)->getX() << "," << (*InnerItr)->getY() << "] : posX = [" << (*InnerItr)->getX() << "] posY = [" << (*InnerItr)->getY() << "]\n";
						count++;
					}
				}
				(*OutterItr)->setCohesionX( CohesionX / count );
				(*OutterItr)->setCohesionY( CohesionY / count );
				//std::cout << "\t\tCohesionX = [" << (*OutterItr)->getCohesionX() << "]  CohesionY = [" << (*OutterItr)->getCohesionY() << "]\n";
				//std::cout << "\n\n\n";
			}
	  }


	  void Separation(void)
	  {
			//std::cout << "\nFind Neighbours Separation (ignoring self) :-\n";
			for (std::vector<Boid*>::iterator OutterItr = BoidsVec.begin(); OutterItr != BoidsVec.end(); OutterItr++)
			{
				int count = 0;
				double SeperationX = 0;
				double SeperationY = 0;

				//std::cout << "Doing Boid : [" << (*OutterItr)->getX() << "," << (*OutterItr)->getY() << "]\n";
				std::vector<Boid*> Neighbours;
				for (std::vector<Boid*>::iterator InnerItr = BoidsVec.begin(); InnerItr != BoidsVec.end(); InnerItr++)
				{
					if ((*OutterItr != *InnerItr) &&
						((abs((*OutterItr)->getX() - (*InnerItr)->getX()) <= 5) ||
						 (abs((*OutterItr)->getY() - (*InnerItr)->getY()) <= 5)))
					{
						SeperationX += (*InnerItr)->getX();
						SeperationY += (*InnerItr)->getY();
						//std::cout << "\t\t\t\tNeighbour : [" << (*InnerItr)->getX() << "," << (*InnerItr)->getY() << "] : posX = [" << (*InnerItr)->getX() << "] posY = [" << (*InnerItr)->getY() << "]\n";
						count++;
					}
				}
				(*OutterItr)->setSeperationX( SeperationX / count );
				(*OutterItr)->setSeperationY( SeperationY / count );
				//std::cout << "\t\tSeperationX = [" << (*OutterItr)->getSeperationX() << "]  SeperationY = [" << (*OutterItr)->getSeperationY() << "]\n";
				//std::cout << "\n\n\n";
			}
	  }

	  void AddAllRules(void)
	  {
		for (std::vector<Boid*>::iterator itr = BoidsVec.begin(); itr != BoidsVec.end(); itr++)
		{
			(*itr)->setVelocityX( (*itr)->getVelocityX() + (*itr)->getAlignmentX() + (*itr)->getCohesionX() + (*itr)->getSeperationX() );
			(*itr)->setVelocityY( (*itr)->getVelocityY() + (*itr)->getAlignmentY() + (*itr)->getCohesionY() + (*itr)->getSeperationY() );

			(*itr)->setX( (*itr)->getX() + (*itr)->getVelocityX() );
			(*itr)->setY( (*itr)->getY() + (*itr)->getVelocityY() );
		}
	  }

private :
	       double posX,posY, velocityX, velocityY, alignmentX, alignmentY, cohesionX, cohesionY, seperationX, seperationY;
		   std::vector<Boid*> BoidsVec;
};



int _tmain(int argc, _TCHAR* argv[])
{
	Boid a;
	a.selectRandomPositions();

	a.ClearSceen(" ");
	a.printBoids();

	//a.ClearSceen(" ");
	//a.printDetails();

	while (1)
	{
		a.Alignment();
		a.Cohesion();
		a.Separation();

		a.AddAllRules();
		Sleep(2000);

		a.ClearSceen(" ");
		a.printBoids();
	}
	return 0;
}

